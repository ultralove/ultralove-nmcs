////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) ultralove contributors (https://github.com/ultralove)
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

#include "compilercommon.h"
#include "compilerdriver.h"
#include "compilerparser.h"
#include "compilerscanner.h"

bool suppressLogo             = false;
bool printVersion             = false;

namespace compiler            = ultralove::nmcs::compiler;
compiler::EmitterType emitter = compiler::EmitterType::CPP_EMITTER;

void PrintLogo();
void PrintVersion();
const char* Version();

int Parse(const char* filename);

int main(int argc, char** argv)
{
   CLI::App app{"Ultralove NMCS Domain Model Compiler version 1.0.0"};

   using namespace CLI::enums;
   std::vector<std::pair<std::string, compiler::EmitterType>> emitterTypes{
      {       "c++",        compiler::EmitterType::CPP_EMITTER},
      {        "c#",     compiler::EmitterType::CSHARP_EMITTER},
      {     "swift",      compiler::EmitterType::SWIFT_EMITTER},
      {"typescript", compiler::EmitterType::TYPESCRIPT_EMITTER},
      {      "java",       compiler::EmitterType::JAVA_EMITTER}
   };
   app.add_option("-e,--emitter", emitter, "Specify target language")->transform(CLI::CheckedTransformer(emitterTypes, CLI::ignore_case));
   app.add_flag("--nologo", suppressLogo, "Do not display the startup banner and copyright message");
   app.add_flag("--version", printVersion, "Display compiler version information");

   try {
      app.parse(argc, argv);
      PrintLogo();
      PrintVersion();
   }
   catch (const CLI::ParseError& e) {
      app.exit(e);
   }

   return 0;
}

void PrintLogo()
{
   if ((false == suppressLogo) && (false == printVersion)) {
      std::cout << "Ultralove NMCS Domain Model Compiler version " << Version() << std::endl
                << "Copyright (c) ultralove contributors (https://github.com/ultralove)" << std::endl
                << std::endl;
   }
}

void PrintVersion()
{
   if (true == printVersion) {
      std::cout << Version() << std::endl;
   }
}

const char* Version()
{
   return "1.0.0";
}

void yyerror(const char* s)
{
   PRECONDITION(s != nullptr);

   // fprintf(stderr, "Syntax error in %s(%d): %s\n", currentInputFile, yylineno, s);
   fprintf(stderr, "\nSyntax error: %s\n", s);
   exit(1);
}

int Parse(const char* filename)
{
   PRECONDITION_RETURN(filename != nullptr, -1);

   extern FILE* yyin;
   yyin = fopen(filename, "r");
   if (yyin != nullptr) {
      printf("Compiling %s...\n", filename);

      do {
         yyparse();
      }
      while (!feof(yyin));

      fclose(yyin);
   }
   else {
      fprintf(stderr, "Failed to open source file '%s': %s\n", filename, strerror(errno));
      return -1;
   }

   return 0;
}
