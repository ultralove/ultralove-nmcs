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

#ifndef __NMCS_MACROS_H_INCL__
#define __NMCS_MACROS_H_INCL__

#include <cstring>

#define NMCS_STRING0(__str__)                     #__str__
#define NMCS_STRING(__str__)                      NMCS_STRING0(__str__)
#define NMCS_MESSAGE(__desc__)                    message(__FILE__ "(" NMCS_STRING(__LINE__) "):" #__desc__)

#define NMCS_IN_RANGE(__low__, __num__, __high__) (((__low__) <= (__num__)) && ((__num__) <= (__high__)))

template<class __value__, class __multiple__> inline __value__ NMCS_ROUND_DOWN(__value__ __v__, __multiple__ __m__)
{
   return ((__v__ / __m__) * __m__);
}
template<class __value__, class __multiple__> inline __value__ NMCS_ROUND_UP(__value__ __v__, __multiple__ __m__)
{
   return (NMCS_ROUND_DOWN(__v__, __m__) + (((__v__ % __m__) > 0) ? __m__ : 0));
}

#define NMCS_STRING_SIZE(__str__) ((strlen(__str__) + 1) * sizeof(char))
#define NMCS_ARRAY_SIZE(__a__)    (sizeof(__a__) / sizeof(__a__[0]))

#endif // #ifndef __NMCS_MACROS_H_INCL__
