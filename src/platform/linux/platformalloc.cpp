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

#include <nmcs/platformalloc.h>

namespace ultralove { namespace nmcs { namespace platform {
}}} // namespace ultralove::nmcs::platform

void* Alloc(const size_t size)
{
   NMCS_PRECONDITION_RETURN(size > 0, nullptr);
   return calloc(size, sizeof(uint8_t));
}

void Release(void*& ptr)
{
   NMCS_PRECONDITION(ptr != nullptr);
   free(ptr);
   ptr = nullptr;
}

uint32_t NmcsUnsynchronize32(const uint32_t value)
{
   uint32_t result = 0;

   uint32_t first  = value & 0xFF;
   uint32_t second = (value >> 8) & 0xFF;
   uint32_t third  = (value >> 16) & 0xFF;
   uint32_t fourth = (value >> 24) & 0xFF;
   result          = result | first;
   result          = result | (second << 7);
   result          = result | (third << 14);
   result          = result | (fourth << 21);

   return result;
}

uint32_t NmcsSynchronize32(const uint32_t value)
{
   uint32_t result      = 0;

   uint32_t valueBuffer = value;
   uint32_t valueMask   = 0x7F;

   while (valueMask ^ 0x7FFFFFFF) {
      result = valueBuffer & ~valueMask;
      result <<= 1;
      result |= valueBuffer & valueMask;
      valueMask   = ((valueMask + 1) << 8) - 1;
      valueBuffer = result;
   }

   return result;
}
