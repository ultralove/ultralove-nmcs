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
#include <nmcs/runtimeguid.h>

namespace ultralove { namespace nmcs { namespace runtime {

const Guid Guid::null_;

Guid::Guid()
{
   memset(data_, 0, sizeof(uint8_t) * 16);
}

Guid::~Guid() {}

Guid::Guid(const Guid& rhs)
{
   *this = rhs;
}

Guid& Guid::operator=(const Guid& rhs)
{
   memcpy(data_, rhs.data_, sizeof(uint8_t) * 16);
   return *this;
}

bool Guid::operator==(const Guid& rhs) const
{
   return memcmp(data_, rhs.data_, sizeof(uint8_t) * 16) == 0;
}

bool Guid::operator<(const Guid& rhs) const
{
   return memcmp(data_, rhs.data_, sizeof(uint8_t) * 16) < 0;
}

Guid Guid::Create()
{
   Guid guid;
   platform::CreateGuid(guid.data_);
   return guid;
}

Guid Guid::Create(const char* str)
{
   Guid guid;
   platform::CreateGuidFromString(str, guid.data_);
   return guid;
}

const Guid& Guid::Null()
{
   return null_;
}

}}} // namespace ultralove::nmcs::runtime
