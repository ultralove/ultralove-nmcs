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

#include "serverurllinkframe.h"
#include "serverframeresource.h"

namespace ultralove { namespace nmcs { namespace server {

static FrameResource<URLLinkFrame> resource1("WCOM");
static FrameResource<URLLinkFrame> resource2("WCOP");
static FrameResource<URLLinkFrame> resource3("WOAF");
static FrameResource<URLLinkFrame> resource4("WOAR");
static FrameResource<URLLinkFrame> resource5("WOAS");
static FrameResource<URLLinkFrame> resource6("WORS");
static FrameResource<URLLinkFrame> resource7("WPAY");
static FrameResource<URLLinkFrame> resource8("WPUB");

URLLinkFrame::URLLinkFrame() {}

URLLinkFrame::~URLLinkFrame() {}

Frame* URLLinkFrame::Create()
{
   return new URLLinkFrame();
}

}}} // namespace ultralove::nmcs::server
