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

void FreeUnicodeString(wchar_t** ppUnicodeString, const size_t unicodeStringSize)
{
   NMCS_PRECONDITION(ppUnicodeString != 0);
   NMCS_PRECONDITION(*ppUnicodeString != 0);
   NMCS_PRECONDITION(unicodeStringSize > 0);

   memset((void*)*ppUnicodeString, 0, unicodeStringSize);
   free((void*)*ppUnicodeString);
   *ppUnicodeString = 0;
}

NmcsStatus AnsiStringToUnicodeString(const char* pAnsiString, const size_t ansiStringSize, wchar_t** ppUnicodeString, size_t* pUnicodeStringSize)
{
   NMCS_PRECONDITION_RETURN(pAnsiString != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(ansiStringSize > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(ppUnicodeString != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUnicodeStringSize != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);

   *ppUnicodeString      = 0;
   *pUnicodeStringSize   = 0;

   NmcsStatus status     = NMCS_NMCS_STATUS_FAILURE;
   int unicodeStringSize = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, pAnsiString, (int)ansiStringSize, 0, 0);
   if (unicodeStringSize > 0) {
      wchar_t* pUnicodeString = (wchar_t*)calloc(unicodeStringSize + 1, sizeof(WCHAR));
      if (pUnicodeString != 0) {
         int convertedChars = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, pAnsiString, (int)ansiStringSize, pUnicodeString, unicodeStringSize);
         if (convertedChars > 0) {
            *ppUnicodeString    = pUnicodeString;
            *pUnicodeStringSize = unicodeStringSize;
            status              = NMCS_STATUS_SUCCESS;
         }
         else {
            CSFreeUnicodeString(&pUnicodeString, unicodeStringSize);
            status = NMCS_NMCS_STATUS_FAILURE;
         }
      }
      else {
         status = NMCS_STATUS_OUT_OF_MEMORY;
      }
   }
   return status;
}

void PrintSecErrorA(const char* Description, const long Status)
{
   NMCS_PRECONDITION(Description != 0);

   const size_t DescriptionLength = strlen(Description);
   if (DescriptionLength > 0) {
      LPWSTR UnicodeString       = 0;
      size_t UnicodeStringLength = 0;
      int32_t Status             = AnsiStringToUnicodeString(Description, DescriptionLength, &UnicodeString, &UnicodeStringLength);
      if (NMCS_STATUS_SUCCESS == Status) {
         PrintSecErrorW(UnicodeString, Status);
         FreeUnicodeString(&UnicodeString, UnicodeStringLength);
      }
   }
}

void CSPrintSecErrorW(const wchar_t* pDescription, const long status)
{
   PRECONDITION(pDescription != 0);

   wchar_t* pMessageBuffer  = 0;
   size_t messageBufferSize = FormatMessageW(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 0, status, MAKELCID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (LPWSTR)&pMessageBuffer, 0, 0);
   if (messageBufferSize > 0) {
      std::wcout << pDescription << L", rc = " << status << L", " << pMessageBuffer << std::endl;
      LocalFree(pMessageBuffer);
   }
   pMessageBuffer    = 0;
   messageBufferSize = 0;
}

NmcsStatus CreateCredentialsA(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);

   wchar_t* pServiceIdBuffer      = 0;
   size_t serviceNameBufferLength = 0;
   NmcsStatus status              = AnsiStringToUnicodeString(pServiceId, serviceIdSize, &pServiceIdBuffer, &serviceNameBufferLength);
   if (NMCS_STATUS_SUCCESS == status) {
      wchar_t* pUserIdBuffer       = 0;
      size_t loginNameBufferLength = 0;
      Status                       = AnsiStringToUnicodeString(pUserId, userIdSize, &pUserIdBuffer, &loginNameBufferLength);
      if (NMCS_STATUS_SUCCESS == Status) {
         status = CreateCredentialsW(pServiceIdBuffer, serviceNameBufferLength, pUserIdBuffer, loginNameBufferLength, pSecret, secretSize);
         FreeUnicodeString(&pUserIdBuffer, loginNameBufferLength);
      }
      FreeUnicodeString(&pServiceIdBuffer, serviceNameBufferLength);
   }
   return Status;
}

NmcsStatus CreateCredentialsW(
   const wchar_t* pServiceId, const size_t serviceIdSize, const wchar_t* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pSecret != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(secretSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(secretSize <= CRED_MAX_CREDENTIAL_BLOB_SIZE, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status        = NMCS_STATUS_FAILURE;
   PCREDENTIALW pCredential = {0};
   if (CredReadW(pServiceId, CRED_TYPE_GENERIC, 0, &pCredential) == FALSE) {
      CREDENTIALW Credential        = {0};
      Credential.Type               = CRED_TYPE_GENERIC;
      Credential.TargetName         = (LPWSTR)pServiceId;
      Credential.Comment            = L"ultralove::nmcs::vault";
      Credential.CredentialBlobSize = (DWORD)secretSize;
      Credential.CredentialBlob     = (LPBYTE)pSecret;
      Credential.Persist            = CRED_PERSIST_LOCAL_MACHINE;
      Credential.UserName           = (LPWSTR)pUserId;
      if (CredWriteW(&pCredential, 0) != FALSE) {
         status = NMCS_STATUS_SUCCESS;
      }
      else {
         PrintSecErrorW(L"CredWrite failed", GetLastError());
         status = NMCS_STATUS_FAILURE;
      }
   }
   else {
      CredFree(pCredential);
      pCredential = 0;
      CSPrintSecErrorW(L"CredWrite failed", ERROR_ALREADY_EXISTS);
      status = NMCS_STATUS_ALREADY_EXISTS;
   }
   return status;
}

NmcsStatus
ReadCredentialsA(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, void** ppSecret, size_t* pSecretSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);

   wchar_t* pServiceIdBuffer      = 0;
   size_t serviceNameBufferLength = 0;
   NmcsStatus status              = AnsiStringToUnicodeString(pServiceId, serviceIdSize, &pServiceIdBuffer, &serviceNameBufferLength);
   if (NMCS_STATUS_SUCCESS == status) {
      wchar_t* pUserIdBuffer       = 0;
      size_t loginNameBufferLength = 0;
      status                       = AnsiStringToUnicodeString(pUserId, userIdSize, &pUserIdBuffer, &loginNameBufferLength);
      if (NMCS_STATUS_SUCCESS == status) {
         status = ReadCredentialsW(pServiceIdBuffer, serviceNameBufferLength, pUserIdBuffer, loginNameBufferLength, ppSecret, pSecretSize);
         FreeUnicodeString(&pUserIdBuffer, loginNameBufferLength);
      }
      FreeUnicodeString(&pServiceIdBuffer, serviceNameBufferLength);
   }
   return status;
}

NmcsStatus
ReadCredentialsW(const wchar_t* pServiceId, const size_t serviceIdSize, const wchar_t* pUserId, const size_t userIdSize, void** ppSecret, size_t* pSecretSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(ppSecret != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pSecretSize != NULL, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus Status        = NMCS_STATUS_FAILURE;
   *ppSecret                = 0;
   *pSecretSize             = 0;
   PCREDENTIALW pCredential = {0};
   if (CredReadW(ServiceName, CRED_TYPE_GENERIC, 0, &pCredential) != FALSE) {
      status = AllocPassword(ppSecret, pCredential->CredentialBlobSize);
      if (NMCS_STATUS_SUCCESS == status) {
         memmove(*ppSecret, pCredential->CredentialBlob, pCredential->CredentialBlobSize);
         *pSecretSize = pCredential->CredentialBlobSize;
         status       = NMCS_STATUS_SUCCESS;
      }
      CredFree(pCredential);
      pCredential = 0;
   }
   else {
      const long result = GetLastError();
      if (ERROR_NOT_FOUND == result) {
         Status = NMCS_STATUS_NOT_FOUND;
      }
      else {
         status = NMCS_STATUS_FAILURE;
      }
   }
   return status;
}

NmcsStatus UpdateCredentialsA(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != NULL, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != NULL, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);

   wchar_t* pServiceIdBuffer      = 0;
   size_t serviceNameBufferLength = 0;
   NmcsStatus status              = AnsiStringToUnicodeString(pServiceId, serviceIdSize, &pServiceIdBuffer, &serviceNameBufferLength);
   if (NMCS_STATUS_SUCCESS == status) {
      wchar_t* pUserIdBuffer       = 0;
      size_t loginNameBufferLength = 0;
      status                       = AnsiStringToUnicodeString(pUserId, userIdSize, &pUserIdBuffer, &loginNameBufferLength);
      if (NMCS_STATUS_SUCCESS == status) {
         status = UpdateCredentialsW(pServiceIdBuffer, serviceNameBufferLength, pUserIdBuffer, loginNameBufferLength, pSecret, secretSize);
         FreeUnicodeString(&pUserIdBuffer, loginNameBufferLength);
      }
      FreeUnicodeString(&pServiceIdBuffer, serviceNameBufferLength);
   }
   return status;
}

NmcsStatus UpdateCredentialsW(
   const wchar_t* pServiceId, const size_t serviceIdSize, const wchar_t* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pSecret != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(secretSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(secretSize <= CRED_MAX_CREDENTIAL_BLOB_SIZE, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status        = NMCS_STATUS_FAILURE;
   PCREDENTIALW pCredential = {0};
   if (CredReadW(pServiceId, CRED_TYPE_GENERIC, 0, &pCredential) != FALSE) {
      CredFree(pCredential);
      pCredential                   = 0;
      CREDENTIALW Credential        = {0};
      Credential.Type               = CRED_TYPE_GENERIC;
      Credential.TargetName         = (LPWSTR)pServiceId;
      Credential.Comment            = L"ultralove::nmcs::vault";
      Credential.CredentialBlobSize = (DWORD)secretSize;
      Credential.CredentialBlob     = (LPBYTE)pSecret;
      Credential.Persist            = CRED_PERSIST_LOCAL_MACHINE;
      Credential.UserName           = (LPWSTR)pUserId;

      if (CredWriteW(&Credential, 0) != FALSE) {
         status = NMCS_STATUS_SUCCESS;
      }
      else {
         status = NMCS_STATUS_FAILURE;
      }
   }
   else {
      status = NMCS_STATUS_NOT_FOUND;
   }
   return status;
}

NmcsStatus DeleteCredentialsA(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != NULL, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != NULL, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);

   wchar_t* pServiceIdBuffer      = 0;
   size_t serviceNameBufferLength = 0;
   NmcsStatus status              = AnsiStringToUnicodeString(pServiceId, serviceIdSize, &pServiceIdBuffer, &serviceNameBufferLength);
   if (NMCS_STATUS_SUCCESS == status) {
      wchar_t* pUserIdBuffer       = 0;
      size_t loginNameBufferLength = 0;
      status                       = AnsiStringToUnicodeString(pUserId, userIdSize, &pUserIdBuffer, &loginNameBufferLength);
      if (NMCS_STATUS_SUCCESS == status) {
         status = DeleteCredentialsW(pServiceIdBuffer, serviceNameBufferLength, pUserIdBuffer, loginNameBufferLength);
         FreeUnicodeString(&pUserIdBuffer, loginNameBufferLength);
      }
      FreeUnicodeString(&pServiceIdBuffer, serviceNameBufferLength);
   }
   return status;
}

NmcsStatus DeleteCredentialsW(const wchar_t* pServiceId, const size_t serviceIdSize, const wchar_t* pUserId, const size_t userIdSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != NULL, STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != NULL, STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, STATUS_INVALID_PARAMETER);

   NmcsStatus status = STATUS_FAILURE;
   if (CredDeleteW(pServiceId, CRED_TYPE_GENERIC, 0) != FALSE) {
      status = NMCS_STATUS_SUCCESS;
   }
   else {
      const long result = GetLastError();
      if (ERROR_NOT_FOUND == result) {
         status = NMCS_STATUS_NOT_FOUND;
      }
      else {
         status = NMCS_STATUS_FAILURE;
      }
   }
   return status;
}

NmcsStatus AllocSecret(void** ppSecret, const size_t secretSize)
{
   NMCS_PRECONDITION_RETURN(ppSecret != 0, NMCS_NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(*ppSecret == 0, NMCS_NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(secretSize > 0, NMCS_NMCS_NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_NMCS_STATUS_FAILURE;
   *ppSecret         = calloc(secretSize, sizeof(char));
   if (*ppSecret != 0) {
      status = NMCS_STATUS_SUCCESS;
   }
   else {
      status = NMCS_STATUS_OUT_OF_MEMORY;
   }
   return status;
}

void ReleaseSecret(void** ppSecret, const size_t secretSize)
{
   NMCS_PRECONDITION(ppSecret != 0);
   NMCS_PRECONDITION(*ppSecret != 0);
   NMCS_PRECONDITION(secretSize > 0);

   memset(*ppSecret, 0, secretSize);
   free(*ppSecret);
   *ppSecret = 0;
}

}}} // namespace ultralove::nmcs::platform
