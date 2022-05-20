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

#include "serverservicefactory.h"

#include <nmcs/serverservicemanager.h>

namespace ultralove { namespace nmcs { namespace server {

ServiceManager::ServiceManager() {}

ServiceManager::~ServiceManager() {}

NmcsStatus ServiceManager::RegisterService(const runtime::String& serviceId, CREATE_SERVICE_FUNCTION pCreateFunction)
{
   NMCS_PRECONDITION_RETURN(serviceId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pCreateFunction != 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_FAILURE;

   std::lock_guard<std::recursive_mutex> lock(createFunctionsLock_);
   const std::map<runtime::String, CREATE_SERVICE_FUNCTION>::const_iterator functionIterator = createFunctions_.find(serviceId);
   if (functionIterator == createFunctions_.end()) {
      createFunctions_.insert(std::pair<const runtime::String, CREATE_SERVICE_FUNCTION>(serviceId, pCreateFunction));
      status = NMCS_STATUS_SUCCESS;
   }
   else {
      status = NMCS_STATUS_ALREADY_REGISTERED;
   }

   return status;
}

NmcsStatus ServiceManager::RegisterService(const runtime::String& serviceId, CREATE_SERVICE_FUNCTION pCreateFunction, RELEASE_SERVICE_FUNCTION pReleaseFunction)
{
   NMCS_PRECONDITION_RETURN(serviceId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pCreateFunction != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pReleaseFunction != 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = RegisterService(serviceId, pCreateFunction);
   if (NMCS_STATUS_SUCCESS == status) {
      std::lock_guard<std::recursive_mutex> lock(releaseFunctionsLock_);
      const std::map<runtime::String, RELEASE_SERVICE_FUNCTION>::const_iterator functionIterator = releaseFunctions_.find(serviceId);
      if (functionIterator != releaseFunctions_.end()) {
         releaseFunctions_.erase(functionIterator);
      }
      releaseFunctions_.insert(std::pair<const runtime::String, RELEASE_SERVICE_FUNCTION>(serviceId, pReleaseFunction));
   }
   return status;
}

void ServiceManager::UnregisterService(const runtime::String& serviceId)
{
   NMCS_PRECONDITION(serviceId.Size() > 0);

   std::lock_guard<std::recursive_mutex> lock(createFunctionsLock_);
   const std::map<runtime::String, CREATE_SERVICE_FUNCTION>::const_iterator functionIterator = createFunctions_.find(serviceId);
   if (functionIterator != createFunctions_.end()) {
      createFunctions_.erase(functionIterator);
   }
}

NmcsStatus ServiceManager::AcquireService(const runtime::String& serviceId, IServiceCallback* pCallback, IService*& pService)
{
   NMCS_PRECONDITION_RETURN(serviceId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_FAILURE;

   pService          = 0;
   std::lock_guard<std::recursive_mutex> lock(createFunctionsLock_);
   const std::map<runtime::String, CREATE_SERVICE_FUNCTION>::const_iterator functionIterator = createFunctions_.find(serviceId);
   if (functionIterator != createFunctions_.end()) {
      CREATE_SERVICE_FUNCTION pFactoryFunction = functionIterator->second;
      if (pFactoryFunction != 0) {
         status = (*pFactoryFunction)(pCallback, pService);
      }
   }
   return status;
}

}}} // namespace ultralove::nmcs::server
