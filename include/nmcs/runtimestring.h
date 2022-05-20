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

#ifndef __NMCS_RUNTIME_STRING_H_INCL__
#define __NMCS_RUNTIME_STRING_H_INCL__

#include <nmcs/common.h>

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace runtime {

class NMCS_SHARED_API String
{
public:
   enum class Encoding
   {
      LATIN1,
      UTF8,
      UTF16,
      UTF16_LE,
      UTF16_BE,
      UTF32,
      MAX_STRING_ENCODING     = UTF32,
      INVALID_STRING_ENCODING = MAX_STRING_ENCODING + 1
   };

   String();
   String(const char* str, const size_t size);
   virtual ~String();

   String(const String& rhs);
   void operator=(const String& rhs);

   void operator=(const char* str);
   void operator=(const char16_t* str);
   void operator=(const char32_t* str);

   String(const uint8_t* data, const size_t dataSize);
   String(const uint16_t* data, const size_t dataSize);
   String(const uint32_t* data, const size_t dataSize);

   bool operator==(const String& rhs) const;
   bool operator<(const String& rhs) const;

   const uint8_t* Data() const;
   size_t Size() const;
   Encoding Encoding() const;

private:
   uint8_t* data_          = 0;
   size_t dataSize_        = 0;
   enum Encoding encoding_ = Encoding::INVALID_STRING_ENCODING;
};

}}} // namespace ultralove::nmcs::runtime

#pragma pack(pop)

#endif // #ifndef __NMCS_RUNTIME_STRING_H_INCL__
