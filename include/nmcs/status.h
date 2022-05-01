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

#ifndef __NMCS_STATUS_H_INCL__
#define __NMCS_STATUS_H_INCL__

#include <cstdint>

typedef uint32_t NmcsStatus;
#define NMCS_MAKE_STATUS_CODE(__severity__, __facility__, __code__) ((uint32_t)((__severity__) | (__facility__ << 16) | (__code__ << 0)))

#define NMCS_SEVERITY_SUCCESS                                       0
#define NMCS_SEVERITY_WARNING                                       1
#define NMCS_SEVERITY_ERROR                                         2
#define NMCS_SEVERITY_FATAL_EROR                                    3

#define NMCS_STATUS_SUCCESS                                         NMCS_MAKE_STATUS_CODE(NMCS_SEVERITY_SUCCESS, 0, 0x00000000)
#define NMCS_STATUS_FAILURE                                         NMCS_MAKE_STATUS_CODE(NMCS_SEVERITY_ERROR, 0, 0x00000001)
#define NMCS_STATUS_NOT_FOUND                                       NMCS_MAKE_STATUS_CODE(NMCS_SEVERITY_ERROR, 0, 0x00000002)
#define NMCS_STATUS_INVALID_PARAMETER                               NMCS_MAKE_STATUS_CODE(NMCS_SEVERITY_ERROR, 0, 0x00000003)
#define NMCS_STATUS_NOT_IMPLEMENTED                                 NMCS_MAKE_STATUS_CODE(NMCS_SEVERITY_ERROR, 0, 0x00000004)
#define NMCS_STATUS_ALREADY_REGISTERED                              NMCS_MAKE_STATUS_CODE(NMCS_SEVERITY_ERROR, 0, 0x00000005)
#define NMCS_STATUS_OUT_OF_MEMORY                                   NMCS_MAKE_STATUS_CODE(NMCS_SEVERITY_ERROR, 0, 0x00000006)

#define NMCS_SUCCEEDED(__status__)                                  (NMCS_STATUS_SUCCESS == (__status__))
#define NMCS_FAILED(__status__)                                     (NMCS_STATUS_SUCCESS != (__status__))

typedef uint32_t NmcsStatus;

#endif // #ifndef __NMCS_STATUS_H_INCL__
