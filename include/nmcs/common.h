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

#ifndef __NMCS_COMMON_H_INCL__
#define __NMCS_COMMON_H_INCL__

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <iomanip>
#include <sstream>
#include <string>

#include "version.h"

#include <nmcs/macros.h>
#include <nmcs/status.h>

#ifdef _MSC_VER
   #ifdef NMCS_SHARED
      #define NMCS_SHARED_API __declspec(dllexport)
   #else
      #define NMCS_SHARED_API __declspec(dllimport)
   #endif
#else
   #ifdef __GNUC__
      #ifdef NMCS_SHARED
         #define NMCS_SHARED_API __attribute__((visibility("default")))
      #else
         #define NMCS_SHARED_API
      #endif
   #endif
#endif

typedef uint32_t NmcsStatus;

#define NMCS_PRECONDITION(__nmcs_condition__) \
   if (false == (__nmcs_condition__)) {       \
      return;                                 \
   }

#define NMCS_PRECONDITION_RETURN(__nmcs_condition__, __nmcs_return__) \
   if (false == (__nmcs_condition__)) {                               \
      return (__nmcs_return__);                                       \
   }

namespace ultralove { namespace nmcs {

#pragma pack(push)
#pragma pack(8)

template<class T> inline static T* SafeAlloc()
{
   T* ptr = new T();
   if (ptr != 0) {
      memset(ptr, 0, sizeof(T));
   }

   return ptr;
}

template<class T> inline static T* SafeAllocArray(const size_t itemCount)
{
   T* ptr = 0;
   if (itemCount > 0) {
      ptr = new T[itemCount]();
      if (ptr != 0) {
         memset(ptr, 0, sizeof(T) * itemCount);
      }
   }

   return ptr;
}

template<class T> inline static void SafeDelete(T*& ptr)
{
   delete ptr;
   ptr = 0;
}

template<class T> inline static void SafeDeleteArray(T*& ptr)
{
   delete[] ptr;
   ptr = 0;
}

}} // namespace ultralove::nmcs

inline static const char* NmcsVersion()
{
   return NMCS_VERSION;
}

inline static const char* NmcsBuildId()
{
   return NMCS_BUILD_ID;
}

inline static const char* NmcsBuildString()
{
   return NMCS_BUILD_STRING;
}

#pragma pack(pop)

#endif // #ifndef __NMCS_COMMON_H_INCL__
