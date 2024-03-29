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

#ifndef __NMCS_SERVER_SERVICE_MANAGER_H_INCL__
#define __NMCS_SERVER_SERVICE_MANAGER_H_INCL__

#include <nmcs/runtimestring.h>
#include <nmcs/serverservice.h>

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace server {

class NMCS_SHARED_API ServiceManager
{
public:
   virtual ~ServiceManager();

   static ServiceManager& Instance();

   NmcsStatus RegisterService(const runtime::String& serviceId, CREATE_SERVICE_FUNCTION pCreateFunction);
   NmcsStatus RegisterService(const runtime::String& serviceId, CREATE_SERVICE_FUNCTION pCreateFunction, RELEASE_SERVICE_FUNCTION pReleaseFunction);
   void UnregisterService(const runtime::String& serviceId);

   NmcsStatus AcquireService(const runtime::String& serviceId, IServiceCallback* callback, IService*& service);

private:
   ServiceManager();

   std::map<runtime::String, CREATE_SERVICE_FUNCTION> createFunctions_;
   std::recursive_mutex createFunctionsLock_;

   std::map<runtime::String, RELEASE_SERVICE_FUNCTION> releaseFunctions_;
   std::recursive_mutex releaseFunctionsLock_;
};

}}} // namespace ultralove::nmcs::server

#pragma pack(pop)

#endif // #ifndef __NMCS_SERVER_SERVICE_MANAGER_H_INCL__
