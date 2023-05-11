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

#ifndef __NMCS_RUNTIME_GUID_H_INCL__
#define __NMCS_RUNTIME_GUID_H_INCL__

#include <nmcs/common.h>

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace runtime {

class NMCS_SHARED_API Guid
{
public:
   explicit Guid(const char* str);
   virtual ~Guid();

   Guid(const Guid& rhs);
   Guid& operator=(const Guid& rhs);

   bool operator==(const Guid& rhs) const;
   bool operator<(const Guid& rhs) const;

   static Guid Create();
   static Guid Create(const char* str);
   static const Guid& Null();

   std::string PlainString() const;
   std::string RegistryString() const;
   std::string UniversalString() const;

private:
   uint8_t data_[16];
   static const Guid null_;

   Guid();
};

}}} // namespace ultralove::nmcs::runtime

#pragma pack(pop)

#endif // #ifndef __NMCS_RUNTIME_GUID_H_INCL__
