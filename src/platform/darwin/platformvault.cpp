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
#include <nmcs/platformalloc.h>
#include <nmcs/platformvault.h>

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <Security/Security.h>

namespace ultralove { namespace nmcs { namespace platform {

NmcsStatus GetCredentialsErrorString(char** ppErrorString, const OSStatus systemStatus)
{
   NMCS_PRECONDITION_RETURN(ppErrorString != 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status        = NMCS_STATUS_FAILURE;
   CFStringRef errorMessage = SecCopyErrorMessageString(systemStatus, 0);
   if (errorMessage != 0) {
      CFIndex minBufferLength = CFStringGetLength(errorMessage);
      CFIndex maxBufferLength = CFStringGetMaximumSizeForEncoding(minBufferLength, kCFStringEncodingUTF8) + 1;
      char* pBuffer           = (char*)Alloc(maxBufferLength * sizeof(char));
      if (pBuffer != 0) {
         if (CFStringGetCString(errorMessage, pBuffer, maxBufferLength, kCFStringEncodingUTF8) != FALSE) {
            *ppErrorString = pBuffer;
            status         = NMCS_STATUS_SUCCESS;
         }
         else {
            status = NMCS_STATUS_NOT_FOUND;
         }
      }
      else {
         status = NMCS_STATUS_OUT_OF_MEMORY;
      }
      CFRelease(errorMessage);
      errorMessage = 0;
   }
   else {
      status = NMCS_STATUS_NOT_FOUND;
   }
   return status;
}

NmcsStatus CreateCredentials(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pSecret != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(secretSize > 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status = NMCS_STATUS_FAILURE;
   OSStatus result   = SecKeychainAddGenericPassword(0, (UInt32)serviceIdSize, pServiceId, (UInt32)userIdSize, pUserId, (UInt32)secretSize, pSecret, 0);
   if (errSecSuccess == result) {
      status = NMCS_STATUS_SUCCESS;
   }
   else if (errSecDuplicateItem == result) {
      status = NMCS_STATUS_ALREADY_EXISTS;
   }
   else {
      status = NMCS_STATUS_FAILURE;
   }
   return status;
}

NmcsStatus
ReadCredentials(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, void** ppSecret, size_t* pSecretSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(ppSecret != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pSecretSize != 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status       = NMCS_STATUS_FAILURE;
   *pSecretSize            = 0;
   *ppSecret               = 0;
   void* pSecretBuffer     = 0;
   SecKeychainItemRef item = 0;
   OSStatus result =
      SecKeychainFindGenericPassword(0, (UInt32)serviceIdSize, pServiceId, (UInt32)userIdSize, pUserId, (UInt32*)pSecretSize, &pSecretBuffer, &item);
   if (errSecSuccess == result) {
      status = AllocSecret(ppSecret, *pSecretSize);
      if ((NMCS_STATUS_SUCCESS == status) && (*ppSecret != 0)) {
         memmove(*ppSecret, pSecretBuffer, *pSecretSize);
         status = NMCS_STATUS_SUCCESS;
      }
      SecKeychainItemFreeContent(0, pSecretBuffer);
      pSecretBuffer = 0;

      CFRelease(item);
      item = 0;
   }
   else if (errSecItemNotFound == result) {
      status = NMCS_STATUS_NOT_FOUND;
   }
   else {
      status = NMCS_STATUS_FAILURE;
   }
   return status;
}

NmcsStatus UpdateCredentials(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pSecret != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(secretSize > 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status       = NMCS_STATUS_FAILURE;
   SecKeychainItemRef item = 0;
   OSStatus result         = SecKeychainFindGenericPassword(0, (UInt32)serviceIdSize, pServiceId, (UInt32)userIdSize, pUserId, 0, 0, &item);
   if (errSecSuccess == result) {
      result = SecKeychainItemModifyAttributesAndData(item, 0, (UInt32)secretSize, pSecret);
      if (errSecSuccess == result) {
         status = NMCS_STATUS_SUCCESS;
      }
      else {
         status = NMCS_STATUS_FAILURE;
      }
   }
   else if (errSecItemNotFound == result) {
      status = NMCS_STATUS_NOT_FOUND;
   }
   else {
      status = NMCS_STATUS_FAILURE;
   }
   return status;
}

NmcsStatus DeleteCredentials(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize)
{
   NMCS_PRECONDITION_RETURN(pServiceId != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(serviceIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(pUserId != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(userIdSize > 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus status       = NMCS_STATUS_FAILURE;
   SecKeychainItemRef item = 0;
   OSStatus result         = SecKeychainFindGenericPassword(0, (UInt32)serviceIdSize, pServiceId, (UInt32)userIdSize, pUserId, 0, 0, &item);
   if (errSecSuccess == result) {
      result = SecKeychainItemDelete(item);
      if (errSecSuccess == result) {
         status = NMCS_STATUS_SUCCESS;
      }
      else {
         status = NMCS_STATUS_FAILURE;
      }
   }
   else if (errSecItemNotFound == result) {
      status = NMCS_STATUS_NOT_FOUND;
   }
   else {
      status = NMCS_STATUS_FAILURE;
   }
   return status;
}

NmcsStatus AllocSecret(void** ppSecret, const size_t secretSize)
{
   NMCS_PRECONDITION_RETURN(ppSecret != 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(*ppSecret == 0, NMCS_STATUS_INVALID_PARAMETER);
   NMCS_PRECONDITION_RETURN(secretSize > 0, NMCS_STATUS_INVALID_PARAMETER);

   NmcsStatus Status = NMCS_STATUS_FAILURE;
   *ppSecret         = calloc(secretSize, sizeof(char));
   if (*ppSecret != 0) {
      Status = NMCS_STATUS_SUCCESS;
   }
   else {
      Status = NMCS_STATUS_OUT_OF_MEMORY;
   }
   return Status;
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
