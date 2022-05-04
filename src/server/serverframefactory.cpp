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

#include "serverframefactory.h"

namespace ultralove { namespace nmcs { namespace server {

FrameFactory::FrameFactory() {}

FrameFactory::~FrameFactory()
{
   std::lock_guard<std::recursive_mutex> lock(functionsLock_);
   functions_.clear();
}

bool FrameFactory::RegisterFrame(const uint32_t id, CREATE_FRAME_FUNCTION factoryFunction)
{
   NMCS_PRECONDITION_RETURN(id != ID3V2_INVALID_FRAME_ID, false);
   NMCS_PRECONDITION_RETURN(factoryFunction != nullptr, false);

   std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   bool registered                                           = false;
   const FunctionDictionary::const_iterator functionIterator = functions_.find(id);
   if (functionIterator == functions_.end()) {
      registered = functions_.insert(std::pair<uint32_t, CREATE_FRAME_FUNCTION>(id, factoryFunction)).second;
   }

   return registered;
}

void FrameFactory::UnregisterFrame(const uint32_t id)
{
   std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   const FunctionDictionary::const_iterator functionIterator = functions_.find(id);
   if (functionIterator != functions_.end()) {
      functions_.erase(functionIterator);
   }
}

FrameFactory& FrameFactory::Instance()
{
   static FrameFactory self;
   return self;
}

bool FrameFactory::CanCreate(const uint8_t* data, const size_t dataSize) const
{
   NMCS_PRECONDITION_RETURN(data != nullptr, false);
   NMCS_PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_ID_SIZE, false);

   const char idString[5] = {(char)data[0], (char)data[1], (char)data[2], (char)data[3], 0};

   const uint32_t id      = ID3V2_DECODE_FRAME_ID(&data[ID3V2_FRAME_ID_OFFSET], ID3V2_FRAME_ID_SIZE);
   return (functions_.find(id) != functions_.end());
}

IFrame* FrameFactory::Create(const uint8_t* data, const size_t dataSize) const
{
   NMCS_PRECONDITION_RETURN(data != nullptr, nullptr);
   NMCS_PRECONDITION_RETURN(dataSize >= ID3V2_FRAME_HEADER_SIZE, nullptr);

   std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   IFrame* pFrame    = nullptr;
   const uint32_t id = ID3V2_DECODE_FRAME_ID(&data[ID3V2_FRAME_ID_OFFSET], ID3V2_FRAME_ID_SIZE);
   if (id != ID3V2_INVALID_FRAME_ID) {
      const FunctionDictionary::const_iterator functionIterator = functions_.find(id);
      if (functionIterator != functions_.end()) {
         CREATE_FRAME_FUNCTION factoryFunction = functionIterator->second;
         if (factoryFunction != nullptr) {
            pFrame = (*factoryFunction)();
            if (pFrame != nullptr) {
               bool isConfigured = pFrame->ConfigureData(&data[ID3V2_FRAME_HEADER_OFFSET], dataSize - ID3V2_FRAME_HEADER_SIZE);
               if (false == isConfigured) {
                  SafeDelete(pFrame);
               }
            }
         }
      }
   }

   return pFrame;
}

}}} // namespace ultralove::nmcs::server
