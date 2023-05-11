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

#ifndef __NMCS_SERVER_FRAME_H_INCL__
#define __NMCS_SERVER_FRAME_H_INCL__

#include "serverid3v2.h"

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace server {

class Frame
{
public:
   virtual ~Frame();

   static bool IsValid(const uint8_t* data, const size_t dataSize);
   bool IsValid() const;

   inline uint32_t Id() const;
   inline uint32_t Size() const;
   inline uint16_t Flags() const;

   bool ConfigureData(const uint8_t* data, const size_t dataSize);

protected:
   Frame();

   void Id(const uint32_t id);
   void Size(const uint32_t size);
   void Flags(const uint16_t flags);

private:
   uint8_t* data_   = nullptr;
   size_t dataSize_ = ID3V2_INVALID_SIZE_VALUE;

   uint32_t id_     = ID3V2_INVALID_FRAME_ID;
   uint32_t size_   = ID3V2_INVALID_FRAME_SIZE;
   uint16_t flags_  = ID3V2_INVALID_FRAME_FLAGS;

   bool AllocData(const uint8_t* data, const size_t dataSize);
};

inline uint32_t Frame::Id() const
{
   NMCS_PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_FRAME_ID);
   return id_;
}

inline uint32_t Frame::Size() const
{
   NMCS_PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_FRAME_SIZE);
   return size_;
}

inline uint16_t Frame::Flags() const
{
   NMCS_PRECONDITION_RETURN(IsValid() == true, ID3V2_INVALID_FRAME_FLAGS);
   return flags_;
}

}}} // namespace ultralove::nmcs::server

#pragma pack(pop)

#endif // #ifndef __NMCS_SERVER_FRAME_H_INCL__
