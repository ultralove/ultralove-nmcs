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

#include <algorithm>
#include <iostream>

#include <CLI/CLI.hpp>

#include <nmcs/common.h>

#include "compilerdriver.h"
#include "version.h"

bool suppressLogo             = false;
bool printVersion             = false;

namespace compiler            = ultralove::nmcs::compiler;
compiler::EmitterType emitter = compiler::EmitterType::CPP_EMITTER;
std::string input;

void PrintLogo();
void PrintVersion();

int Parse(const char* filename);

int main(int argc, char** argv)
{
   const std::string banner = "Ultralove NMCS Domain Model Compiler " + std::string(NmcsBuildString());
   CLI::App app{banner};

   std::map<std::string, compiler::EmitterType> emitters{
      {       "C++",        compiler::EmitterType::CPP_EMITTER},
      {        "C#",     compiler::EmitterType::CSHARP_EMITTER},
      {     "Swift",      compiler::EmitterType::SWIFT_EMITTER},
      {"Typescript", compiler::EmitterType::TYPESCRIPT_EMITTER},
      {      "Java",       compiler::EmitterType::JAVA_EMITTER}
   };
   app.add_option("-e,--emitter", emitter, "Specify target language")->transform(CLI::CheckedTransformer(emitters, CLI::ignore_case));

   app.add_flag("--nologo", suppressLogo, "Do not display the startup banner and copyright message");
   app.add_flag("--version", printVersion, "Display compiler version information");
   app.add_option("file", input, "Specify the input file");
   try {
      app.parse(argc, argv);
      PrintLogo();
      PrintVersion();
      if (input.empty() == false) {
         Parse(input.c_str());
      }
   }
   catch (const CLI::ParseError& e) {
      app.exit(e);
   }
   return 0;
}

void PrintLogo()
{
   if ((false == suppressLogo) && (false == printVersion)) {
      std::cout << "Ultralove NMCS Domain Model Compiler " << NmcsBuildString() << std::endl
                << "Copyright (c) Ultralove NMCS Contributors (https://github.com/ultralove)" << std::endl
                << std::endl;
   }
}

void PrintVersion()
{
   if (true == printVersion) {
      std::cout << NmcsVersion() << std::endl;
   }
}

int Parse(const char* filename)
{
   NMCS_PRECONDITION_RETURN(filename != nullptr, -1);
   return 0;
}
