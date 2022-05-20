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

#ifndef __NMCS_NATIVE_BRIDGE_H_INCL__
#define __NMCS_NATIVE_BRIDGE_H_INCL__

#pragma pack(push)
#pragma pack(8)

#include <stdint.h>

#define _IN
#define _OUT
#define _INOUT

typedef uint32_t NMCS_STATUS;

typedef enum _tag_NMCS_ENCODING
{
   NMCS_LATIN1_ENCODING   = 0,
   NMCS_UTF8_ENCODING     = 1,
   NMCS_UTF16_ENCODING    = 2,
   NMCS_UTF16_LE_ENCODING = 3,
   NMCS_UTF16_BE_ENCODING = 4,
   NMCS_UTF32_ENCODING    = 5,
   NMCS_MAX_ENCODING      = NMCS_UTF32_ENCODING,
   NMCS_INVALID_ENCODING  = NMCS_MAX_ENCODING + 1
} NMCS_ENCODING;

typedef struct _tag_NMCS_STRING
{
   NMCS_ENCODING Encoding;
   size_t Size;
   uint8_t* Data;
} NMCS_STRING, *PNMCS_STRING, **PPNMCS_STRING;

NMCS_STATUS
NmcsAllocString(_IN const uint8_t* pData, _IN const size_t Size, _OUT PPNMCS_STRING ppString);
void NmcsReleaseString(_INOUT PPNMCS_STRING ppString);

const size_t NMCS_GUID_SIZE = (sizeof(uint8_t) * 16);

typedef struct _tag_NMCS_GUID
{
   uint8_t Data[NMCS_GUID_SIZE];
} NMCS_GUID, *PNMCS_GUID, **PPNMCS_GUID;

typedef double NMCS_TIMESTAMP;
typedef double NMCS_TIMESPAN;

typdef struct _tag_NMCS_ITEM
{
   NMCS_GUID Id;
   NMCS_TIMESTAMP CreationDate;
   NMCS_TIMESPAN ModificationDate;
   NMCS_STRING Comment;
} NMCS_ITEM_HEADER, *PNMCS_ITEM_HEADER, **PPNMCS_ITEM_HEADER;

typedef enum _tag_NMCS_PICTURE_TYPE
{
   NMCS_PICTURE_TYPE_JPEG    = 0,
   NMCS_PICTURE_TYPE_PNG     = 1,
   NMCS_MAX_PICTURE_TYPE     = NMCS_PICTURE_TYPE_PNG,
   NMCS_INVALID_PICTURE_TYPE = NMCS_MAX_PICTURE_TYPE + 1
} NMCS_PICTURE_TYPE;

typedef enum _tag_NMCS_TAG_REFERENCE_TYPE
{
   NMCS_TAG_REFERENCE_TYPE_ANY       = 0,
   NMCS_TAG_REFERENCE_TYPE_WIKIPEDIA = 1,
   NMCS_TAG_REFERENCE_TYPE_WIKIDATA  = 2,
   NMCS_MAX_TAG_REFERENCE_TYPE,
   NMCS_INVALID_TAG_REFERENCE_TYPE = NMCS_MAX_TAG_REFERENCE_TYPE
} NMCS_TAG_REFERENCE_TYPE;

typedef struct _tag_NMCS_TAG_REFERENCE
{
   NMCS_ITEM Item;
   NMCS_STRING Uri;
   NMCS_TAG_REFERENCE_TYPE Type;
} NMCS_TAG_REFERENCE, *PNMCS_TAG_REFERENCE, **PPNMCS_TAG_REFERENCE;

typedef struct _tag_NMCS_TAG
{
   NMCS_ITEM Item;
   NMCS_TIMESTAMP Timestamp;
   NMCS_STRING Name;
   NMCS_STRING Description;
   NMCS_TAG_REFERENCE Reference;
} NMCS_TAFG, *PNMCS_TAG, **PPNMCS_TAG;

typedef struct _tag_NMCS_CHAPTER
{
   NMCS_TAG Tag;
   NMCS_TIMESPAN Duration;
   NMCS_PICTURE Picture;
   NMCS_STRING Uri;
} NMCS_CHAPTER, *PNMCS_CHAPTER, **PPNMCS_CHAPTER;

#pragma pack(pop)

#endif // #ifndef __NMCS_NATIVE_BRIDGE_H_INCL__
