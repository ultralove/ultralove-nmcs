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

#include <nmcs/platform.h>
#include <nmcs/platformvault.h>

namespace ultralove { namespace nmcs { namespace platform {

NmcsStatus GetCredentialsErrorString(char** ppErrorString, const OSStatus systemStatus)
{
   NMCS_PRECONDITION_RETURN(ppErrorString != 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
   return status;
}

NmcsStatus CreateCredentials(
   const char* pServiceName, const size_t serviceNameLength, const char* pLoginName, const size_t loginNameLength, const void* pPassword,
   const size_t passwordLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pPassword != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(passwordLength > 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
   return status;
}

NmcsStatus ReadCredentials(
   const char* pServiceName, const size_t serviceNameLength, const char* pLoginName, const size_t loginNameLength, void** ppPassword, size_t* pPasswordLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(ppPassword != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pPasswordLength != 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
   return status;
}

NmcsStatus UpdateCredentials(
   const char* pServiceName, const size_t serviceNameLength, const char* pLoginName, const size_t loginNameLength, const void* pPassword,
   const size_t passwordLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pPassword != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(passwordLength > 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
   return status;
}

NmcsStatus DeleteCredentials(const char* pServiceName, const size_t serviceNameLength, const char* pLoginName, const size_t loginNameLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_NOT_IMPLEMENTED;
   return status;
}

NmcsStatus AllocPassword(void** ppPassword, const size_t passwordLength)
{
   NMCS_PRECONDITION_RETURN(ppPassword != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(*ppPassword == 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(passwordLength > 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus Status = NMCS_STATUS_FAILURE;
   *ppPassword       = calloc(passwordLength, sizeof(char));
   if (*ppPassword != 0) {
      Status = NMCS_STATUS_SUCCESS;
   }
   else {
      Status = NMCS_STATUS_OUT_OF_MEMORY;
   }
   return Status;
}

void ReleasePassword(void** ppPassword, const size_t passwordLength)
{
   NMCS_PRECONDITION(ppPassword != 0);
   NMCS_PRECONDITION(*ppPassword != 0);
   NMCS_PRECONDITION(passwordLength > 0);

   memset(*ppPassword, 0, passwordLength);
   free(*ppPassword);
   *ppPassword = 0;
}

}}} // namespace ultralove::nmcs::platform
