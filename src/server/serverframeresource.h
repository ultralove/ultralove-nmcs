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

#ifndef __NMCS_SERVER_FRAME_RESOURCE_H_INCL__
#define __NMCS_SERVER_FRAME_RESOURCE_H_INCL__

#include "serverframefactory.h"

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace server {

template<class T> class FrameResource
{
public:
   FrameResource(const char* id)
   {
      FrameResource(runtime::String(id, 4));
   }

   FrameResource(const runtime::String& id)
   {
      NMCS_PRECONDITION(id.Size() >= ID3V2_FRAME_ID_SIZE);

      id_                        = ID3V2_DECODE_FRAME_ID(reinterpret_cast<const uint8_t*>(id.Data()), ID3V2_FRAME_ID_SIZE);
      FrameFactory& frameFactory = FrameFactory::Instance();
      registered_                = frameFactory.RegisterFrame(id_, T::Create);
   }

   ~FrameResource()
   {
      if ((id_ != ID3V2_INVALID_FRAME_ID) && (true == registered_)) {
         FrameFactory& frameFactory = FrameFactory::Instance();
         frameFactory.UnregisterFrame(id_);
      }
   }

private:
   uint32_t id_     = ID3V2_INVALID_FRAME_ID;
   bool registered_ = false;
};

}}} // namespace ultralove::nmcs::server

#pragma pack(pop)

#endif // #ifndef __NMCS_SERVER_FRAME_RESOURCE_H_INCL__
