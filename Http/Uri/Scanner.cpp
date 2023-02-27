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

#include "Http/Uri/Scanner.h"
#include "Http/Uri/Token.h"
#include "Utils/Char.h"

namespace Rt2::Http::Uri
{
    /*
        https://www.ietf.org/rfc/rfc2396.txt

        URI-reference   = [ absoluteURI | relativeURI ] [ "#" fragment ]
        absoluteURI     = scheme ":" ( hier_part | opaque_part )
        relativeURI     = ( net_path | abs_path | rel_path ) [ "?" query ]
        hier_part       = ( net_path | abs_path ) [ "?" query ]
        opaque_part     = uric_no_slash *uric
        uric_no_slash   = unreserved | escaped | ";" | "?" | ":" | "@"
                        | "&" | "=" | "+" | "$" | ","

        net_path        = "//" authority [ abs_path ]
        abs_path        = "/" path_segments
        rel_path        = rel_segment [ abs_path ]
        rel_segment     = 1*( unreserved | escaped
                         | ";" | "@" | "&" | "=" | "+" | "$" | "," )

        scheme          = alpha *( alpha | digit | "+" | "-" | "." )
        authority       = server | reg_name
        reg_name        = 1*( unreserved | escaped | "$" | ","
                        | ";" | ":" | "@" | "&" | "=" | "+" )
        server          = [ [ userinfo "@" ] hostport ]

        userinfo        = *( unreserved | escaped | ";" | ":" | "&" | "=" | "+" | "$" | "," )
        hostport        = host [ ":" port ]

        host            = hostname | IPv4address
        hostname        = *( domainlabel "." ) toplabel [ "." ]
        domainlabel     = alphanum | alphanum *( alphanum | "-" ) alphanum
        toplabel        = alpha | alpha *( alphanum | "-" ) alphanum
        IPv4address     = 1*digit "." 1*digit "." 1*digit "." 1*digit
        port            = *digit
        path            = [ abs_path | opaque_part ]
        path_segments   = segment *( "/" segment )
        segment         = *pchar *( ";" param )
        param           = *pchar


        pchar           = unreserved | escaped
                        | ":" | "@" | "&" | "=" | "+" | "$" | ","
        query           = *uric
        fragment        = *uric
        uric            = reserved | unreserved | escaped
        reserved        = ";" | "/" | "?" | ":" | "@" | "&" | "=" | "+" | "$" | ","
        unreserved      = alphanum | mark
        mark            = "-" | "_" | "." | "!" | " ?" | "*" | "’" | "(" | ")"
        escaped         = "%" hex hex
        hex             = digit | "A" | "B" | "C" | "D" | "E" | "F" | "a" | "b" | "c" | "d" | "e" | "f"
        alphanum        = alpha | digit
        alpha           = lowalpha | upalpha
        lowalpha        = [a-z]
        upalpha         = [A-Z]
        digit           = [0-9]
    */

    void Scanner::scanInt(TokenBase& tok)
    {
        String dest;
        int    ch = _stream->get();

        while (isDecimal(ch))
        {
            dest.push_back((char)ch);
            ch = _stream->get();
        }
        _stream->putback((char)ch);

        // save it to the cache and set it's index
        tok.setIndex(save(Char::toInt32(dest)));
        tok.setType(TOK_DIGIT);
    }

    void Scanner::scanId(TokenBase& tok)
    {
        String dest;

        int ch = _stream->get();
        while (isLetter(ch) || isDecimal(ch))
        {
            dest.push_back((char)ch);
            ch = _stream->get();
        }

        // restore the last read character
        // that was not a letter or a decimal.
        _stream->putback((char)ch);

        // save it to the cache and set it's index
        tok.setIndex(save(dest));
        tok.setType(TOK_ID);
    }

    void Scanner::setStartState(const int ch)
    {
        // The scan state pivots around the
        // first character.
        if (ch == '/')
        {
            if (_stream->peek() == '/')
                _state = RelativeNet;
            else
                _state = Relative;
        }
        else
            _state = Absolute;
    }

    void Scanner::scan(TokenBase& tok)
    {
        if (_stream == nullptr)
            syntaxError("no supplied stream");

        tok.clear();
        tok.setType(TOK_NULL);

        String scratch;

        int ch;
        while ((ch = _stream->get()) > 0)
        {
            if (_state == Start)
                setStartState(ch);

            switch (ch)
            {
            case '#':
                tok.setType(TOK_POUND);
                return;
            case '/':
                tok.setType(TOK_SLASH);
                return;
            case '.':
                tok.setType(TOK_DOT);
                return;
            case ';':
                tok.setType(TOK_SEMICOLON);
                return;
            case ':':
                tok.setType(TOK_COLON);
                return;
            case '?':
                tok.setType(TOK_QUESTION);
                return;
            case '@':
                tok.setType(TOK_AT);
                return;
            case '&':
                tok.setType(TOK_AMP);
                return;
            case '=':
                tok.setType(TOK_EQ);
                return;
            case '+':
                tok.setType(TOK_PLUS);
                return;
            case '$':
                tok.setType(TOK_DOLLAR);
                return;
            case ',':
                tok.setType(TOK_COMMA);
                return;
            case '-':
                tok.setType(TOK_DASH);
                return;
            case '_':
                tok.setType(TOK_UNDERSCORE);
                return;
            case '!':
                tok.setType(TOK_EXCLAIM);
                return;
            case '*':
                tok.setType(TOK_MUL);
                return;
            case '`':
                tok.setType(TOK_TICK);
                return;
            case '(':
                tok.setType(TOK_LP);
                return;
            case ')':
                tok.setType(TOK_RP);
                return;
            case Digits09:
                // TODO: separate out digits from hex digits
                _stream->putback((char)ch);
                scanInt(tok);
                return;
            case LowerCaseAz:
            case UpperCaseAz:
                _stream->putback((char)ch);
                scanId(tok);
                return;
            default:
                break;
            }
        }
        tok.setType(TOK_EOF);
    }

}  // namespace Rt2::Http::Uri