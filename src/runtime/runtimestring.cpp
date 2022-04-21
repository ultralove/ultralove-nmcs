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

#include <nmcs/runtimestring.h>

namespace ultralove { namespace nmcs { namespace runtime {

String::String() {}

String::String(const char* str) {}

String::~String() {}

void String::operator=(const char* str) {}

void String::operator=(const char16_t* str) {}

void String::operator=(const char32_t* str) {}

bool String::operator==(const String& str) const
{
   return false;
}

bool String::operator<(const String& str) const
{
   return false;
}

#if 0
bool String::empty() const
{
   return false;
}

size_t String::size() const
{
   return -1;
}

size_t String::length() const
{
   return -1;
}

const char* String::c_str() const
{
   return 0;
}

const char* String::data() const
{
   return 0;
}

String String::substr(const size_t offset = 0, const size_t count = String::NPOS) const
{
   return String();
}

void String::replace(const String& source, const String& target) {}

String& String::append(const char* str)
{
   return *this;
}

void String::trim_left() {}

void String::trim_right() {}

void String::trim() {}

String String::trim_left(String str)
{
   return String();
}

String String::trim_right(String str)
{
   return String();
}

String String::trim(String str)
{
   return String();
}

String String::to_lower()
{
   return String();
}

String String::to_upper()
{
   return String();
}

int String::to_int(const String& str)
{
   return -1;
}

String String::from_int(const int value)
{
   return String();
}
#endif // #if 0

}}} // namespace ultralove::nmcs::runtime
