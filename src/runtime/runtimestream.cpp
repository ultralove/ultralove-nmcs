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

#include <nmcs/runtimestream.h>

namespace ultralove { namespace nmcs { namespace runtime {

Stream::Stream() {}

Stream::Stream(const uint8_t* items, const size_t itemCount)
{
   Write(items, itemCount);
}

Stream::~Stream()
{
   Reset();
}

Stream::Stream(const Stream& rhs)
{
   *this = rhs;
}

Stream& Stream::operator=(const Stream& rhs)
{
   if (this != &rhs) {
      Write(rhs.Data(), rhs.Size());
   }

   return *this;
}

Stream::Stream(Stream&& rhs) noexcept : items_(std::exchange(rhs.items_, nullptr)), itemCount_(std::exchange(rhs.itemCount_, 0)) {}

Stream& Stream::operator=(Stream&& rhs) noexcept
{
   if (this != &rhs) {
      delete[] items_;
      items_     = std::exchange(rhs.items_, nullptr);
      itemCount_ = std::exchange(rhs.itemCount_, 0);
   }

   return *this;
}

bool Stream::operator==(const Stream& rhs) const
{
   bool result = false;

   if (Size() == rhs.Size()) {
      result = memcmp(Data(), rhs.Data(), Size()) == 0;
   }

   return result;
}

bool Stream::operator<(const Stream& rhs) const
{
   bool result = false;

   if (Size() < rhs.Size()) {
      result = true;
   }
   else {
      result = (memcmp(Data(), rhs.Data(), Size()) < 0);
   }

   return result;
}

const uint8_t* Stream::Data(const size_t itemOffset) const
{
   NMCS_PRECONDITION_RETURN(items_ != 0, 0);
   NMCS_PRECONDITION_RETURN(itemOffset < itemCount_, 0);

   return &items_[itemOffset];
}

size_t Stream::Write(const size_t itemOffset, const uint8_t* items, const size_t itemCount)
{
   NMCS_PRECONDITION_RETURN(items != 0, false);
   NMCS_PRECONDITION_RETURN(itemCount > 0, false);

   size_t itemsWritten = 0;

   if (Valid() == false) {
      AllocItems(itemCount);
   }
   else if ((itemOffset + itemCount) > itemCount_) {
      uint8_t* currentItems   = items_;
      size_t currentItemCount = itemCount_;

      AllocItems(itemCount);
      ReplaceItems(currentItems, currentItemCount);

      SafeDeleteArray(currentItems);
      currentItemCount = 0;
   }

   if ((Valid() == true) && (itemCount_ >= (itemOffset + itemCount))) {
      memcpy(&items_[itemOffset * sizeof(uint8_t)], items, itemCount * sizeof(uint8_t));
      itemsWritten = itemCount;
   }

   return itemsWritten;
}

size_t Stream::Read(const size_t itemOffset, uint8_t* items, const size_t itemCount) const
{
   NMCS_PRECONDITION_RETURN(items_ != 0, 0);
   NMCS_PRECONDITION_RETURN(itemCount_ > 0, 0);
   NMCS_PRECONDITION_RETURN(items != 0, 0);
   NMCS_PRECONDITION_RETURN(itemCount > 0, 0);

   const size_t resultItemCount = ((itemOffset + itemCount) <= itemCount_) ? itemCount : (itemCount_ - itemOffset);
   memcpy(items, &items_[itemOffset * sizeof(uint8_t)], resultItemCount * sizeof(uint8_t));
   return resultItemCount;
}

void Stream::Reset()
{
   itemCount_ = 0;
   SafeDeleteArray(items_);
}

void Stream::AllocItems(const size_t itemCount)
{
   Reset();

   if (itemCount > 0) {
      items_ = new uint8_t[itemCount * sizeof(uint8_t)];
      if (items_ != 0) {
         itemCount_ = itemCount;
      }
   }
}

void Stream::ReplaceItems(const uint8_t* items, const size_t itemCount)
{
   NMCS_PRECONDITION(items_ != 0);
   NMCS_PRECONDITION(itemCount_ <= itemCount);

   memcpy(items_, items, itemCount * sizeof(uint8_t));
}
}}} // namespace ultralove::nmcs::runtime
