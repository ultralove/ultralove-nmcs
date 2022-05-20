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

#ifndef __NMCS_SERVER_SERVICE_RESOURCE_H_INCL__
#define __NMCS_SERVER_SERVICE_RESOURCE_H_INCL__

#include "serverservicefactory.h"

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace server {

template<class T> class ServiceResource
{
public:
   ServiceResource(const char* id)
   {
      ServiceResource(runtime::String(id, strlen(id)));
   }

   ServiceResource(const runtime::String& id)
   {
      NMCS_PRECONDITION(id.Size() > 0);

      id_                            = id;
      ServiceFactory& serviceFactory = ServiceFactory::Instance();
      registered_                    = serviceFactory.RegisterService(id, T::CreateService);
   }

   ~ServiceResource()
   {
      if (true == registered_) {
         ServiceFactory& serviceFactory = ServiceFactory::Instance();
         serviceFactory.UnregisterService(id_);
      }
   }

private:
   runtime::String id_;
   bool registered_ = false;
};

}}} // namespace ultralove::nmcs::server

#pragma pack(pop)

#endif // #ifndef __NMCS_SERVER_SERVICE_RESOURCE_H_INCL__
