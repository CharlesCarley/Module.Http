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
#include "Http/Method.h"
#include "Http/Common.h"
#include "Utils/Char.h"
#include "Utils/Definitions.h"
#include "Utils/Exception.h"
#include "Utils/String.h"

namespace Rt2::Http
{
    constexpr EnumNameTable MethodValues[] = {
        {      "GET",       Method::Get, 3},
        {      "PUT",       Method::Put, 3},
        {     "POST",      Method::Post, 4},
        {   "DELETE",    Method::Delete, 6},
        {     "HEAD",      Method::Head, 4},
        {  "CONNECT",   Method::Connect, 7},
        {"UNDEFINED", Method::Undefined, 9},
    };

    String Method::toString(I8 type)
    {
        switch (type)
        {
        case Post:
        case Put:
        case Delete:
        case Get:
        case Head:
        case Connect:
        case Undefined:
            return MethodValues[type].string();
        default:
            throw Exception("undefined method ", (int)type);
        }
    }

    I8 Method::fromString(const String& str)
    {
        return EnumNameTable::enumeration(
            str,
            MethodValues,
            std::size(MethodValues),
            Undefined);
    }
}  // namespace Rt2::Http
