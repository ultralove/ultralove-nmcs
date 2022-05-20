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

void FreeUnicodeString(wchar_t** ppUnicodeString, const size_t unicodeStringLength)
{
   NMCS_PRECONDITION(ppUnicodeString != 0);
   NMCS_PRECONDITION(*ppUnicodeString != 0);
   NMCS_PRECONDITION(unicodeStringLength > 0);

   memset((void*)*ppUnicodeString, 0, unicodeStringLength);
   free((void*)*ppUnicodeString);
   *ppUnicodeString = 0;
}

NmcsStatus AnsiStringToUnicodeString(const char* pAnsiString, const size_t ansiStringLength, wchar_t** ppUnicodeString, size_t* pUnicodeStringLength)
{
   NMCS_PRECONDITION_RETURN(pAnsiString != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(ansiStringLength > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(ppUnicodeString != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUnicodeStringLength != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);

   *ppUnicodeString        = 0;
   *pUnicodeStringLength   = 0;

   NmcsStatus status       = NMCS_NMCS_STATUS_FAILURE;
   int unicodeStringLength = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, pAnsiString, (int)ansiStringLength, 0, 0);
   if (unicodeStringLength > 0) {
      wchar_t* pUnicodeString = (wchar_t*)calloc(unicodeStringLength + 1, sizeof(WCHAR));
      if (pUnicodeString != 0) {
         int convertedChars = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, pAnsiString, (int)ansiStringLength, pUnicodeString, unicodeStringLength);
         if (convertedChars > 0) {
            *ppUnicodeString      = pUnicodeString;
            *pUnicodeStringLength = unicodeStringLength;
            status                = NMCS_STATUS_SUCCESS;
         }
         else {
            CSFreeUnicodeString(&pUnicodeString, unicodeStringLength);
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
   const char* pServiceName, const size_t serviceNameLength, const char* pLoginName, const size_t loginNameLength, const void* pPassword,
   const size_t passwordLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);

   wchar_t* pServiceNameBuffer    = 0;
   size_t serviceNameBufferLength = 0;
   NmcsStatus status              = AnsiStringToUnicodeString(pServiceName, serviceNameLength, &pServiceNameBuffer, &serviceNameBufferLength);
   if (NMCS_STATUS_SUCCESS == status) {
      wchar_t* pLoginNameBuffer    = 0;
      size_t loginNameBufferLength = 0;
      Status                       = AnsiStringToUnicodeString(pLoginName, loginNameLength, &pLoginNameBuffer, &loginNameBufferLength);
      if (NMCS_STATUS_SUCCESS == Status) {
         status = CreateCredentialsW(pServiceNameBuffer, serviceNameBufferLength, pLoginNameBuffer, loginNameBufferLength, pPassword, passwordLength);
         FreeUnicodeString(&pLoginNameBuffer, loginNameBufferLength);
      }
      FreeUnicodeString(&pServiceNameBuffer, serviceNameBufferLength);
   }
   return Status;
}

NmcsStatus CreateCredentialsW(
   const wchar_t* pServiceName, const size_t serviceNameLength, const wchar_t* pLoginName, const size_t loginNameLength, const void* pPassword,
   const size_t passwordLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pPassword != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(passwordLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(passwordLength <= CRED_MAX_CREDENTIAL_BLOB_SIZE, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status        = NMCS_STATUS_FAILURE;
   PCREDENTIALW pCredential = {0};
   if (CredReadW(pServiceName, CRED_TYPE_GENERIC, 0, &pCredential) == FALSE) {
      CREDENTIALW Credential        = {0};
      Credential.Type               = CRED_TYPE_GENERIC;
      Credential.TargetName         = (LPWSTR)pServiceName;
      Credential.Comment            = L"ultralove::nmcs::vault";
      Credential.CredentialBlobSize = (DWORD)passwordLength;
      Credential.CredentialBlob     = (LPBYTE)pPassword;
      Credential.Persist            = CRED_PERSIST_LOCAL_MACHINE;
      Credential.UserName           = (LPWSTR)pLoginName;
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

NmcsStatus ReadCredentialsA(
   const char* pServiceName, const size_t serviceNameLength, const char* pLoginName, const size_t loginNameLength, void** ppPassword, size_t* pPasswordLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);

   wchar_t* pServiceNameBuffer    = 0;
   size_t serviceNameBufferLength = 0;
   NmcsStatus status              = AnsiStringToUnicodeString(pServiceName, serviceNameLength, &pServiceNameBuffer, &serviceNameBufferLength);
   if (NMCS_STATUS_SUCCESS == status) {
      wchar_t* pLoginNameBuffer    = 0;
      size_t loginNameBufferLength = 0;
      status                       = AnsiStringToUnicodeString(pLoginName, loginNameLength, &pLoginNameBuffer, &loginNameBufferLength);
      if (NMCS_STATUS_SUCCESS == status) {
         status = ReadCredentialsW(pServiceNameBuffer, serviceNameBufferLength, pLoginNameBuffer, loginNameBufferLength, ppPassword, pPasswordLength);
         FreeUnicodeString(&pLoginNameBuffer, loginNameBufferLength);
      }
      FreeUnicodeString(&pServiceNameBuffer, serviceNameBufferLength);
   }
   return status;
}

NmcsStatus ReadCredentialsW(
   const wchar_t* pServiceName, const size_t serviceNameLength, const wchar_t* pLoginName, const size_t loginNameLength, void** ppPassword,
   size_t* pPasswordLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(ppPassword != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pPasswordLength != NULL, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus Status        = NMCS_STATUS_FAILURE;
   *ppPassword              = 0;
   *pPasswordLength         = 0;
   PCREDENTIALW pCredential = {0};
   if (CredReadW(ServiceName, CRED_TYPE_GENERIC, 0, &pCredential) != FALSE) {
      status = AllocPassword(ppPassword, pCredential->CredentialBlobSize);
      if (NMCS_STATUS_SUCCESS == status) {
         memmove(*ppPassword, pCredential->CredentialBlob, pCredential->CredentialBlobSize);
         *pPasswordLength = pCredential->CredentialBlobSize;
         status           = NMCS_STATUS_SUCCESS;
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
   const char* pServiceName, const size_t serviceNameLength, const char* pLoginName, const size_t loginNameLength, const void* pPassword,
   const size_t passwordLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != NULL, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != NULL, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);

   wchar_t* pServiceNameBuffer    = 0;
   size_t serviceNameBufferLength = 0;
   NmcsStatus status              = AnsiStringToUnicodeString(pServiceName, serviceNameLength, &pServiceNameBuffer, &serviceNameBufferLength);
   if (NMCS_STATUS_SUCCESS == status) {
      wchar_t* pLoginNameBuffer    = 0;
      size_t loginNameBufferLength = 0;
      status                       = AnsiStringToUnicodeString(pLoginName, loginNameLength, &pLoginNameBuffer, &loginNameBufferLength);
      if (NMCS_STATUS_SUCCESS == status) {
         status = UpdateCredentialsW(pServiceNameBuffer, serviceNameBufferLength, pLoginNameBuffer, loginNameBufferLength, pPassword, passwordLength);
         FreeUnicodeString(&pLoginNameBuffer, loginNameBufferLength);
      }
      FreeUnicodeString(&pServiceNameBuffer, serviceNameBufferLength);
   }
   return status;
}

NmcsStatus UpdateCredentialsW(
   const wchar_t* pServiceName, const size_t serviceNameLength, const wchar_t* pLoginName, const size_t loginNameLength, const void* pPassword,
   const size_t passwordLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pPassword != NULL, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(passwordLength > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(passwordLength <= CRED_MAX_CREDENTIAL_BLOB_SIZE, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status        = NMCS_STATUS_FAILURE;
   PCREDENTIALW pCredential = {0};
   if (CredReadW(pServiceName, CRED_TYPE_GENERIC, 0, &pCredential) != FALSE) {
      CredFree(pCredential);
      pCredential                   = 0;
      CREDENTIALW Credential        = {0};
      Credential.Type               = CRED_TYPE_GENERIC;
      Credential.TargetName         = (LPWSTR)pServiceName;
      Credential.Comment            = L"ultralove::nmcs::vault";
      Credential.CredentialBlobSize = (DWORD)passwordLength;
      Credential.CredentialBlob     = (LPBYTE)pPassword;
      Credential.Persist            = CRED_PERSIST_LOCAL_MACHINE;
      Credential.UserName           = (LPWSTR)pLoginName;

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

NmcsStatus DeleteCredentialsA(const char* pServiceName, const size_t serviceNameLength, const char* pLoginName, const size_t loginNameLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != NULL, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != NULL, NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, NMCS_NMCS_STATUS_INVALID_PARAMETER);

   wchar_t* pServiceNameBuffer    = 0;
   size_t serviceNameBufferLength = 0;
   NmcsStatus status              = AnsiStringToUnicodeString(pServiceName, serviceNameLength, &pServiceNameBuffer, &serviceNameBufferLength);
   if (NMCS_STATUS_SUCCESS == status) {
      wchar_t* pLoginNameBuffer    = 0;
      size_t loginNameBufferLength = 0;
      status                       = AnsiStringToUnicodeString(pLoginName, loginNameLength, &pLoginNameBuffer, &loginNameBufferLength);
      if (NMCS_STATUS_SUCCESS == status) {
         status = DeleteCredentialsW(pServiceNameBuffer, serviceNameBufferLength, pLoginNameBuffer, loginNameBufferLength);
         FreeUnicodeString(&pLoginNameBuffer, loginNameBufferLength);
      }
      FreeUnicodeString(&pServiceNameBuffer, serviceNameBufferLength);
   }
   return status;
}

NmcsStatus DeleteCredentialsW(const wchar_t* pServiceName, const size_t serviceNameLength, const wchar_t* pLoginName, const size_t loginNameLength)
{
   NMCS_PRECONDITION_RETURN(pServiceName != NULL, STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceNameLength > 0, STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pLoginName != NULL, STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(loginNameLength > 0, STATUS_INVALID_PARAMETER);

   NmcsStatus status = STATUS_FAILURE;
   if (CredDeleteW(pServiceName, CRED_TYPE_GENERIC, 0) != FALSE) {
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

NmcsStatus AllocPassword(void** ppPassword, const size_t passwordLength)
{
   NMCS_PRECONDITION_RETURN(ppPassword != 0, NMCS_NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(*ppPassword == 0, NMCS_NMCS_NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(passwordLength > 0, NMCS_NMCS_NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_NMCS_STATUS_FAILURE;
   *ppPassword       = calloc(passwordLength, sizeof(char));
   if (*ppPassword != 0) {
      status = NMCS_STATUS_SUCCESS;
   }
   else {
      status = NMCS_STATUS_OUT_OF_MEMORY;
   }
   return status;
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
