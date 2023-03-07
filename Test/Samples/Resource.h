#pragma once
#include "Utils/Array.h"
#include "Utils/String.h"
namespace Rt2::HtmlSample
{
   using ByteArray = SimpleArray<uint8_t>;


   class Resource
   {
   public:
       static void getSite(ByteArray &dest);

       static void getSite(String &dest);
   };
} // namespace Rt2::HtmlSample
