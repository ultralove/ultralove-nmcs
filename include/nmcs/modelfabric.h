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

#ifndef __NMCS_MODEL_FABRIC_H_INCL__
#define __NMCS_MODEL_FABRIC_H_INCL__

#include <nmcs/runtimeguid.h>
#include <nmcs/runtimestring.h>
#include <nmcs/runtimetimestamp.h>

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace model {

class NMCS_SHARED_API Fabric
{
public:
   static const runtime::Guid& TypeId();

   runtime::Guid id_;
   runtime::Timestamp creationDate_;
   runtime::Timestamp modificationDate_;
   runtime::String comment_;

protected:
   static const runtime::Guid typeId_;
   virtual ~Fabric() {}
};

}}} // namespace ultralove::nmcs::model

#pragma pack(pop)

#endif // #ifndef __NMCS_MODEL_FABRIC_H_INCL__
