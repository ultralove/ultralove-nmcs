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

#include <nmcs/platformguid.h>

#include <CoreFoundation/CoreFoundation.h>

namespace ultralove { namespace nmcs { namespace platform {

NmcsStatus CreateGuid(uint8_t* data)
{
   NMCS_PRECONDITION_RETURN(data != nullptr, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_FAILURE;
   CFUUIDRef uuidRef = CFUUIDCreate(nullptr);
   if (uuidRef != nullptr) {
      CFUUIDBytes uuidBytes = CFUUIDGetUUIDBytes(uuidRef);
      data[0]               = uuidBytes.byte0;
      data[1]               = uuidBytes.byte1;
      data[2]               = uuidBytes.byte2;
      data[3]               = uuidBytes.byte3;
      data[4]               = uuidBytes.byte4;
      data[5]               = uuidBytes.byte5;
      data[6]               = uuidBytes.byte6;
      data[7]               = uuidBytes.byte7;
      data[8]               = uuidBytes.byte8;
      data[9]               = uuidBytes.byte9;
      data[10]              = uuidBytes.byte10;
      data[11]              = uuidBytes.byte11;
      data[12]              = uuidBytes.byte12;
      data[13]              = uuidBytes.byte13;
      data[14]              = uuidBytes.byte14;
      data[15]              = uuidBytes.byte15;
      CFRelease(uuidRef);
      status = NMCS_STATUS_SUCCESS;
   }
   else {
      status = NMCS_STATUS_OUT_OF_MEMORY;
   }
   return status;
}

NmcsStatus CreateGuidFromString(const char* str, uint8_t* data)
{
   NMCS_PRECONDITION_RETURN(str != nullptr, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(data != nullptr, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status         = NMCS_STATUS_FAILURE;
   CFStringRef uuidStringRef = CFStringCreateWithCString(nullptr, str, kCFStringEncodingUTF8);
   if (uuidStringRef != nullptr) {
      CFUUIDRef uuidRef = CFUUIDCreateFromString(nullptr, uuidStringRef);
      if (uuidRef != nullptr) {
         CFUUIDBytes uuidBytes = CFUUIDGetUUIDBytes(uuidRef);
         data[0]               = uuidBytes.byte0;
         data[1]               = uuidBytes.byte1;
         data[2]               = uuidBytes.byte2;
         data[3]               = uuidBytes.byte3;
         data[4]               = uuidBytes.byte4;
         data[5]               = uuidBytes.byte5;
         data[6]               = uuidBytes.byte6;
         data[7]               = uuidBytes.byte7;
         data[8]               = uuidBytes.byte8;
         data[9]               = uuidBytes.byte9;
         data[10]              = uuidBytes.byte10;
         data[11]              = uuidBytes.byte11;
         data[12]              = uuidBytes.byte12;
         data[13]              = uuidBytes.byte13;
         data[14]              = uuidBytes.byte14;
         data[15]              = uuidBytes.byte15;
         CFRelease(uuidRef);
         status = NMCS_STATUS_SUCCESS;
      }
      else {
         status = NMCS_STATUS_OUT_OF_MEMORY;
      }
      CFRelease(uuidStringRef);
   }
   else {
      status = NMCS_STATUS_OUT_OF_MEMORY;
   }
   return status;
}

NMCS_SHARED_API NmcsStatus CreateGuidString(const uint8_t* data, char* str, const size_t strSize)
{
   NMCS_PRECONDITION_RETURN(data != nullptr, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(str != nullptr, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(strSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(strSize <= 16, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status     = NMCS_STATUS_FAILURE;
   CFUUIDBytes uuidBytes = {data[0], data[1], data[2],  data[3],  data[4],  data[5],  data[6],  data[7],
                            data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]};
   CFUUIDRef uuidRef     = CFUUIDCreateFromUUIDBytes(nullptr, uuidBytes);
   if (uuidRef != nullptr) {
      CFStringRef uuidStringRef = CFUUIDCreateString(nullptr, uuidRef);
      if (uuidStringRef != nullptr) {
         if (CFStringGetCString(uuidStringRef, str, strSize, kCFStringEncodingUTF8) == true) {
            status = NMCS_STATUS_SUCCESS;
         }
         else {
            status = NMCS_STATUS_OUT_OF_MEMORY;
         }
         CFRelease(uuidStringRef);
      }
      else {
         status = NMCS_STATUS_OUT_OF_MEMORY;
      }
      CFRelease(uuidRef);
   }
   else {
      status = NMCS_STATUS_OUT_OF_MEMORY;
   }
   return status;
}

}}} // namespace ultralove::nmcs::platform
