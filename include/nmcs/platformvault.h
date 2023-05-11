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

#ifndef __NMCS_PLATFORM_VAULT_H_INCL__
#define __NMCS_PLATFORM_VAULT_H_INCL__

#include <nmcs/common.h>

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace platform {

#ifdef _WIN32
NMCS_SHARED_API NmcsStatus CreateCredentialsA(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize);
NMCS_SHARED_API NmcsStatus
ReadCredentialsA(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, void** ppSecret, size_t* pSecretLength);
NMCS_SHARED_API NmcsStatus UpdateCredentialsA(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize);
NMCS_SHARED_API NmcsStatus DeleteCredentialsA(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize);
NMCS_SHARED_API NmcsStatus CreateCredentialsW(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize);
NMCS_SHARED_API NmcsStatus
ReadCredentialsW(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, void** ppSecret, size_t* pSecretSize);
NMCS_SHARED_API NmcsStatus UpdateCredentialsW(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize);
NMCS_SHARED_API NmcsStatus DeleteCredentialsW(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize);
NMCS_SHARED_API NmcsStatus AllocSecret(void** ppSecret, const size_t secretSize);
NMCS_SHARED_API void ReleaseSecret(void** ppSecret, const size_t secretSize);
#else
NMCS_SHARED_API NmcsStatus CreateCredentials(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize);
NMCS_SHARED_API NmcsStatus
ReadCredentials(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, void** ppSecret, size_t* pSecretSize);
NMCS_SHARED_API NmcsStatus UpdateCredentials(
   const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize, const void* pSecret, const size_t secretSize);
NMCS_SHARED_API NmcsStatus DeleteCredentials(const char* pServiceId, const size_t serviceIdSize, const char* pUserId, const size_t userIdSize);
NMCS_SHARED_API NmcsStatus AllocSecret(void** ppSecret, const size_t secretSize);
NMCS_SHARED_API void ReleaseSecret(void** ppSecret, const size_t secretSize);
#endif
}}} // namespace ultralove::nmcs::platform

#pragma pack(pop)

#endif // #ifndef __NMCS_PLATFORM_VAULT_H_INCL__
