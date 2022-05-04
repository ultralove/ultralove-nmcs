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

#ifndef __NMCS_SERVER_FRAME_FACTORY_H_INCL__
#define __NMCS_SERVER_FRAME_FACTORY_H_INCL__

#include "serverframe.h"

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace server {

class FrameFactory
{
public:
   typedef IFrame* (*CREATE_FRAME_FUNCTION)();

   static FrameFactory& Instance();
   virtual ~FrameFactory();

   bool RegisterFrame(const uint32_t id, CREATE_FRAME_FUNCTION factoryFunction);
   void UnregisterFrame(const uint32_t id);

   bool CanCreate(const uint8_t* data, const size_t dataSize) const;
   IFrame* Create(const uint8_t* data, const size_t dataSize) const;

private:
   FrameFactory();

   typedef std::map<uint32_t, CREATE_FRAME_FUNCTION> FunctionDictionary;
   FunctionDictionary functions_;
   mutable std::recursive_mutex functionsLock_;
};

}}} // namespace ultralove::nmcs::server

#pragma pack(pop)

#endif // #ifndef __NMCS_SERVER_FRAME_FACTORY_H_INCL____
