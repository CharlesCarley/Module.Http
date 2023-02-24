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

namespace Rt2::Http::Uri
{
    enum TokenId
    {
        TOK_ERROR = -2,
        TOK_EOF,   // no more characters in the stream
        TOK_NULL,  // undefined value
        TOK_SCHEME,
        TOK_ALPHA,
        TOK_ID,
        TOK_DIGIT,
        TOK_POUND      = '#',
        TOK_SLASH      = '/',
        TOK_DOT        = '.',
        TOK_SEMICOLON  = ';',
        TOK_COLON      = ':',
        TOK_QUESTION   = '?',
        TOK_AT         = '@',
        TOK_AMP        = '&',
        TOK_EQ         = '=',
        TOK_PLUS       = '+',
        TOK_DOLLAR     = '$',
        TOK_COMMA      = ',',
        TOK_DASH       = '-',
        TOK_UNDERSCORE = '_',
        TOK_EXCLAIM    = '!',
        TOK_MUL        = '*',
        TOK_TICK       = '`',
        TOK_LP         = '(',
        TOK_RP         = ')',
    };

}  // namespace Rt2::Http::Uri
