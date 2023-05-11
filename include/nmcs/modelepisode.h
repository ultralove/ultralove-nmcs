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

#ifndef __NMCS_MODEL_EPISODE_H_INCL__
#define __NMCS_MODEL_EPISODE_H_INCL__

#include <nmcs/runtimeguid.h>
#include <nmcs/runtimestring.h>
#include <nmcs/runtimetimestamp.h>
#include <nmcs/runtimeuri.h>

#include <nmcs/modelchaptertag.h>
#include <nmcs/modelcontribution.h>
#include <nmcs/modelenclosure.h>
#include <nmcs/modelepisodetype.h>
#include <nmcs/modelfabric.h>
#include <nmcs/modellocationtag.h>
#include <nmcs/modelpicture.h>
#include <nmcs/modeltranscripttag.h>

#pragma pack(push)
#pragma pack(8)

namespace ultralove { namespace nmcs { namespace model {

class NMCS_SHARED_API Episode : public Fabric
{
public:
   runtime::Uri uri_;
   runtime::String title_;
   runtime::String description_;
   runtime::String summary_;
   Picture picture_;
   EpisodeType type_;
   bool explicit_;
   runtime::Timestamp publicationDate_;
   runtime::Timespan duration_;
   runtime::Guid guid_;
   Contribution contributions_[0];
   ChapterTag chapters_[0];
   LocationTag locations_[0];
   TranscriptTag transcript_[0];
   Enclosure enclosures_[0];

   virtual ~Episode() {}
};

}}} // namespace ultralove::nmcs::model

#pragma pack(pop)

#endif // #ifndef __NMCS_MODEL_EPISODE_H_INCL__
