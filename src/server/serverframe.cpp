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

#include "serverframe.h"

namespace ultralove { namespace nmcs { namespace server {

Frame::Frame() {}

Frame::~Frame()
{
   SafeDeleteArray(data_);
   dataSize_ = 0;
}

bool Frame::ConfigureData(const uint8_t* data, const size_t dataSize)
{
   NMCS_PRECONDITION_RETURN(data != nullptr, false);
   NMCS_PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_HEADER_SIZE, false);
   NMCS_PRECONDITION_RETURN(data_ == nullptr, false);
   NMCS_PRECONDITION_RETURN(dataSize_ == ID3V2_INVALID_SIZE_VALUE, false);
   NMCS_PRECONDITION_RETURN(id_ == ID3V2_INVALID_FRAME_ID, false);
   NMCS_PRECONDITION_RETURN(size_ == ID3V2_INVALID_FRAME_SIZE, false);
   NMCS_PRECONDITION_RETURN(flags_ == ID3V2_INVALID_FRAME_FLAGS, false);

   bool isValid = AllocData(data, dataSize);
   if (true == isValid) {
      id_                = ID3V2_DECODE_FRAME_ID(&data[ID3V2_FRAME_ID_OFFSET], ID3V2_FRAME_ID_SIZE);
      size_              = ID3V2_DECODE_FRAME_SIZE(&data[ID3V2_FRAME_SIZE_OFFSET], ID3V2_FRAME_SIZE_SIZE);
      flags_             = ID3V2_DECODE_FRAME_FLAGS(&data[ID3V2_FRAME_FLAGS_OFFSET], ID3V2_FRAME_FLAGS_SIZE);
      const bool isValid = IsValid();
      if (false == isValid) {
         id_    = ID3V2_INVALID_FRAME_ID;
         size_  = ID3V2_INVALID_FRAME_SIZE;
         flags_ = ID3V2_INVALID_FRAME_FLAGS;
      }
   }
   return isValid;
}

bool Frame::AllocData(const uint8_t* data, const size_t dataSize)
{
   NMCS_PRECONDITION_RETURN(data != nullptr, false);
   NMCS_PRECONDITION_RETURN(dataSize >= 0, false);

   bool allocated = false;
   SafeDeleteArray(data_);
   dataSize_ = 0;
   data_     = new uint8_t[dataSize];
   if (data_ != nullptr) {
      dataSize_ = dataSize;
      memcpy(data_, data, dataSize_);
      allocated = true;
   }
   return allocated;
}

bool Frame::IsValid(const uint8_t* data, const size_t dataSize)
{
   NMCS_PRECONDITION_RETURN(data != nullptr, false);
   NMCS_PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_HEADER_SIZE, false);

   const bool isConforming = (isalnum(data[0]) != 0) && (isalnum(data[1]) != 0) && (isalnum(data[2]) != 0) && (isalnum(data[3]) != 0);
   return isConforming;
}

bool Frame::IsValid() const
{
   const bool isInitialized = (id_ != ID3V2_INVALID_FRAME_ID) & (size_ != ID3V2_INVALID_FRAME_SIZE) && (flags_ != ID3V2_INVALID_FRAME_FLAGS);
   const bool isConforming =
      (isalnum(((uint8_t*)&id_)[0]) != 0) && (isalnum(((uint8_t*)&id_)[1]) != 0) && (isalnum(((uint8_t*)&id_)[2]) != 0) && (isalnum(((uint8_t*)&id_)[3]) != 0);
   return isInitialized && isConforming;
}

}}} // namespace ultralove::nmcs::server
