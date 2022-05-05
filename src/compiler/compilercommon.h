////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) Ultralove NMCS Contributors (https://github.com/ultralove)
//
// The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __NMCS_COMPILER_COMMON_H_INCL__
#define __NMCS_COMPILER_COMMON_H_INCL__

#include <nmcs/common.h>
#include <nmcs/model.h>
#include <nmcs/platform.h>
#include <nmcs/runtime.h>

namespace nmcs     = ultralove::nmcs;
namespace platform = ultralove::nmcs::platform;
namespace runtime  = ultralove::nmcs::runtime;
namespace model    = ultralove::nmcs::model;

#include <CLI/CLI.hpp>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace client {
}}} // namespace ultralove::nmcs::client

#pragma pack(pop)

#endif // #ifndef __NMCS_COMPILER_COMMON_H_INCL__
