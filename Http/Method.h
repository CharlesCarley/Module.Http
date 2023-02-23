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

    class Method
    {
    public:
        enum Type
        {
            Get,
            Put,
            Post,
            Delete,
            Head,
            Connect,
            Undefined,
        };

    private:
        I8 _type{Undefined};

        static String toString(I8 type);

        static I8 fromString(const String& str);

    public:
        Method(const I8& type) :
            _type(type) {}

        explicit Method(const String& type) :
            _type(fromString(type)) {}

        Method(const Method&) = default;

        const I8& type() const
        {
            return _type;
        }

        String string() const
        {
            return toString(_type);
        }

        bool isTypeOf(const Type& type) const
        {
            return _type == type;
        }
    };

}  // namespace Rt2::Http
