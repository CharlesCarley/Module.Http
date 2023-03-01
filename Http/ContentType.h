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
#pragma once
#include "Utils/Definitions.h"
#include "Utils/String.h"

namespace Rt2::Http
{

    class ContentType
    {
    public:
        enum Type
        {
            AppOctetStream,
            TextHtml,
            TextCss,
            TextPlain,
            TextJson,
            TextJs,
            Icon,
            Undefined,
        };

    private:
        const I8 _type{Undefined};

        static String toString(I8 type);

        static I8 fromString(const String& str);
        static I8 fromFile(const String& str);

    public:
        ContentType(const I8& type) :
            _type(type) {}
        explicit  ContentType(const String& ext) :
            _type(fromFile(ext)) {}

        const I8& type() const
        {
            return _type;
        }

        bool isPlainText() const;

        String string() const
        {
            return toString(_type);
        }
    };

}  // namespace Rt2::Http
