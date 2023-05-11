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

namespace ultralove { namespace nmcs { namespace platform {

NmcsStatus CreateGuid(uint8_t* data)
{
   NMCS_PRECONDITION_RETURN(data != nullptr, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
   return status;
}

NmcsStatus CreateGuidFromString(const char* str, uint8_t* data)
{
   NMCS_PRECONDITION_RETURN(str != nullptr, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(data != nullptr, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
   return status;
}

NMCS_SHARED_API NmcsStatus CreateGuidString(const uint8_t* data, char* str, const size_t strSize)
{
   NMCS_PRECONDITION_RETURN(data != nullptr, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(str != nullptr, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(strSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(strSize <= 16, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
   return status;
}

}}} // namespace ultralove::nmcs::platform
