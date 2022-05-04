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

#include "clientchapterscommand.h"

namespace ultralove { namespace nmcs { namespace client {

void ChaptersCommand::Configure(CLI::App& app)
{
   std::shared_ptr<ChaptersCommandArgs> args = std::make_shared<ChaptersCommandArgs>();
   CLI::App* command                         = app.add_subcommand("chapters", "TODO");
   command->add_flag("-d,--dump", args->dump, "Print chapters");
   command->add_flag("-r,--raw", args->raw, "Don't invoke chapter parser");
   command->callback([args]() { Run(args); });
}

void ChaptersCommand::Run(const std::shared_ptr<ChaptersCommandArgs>& args) {}

}}} // namespace ultralove::nmcs::client
