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

#include "servertextinformationframe.h"
#include "serverframeresource.h"

namespace ultralove { namespace nmcs { namespace server {

static FrameResource<TextInformationFrame> resource1("TALB");
static FrameResource<TextInformationFrame> resource2("TBPM");
static FrameResource<TextInformationFrame> resource3("TCOM");
static FrameResource<TextInformationFrame> resource4("TCON");
static FrameResource<TextInformationFrame> resource5("TCOP");
static FrameResource<TextInformationFrame> resource6("TDAT");
static FrameResource<TextInformationFrame> resource7("TDLY");
static FrameResource<TextInformationFrame> resource8("TENC");
static FrameResource<TextInformationFrame> resource9("TEXT");
static FrameResource<TextInformationFrame> resource10("TFLT");
static FrameResource<TextInformationFrame> resource11("TIME");
static FrameResource<TextInformationFrame> resource12("TIT1");
static FrameResource<TextInformationFrame> resource13("TIT2");
static FrameResource<TextInformationFrame> resource14("TIT3");
static FrameResource<TextInformationFrame> resource15("TKEY");
static FrameResource<TextInformationFrame> resource16("TLAN");
static FrameResource<TextInformationFrame> resource17("TLEN");
static FrameResource<TextInformationFrame> resource18("TMED");
static FrameResource<TextInformationFrame> resource19("TOAL");
static FrameResource<TextInformationFrame> resource20("TOFN");
static FrameResource<TextInformationFrame> resource21("TOLY");
static FrameResource<TextInformationFrame> resource22("TOPE");
static FrameResource<TextInformationFrame> resource23("TORY");
static FrameResource<TextInformationFrame> resource24("TOWN");
static FrameResource<TextInformationFrame> resource25("TPE1");
static FrameResource<TextInformationFrame> resource26("TPE2");
static FrameResource<TextInformationFrame> resource27("TPE3");
static FrameResource<TextInformationFrame> resource28("TPE4");
static FrameResource<TextInformationFrame> resource29("TPOS");
static FrameResource<TextInformationFrame> resource30("TPUB");
static FrameResource<TextInformationFrame> resource31("TRCK");
static FrameResource<TextInformationFrame> resource32("TRDA");
static FrameResource<TextInformationFrame> resource33("TRSN");
static FrameResource<TextInformationFrame> resource34("TRSO");
static FrameResource<TextInformationFrame> resource35("TSIZ");
static FrameResource<TextInformationFrame> resource36("TSRC");
static FrameResource<TextInformationFrame> resource37("TSSE");
static FrameResource<TextInformationFrame> resource38("TYER");

TextInformationFrame::TextInformationFrame() {}

TextInformationFrame::~TextInformationFrame() {}

IFrame* TextInformationFrame::Create()
{
   return new TextInformationFrame();
}

}}} // namespace ultralove::nmcs::server
