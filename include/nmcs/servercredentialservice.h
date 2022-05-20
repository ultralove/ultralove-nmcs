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

#ifndef __NMCS_SERVER_CREDENTIAL_SERVICE_H_INCL__
#define __NMCS_SERVER_CREDENTIAL_SERVICE_H_INCL__

#include <nmcs/serverservice.h>

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace server {

class NMCS_SHARED_API ICredentialService : public IService
{
   virtual NmcsStatus CreateCredentials(const runtime::String& serviceId, const runtime::String& userId, const runtime::String& secret) = 0;

   virtual NmcsStatus ReadCredentials(const runtime::String& serviceId, const runtime::String& userId, runtime::String& secret)         = 0;

   virtual NmcsStatus UpdateCredentials(const runtime::String& serviceId, const runtime::String& userId, const runtime::String& secret) = 0;

   virtual NmcsStatus DeleteCredentials(const runtime::String& serviceId)                                                               = 0;

protected:
   virtual ~ICredentialService() {}
};

}}} // namespace ultralove::nmcs::server

#pragma pack(pop)

#endif // #ifndef __NMCS_CREDENTIAL_FILE_SERVICE_H_INCL__
