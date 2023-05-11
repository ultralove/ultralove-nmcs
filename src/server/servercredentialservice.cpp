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

#include "serverservicefactory.h"
#include "serverserviceresource.h"

#include <nmcs/platformvault.h>
#include <nmcs/servercredentialservice.h>

namespace ultralove { namespace nmcs { namespace server {

class CredentialService : public ICredentialService
{
public:
   static NmcsStatus CreateService(IServiceCallback*, IService*& pService)
   {
      pService = new CredentialService();
      return NMCS_STATUS_SUCCESS;
   }

   virtual NmcsStatus CreateCredentials(const runtime::String& serviceId, const runtime::String& userId, const runtime::String& secret)
   {
      NMCS_PRECONDITION_RETURN(serviceId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);
      NMCS_PRECONDITION_RETURN(userId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);
      NMCS_PRECONDITION_RETURN(secret.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);

      NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
      return status;
   }

   virtual NmcsStatus ReadCredentials(const runtime::String& serviceId, const runtime::String& userId, runtime::String& secret)
   {
      NMCS_PRECONDITION_RETURN(serviceId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);
      NMCS_PRECONDITION_RETURN(userId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);

      NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
      return status;
   }

   virtual NmcsStatus UpdateCredentials(const runtime::String& serviceId, const runtime::String& userId, const runtime::String& secret)
   {
      NMCS_PRECONDITION_RETURN(serviceId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);
      NMCS_PRECONDITION_RETURN(userId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);
      NMCS_PRECONDITION_RETURN(secret.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);

      NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
      return status;
   }

   virtual NmcsStatus DeleteCredentials(const runtime::String& serviceId)
   {
      NMCS_PRECONDITION_RETURN(serviceId.Size() > 0, NMCS_STATUS_INVALID_PARAMETER);

      NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
      return status;
   }

protected:
   virtual ~CredentialService() {}

private:
   CredentialService() {}
};

static ServiceResource<CredentialService> resource("nmcs::credentialService");

}}} // namespace ultralove::nmcs::server
