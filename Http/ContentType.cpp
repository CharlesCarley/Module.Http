/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "Http/ContentType.h"
#include "Http/Common.h"
#include "Utils/Char.h"
#include "Utils/Definitions.h"
#include "Utils/Exception.h"
#include "Utils/String.h"

namespace Rt2::Http
{
    constexpr EnumNameTable ContentTypeValues[] = {
        {"application/octet-stream", ContentType::AppOctetStream, 24},
        {               "text/html",       ContentType::TextHtml,  9},
        {                "text/css",        ContentType::TextCss,  8},
        {               "text/json",       ContentType::TextJson,  9},
    };

    String ContentType::toString(I8 type)
    {
        switch (type)
        {
        case AppOctetStream:
        case TextHtml:
        case TextCss:
        case TextJson:
            return ContentTypeValues[type].string();
        default:
            throw Exception("undefined Content type ", type);
        }
    }

    I8 ContentType::fromString(const String& str)
    {
        return EnumNameTable::enumeration(
            str,
            ContentTypeValues,
            std::size(ContentTypeValues),
            Undefined);
    }
}  // namespace Rt2::Http
