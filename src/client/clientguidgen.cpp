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

#include <nmcs/runtimeguid.h>

#include "clientguidgen.h"

namespace ultralove { namespace nmcs { namespace client {

void Guidgen::Configure(CLI::App& app)
{
   std::shared_ptr<GuidgenArgs> args         = std::make_shared<GuidgenArgs>();
   CLI::App* command                         = app.add_subcommand("guidgen", "Generate a new GUID");
   std::map<std::string, GuidFormat> formats = {
      {"universal", GuidFormat::Universal},
      {    "plain",     GuidFormat::Plain},
      { "registry",  GuidFormat::Registry}
   };
   command->add_option("-f,--format", args->format, "Specify output format")->transform(CLI::CheckedTransformer(formats, CLI::ignore_case));
   command->callback([args]() { Run(args); });
}

void Guidgen::Run(const std::shared_ptr<GuidgenArgs>& args)
{
   runtime::Guid guid = runtime::Guid::Create();
   switch (args->format) {
      case GuidFormat::Universal:
         std::cout << guid.UniversalString() << std::endl;
         break;
      case GuidFormat::Plain:
         std::cout << guid.PlainString() << std::endl;
         break;
      case GuidFormat::Registry:
         std::cout << guid.RegistryString() << std::endl;
         break;
   }
}

}}} // namespace ultralove::nmcs::client
