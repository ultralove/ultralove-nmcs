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

#include "clientapplication.h"

namespace ultralove { namespace nmcs { namespace client {

ClientApplication::ClientApplication() : CLI::App("Ultralove NMCS CLI " + std::string(NmcsBuildString())), args_(std::make_shared<ClientApplicationArgs>())
{
   add_flag("--nologo", args_->suppressLogo, "Do not display the startup banner and copyright message");
   add_flag("--version", args_->printVersion, "Display version information");
   callback([&]() { Run(args_); });
}

void ClientApplication::pre_callback()
{
   if ((false == args_->suppressLogo) && (false == args_->printVersion)) {
      std::cout << "Ultralove NMCS CLI " << NmcsBuildString() << std::endl
                << "Copyright (c) ultralove contributors (https://github.com/ultralove)" << std::endl
                << std::endl;
   }
   if (true == args_->printVersion) {
      std::cout << NmcsVersion() << std::endl;
   }
}

void ClientApplication::Run(const std::shared_ptr<ClientApplicationArgs>& args) {}

}}} // namespace ultralove::nmcs::client
