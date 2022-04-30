#!/bin/bash

################################################################################
#
# Copyright (c) Ultralove NMCS Contributors (https://github.com/ultralove)
#
# The MIT License (MIT)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
################################################################################

BUILD_CLEAN=0
BUILD_CONFIGURATION="Debug"
BUILD_DIRECTORY="$(pwd)/build"
BUILD_ARTIFACTS="$BUILD_DIRECTORY/artifacts"
BUILD_REBUILD=0
BUILD_SHARED="ON"
BUILD_INSTALL=0
BUILD_UNINSTALL=0
BUILD_PACKAGE=0
BUILD_THREADS=4

CMAKE_BUILD_ARGS=""
CMAKE_GENERATOR="Ninja"
CMAKE_INSTALL_FOUND=0
CMAKE_INSTALL_PATH=cmake
CMAKE_REQUIRED_VERSION="3.19.0"

source "scripts/buildtools.sh"

for arg in "$@"
do
case $arg in
    --bootstrap)
    BUILD_BOOTSTRAP=1
    shift # past argument
    ;;
    --clean)
    BUILD_CLEAN=1
    shift # past argument
    ;;
    -c=*|--config=*)
    BUILD_CONFIGURATION="${arg#*=}"
    shift # past argument
    ;;
    -i|--install)
    BUILD_INSTALL=1
    shift # past argument
    ;;
    -n|--no-shared)
    BUILD_SHARED="OFF"
    shift # past argument
    ;;
    -p|--package)
    BUILD_PACKAGE=1
    shift # past argument
    ;;
    --rebuild)
    CMAKE_BUILD_ARGS="$CMAKE_BUILD_ARGS --clean-first "
    shift # past argument
    ;;
    -r|--release)
    BUILD_CONFIGURATION="Release"
    shift # past argument
    ;;
    "-h"|"--help")
    echo "Usage: build.sh [options]"
    echo ""
    echo "Options:"
    echo "  --clean                                     Completely remove build output"
    echo "  -c=<BUILD_CONFIG>|--config=<BUILD_CONFIG>   Specify build configuration (default = 'Debug')"
    echo "  -i|--install                                Install build targets to /usr/local"
    echo "  -n|--no-shared                              Don't build shared libraries"
    echo "  -p|--package                                Build distributable package"
    echo "  --rebuild                                   Remove intermediate files before build"
    echo "  --release                                   Don't include debug symbols, overrides '-c|--config'"
    echo "  -u|--uninstall                              Remove build targets from /usr/local"
    echo ""
    exit 0
    shift # past argument
    ;;
    -u|--uninstall)
    BUILD_UNINSTALL=1
    shift # past argument
    ;;
    *)    # unknown option
    echo "Unknown argument $arg"
    exit 1
    ;;
esac
done

if [ $BUILD_UNINSTALL -ne 0 ]; then
  echo "Uninstalling..."
  if [ -f "$BUILD_DIRECTORY/install_manifest.txt" ]; then
    xargs sudo rm -f < "$BUILD_DIRECTORY/install_manifest.txt"
    sudo rm -rf "$CMAKE_INSTALL_PREFIX/include/nmcs"
    echo "Done."
  fi
  exit 0
fi

if [ $BUILD_CLEAN -eq 1 ]; then
  if [ -d "$BUILD_DIRECTORY" ]; then
    rm -rf "$BUILD_DIRECTORY"
  fi
  if [ -d "$BUILD_TARGET_DIRECTORY" ]; then
    rm -rf "$BUILD_TARGET_DIRECTORY"
  fi
  exit 0
fi

echo "Looking for CMake $CMAKE_REQUIRED_VERSION..."
if [ $CMAKE_INSTALL_FOUND -eq 0 ]; then
  if [ -x "$(command -v $CMAKE_INSTALL_PATH)" ]; then
    CMAKE_CURRENT_VERSION=`$CMAKE_INSTALL_PATH --version | sort -V | tail -n 1 | awk -v n=3 '{print $n}'`
    echo "Found CMake version $CMAKE_CURRENT_VERSION."
    CompareVersions $CMAKE_CURRENT_VERSION $CMAKE_REQUIRED_VERSION
    if [ ! $? -eq 2 ]; then
      CMAKE_INSTALL_FOUND=1
    fi
  fi
fi

if [ $CMAKE_INSTALL_FOUND -eq 0 ]; then
  echo "CMake not found. Please install at least CMake version $CMAKE_REQUIRED_VERSION."
  exit 1
fi

if [ ! -d "$BUILD_DIRECTORY" ]; then
    echo "Configuring projects using $CMAKE_GENERATOR..."
    cmake -B"$BUILD_DIRECTORY" -G"$CMAKE_GENERATOR" -Wno-dev --no-warn-unused-cli -DBUILD_SHARED_LIBS="$BUILD_SHARED" -DNMCS_BUILD_PACKAGE="$BUILD_PACKAGE" -DNMCS_BUILD_ID=0 -DCMAKE_BUILD_TYPE="$BUILD_CONFIGURATION"
    if [ $? -ne 0 ]; then
      echo "Failed to configure projects."
      exit -1
    fi
    echo "Done."
fi

echo "Building projects..."
cmake --build "$BUILD_DIRECTORY" $CMAKE_BUILD_ARGS --config "$BUILD_CONFIGURATION" -j
if [ $? -ne 0 ]; then
  echo "Failed to build projects."
  exit -1
fi
echo "Done."

if [ $BUILD_PACKAGE -ne 0 ]; then
  echo "Packaging targets..."
  cmake --build "$BUILD_DIRECTORY" --config "$BUILD_CONFIGURATION" --target package
  if [ $? -ne 0 ]; then
    echo "Failed to package targets."
    exit -1
  fi
  echo "Done."
fi

if [ $BUILD_INSTALL -ne 0 ]; then
  echo "Installing targets to $CMAKE_INSTALL_PREFIX..."
  sudo cmake --build "$BUILD_DIRECTORY" --config "$BUILD_CONFIGURATION" --target install
  if [ $? -ne 0 ]; then
    echo "Failed to install targets."
    exit -1
  fi
  echo "Done."
fi

exit 0
