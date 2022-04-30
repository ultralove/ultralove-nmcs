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

#ifndef __NMCS_RUNTIME_STREAM_H_INCL__
#define __NMCS_RUNTIME_STREAM_H_INCL__

#include <nmcs/runtimeshared.h>

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace runtime {

class NMCS_SHARED_API Stream : public Shared
{
public:
   explicit Stream(const size_t size);

   size_t Size() const;
   const uint8_t* Data() const;

   bool Write(const size_t offset, const uint8_t* data, const size_t size);
   bool Read(const size_t offset, uint8_t* data, const size_t size);

protected:
   virtual ~Stream();
};

}}} // namespace ultralove::nmcs::runtime

#pragma pack(pop)

#endif // #ifdef __NMCS_RUNTIME_STREAM_H_INCL__
