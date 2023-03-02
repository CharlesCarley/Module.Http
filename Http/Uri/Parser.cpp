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
#include "Http/Uri/Parser.h"
#include "Http/Common.h"
#include "ParserBase/ParserBase.h"
#include "Utils/String.h"

namespace Rt2::Http::Uri
{
    constexpr EnumNameTable ValidSchemes[] = {
        {"file", FileScheme, 4},
        {"http", HttpScheme, 4},
    };

    inline bool isScheme(const I8 a,
                         const I8 b,
                         const I8 c,
                         const I8 d)
    {
        return a == TOK_ID &&
               b == TOK_COLON &&
               c == TOK_SLASH &&
               d == TOK_SLASH;
    }

    inline bool isDot(const I8 a,
                      const I8 b,
                      const I8 c)
    {
        return a == TOK_DOT &&
               b == TOK_DOT &&
               c == TOK_DOT;
    }

    inline bool isPathToken(const I8 a)
    {
        return a == TOK_ID ||
               a == TOK_DIGIT ||
               a == TOK_SLASH ||
               a == TOK_DOT ||
               a == TOK_UNDERSCORE;
    }

    inline bool isDomainToken(const I8 a)
    {
        return a == TOK_ID ||
               a == TOK_DIGIT ||
               a == TOK_DOT ||
               a == TOK_UNDERSCORE;
    }

    inline bool isRangeI8(const I32 a)
    {
        return a >= 0x00 && a <= 0xFF;
    }

    inline bool isRangeU16(const I32 a)
    {
        return a >= 0x00 && a <= 0xFFFF;
    }

    Parser::Parser()
    {
        _scanner = new Scanner();
    }

    Parser::~Parser()
    {
        delete _scanner;
    }

    void Parser::ruleAbsoluteUri()
    {
        String scheme;

        const I8 t0 = token(0).type();
        const I8 t1 = token(1).type();
        const I8 t2 = token(2).type();
        if (const I8 t3 = token(3).type();
            !isScheme(t0, t1, t2, t3))
        {
            // default to http
            scheme = "http";
        }
        else
        {
            scheme = string(0);
            if (isInvalidScheme(scheme))
                error("invalid scheme type: ", scheme);
            advanceCursor(4);
        }

        _url.setScheme(scheme);

        ruleOptionalUserPassword();
        ruleAuthority();
        ruleOptionalPort();
        ruleRelativeUri();
    }

    void Parser::ruleOptionalUserPassword()
    {
        if (tokenType(0) == TOK_ID &&
            tokenType(1) == TOK_COLON &&
            tokenType(2) == TOK_ID &&
            tokenType(3) == TOK_AT)
        {
            // ignore for now
            advanceCursor(4);
        }
    }

    void Parser::ruleRelativeUri()
    {
        rulePath();
        // arguments
        // fragments
    }

    void Parser::ruleIpv4()
    {
        const I8 dc0 = tokenType(1);
        const I8 dc1 = tokenType(3);
        if (const I8 dc2 = tokenType(5);
            !isDot(dc0, dc1, dc2))
            error("invalid ipv4");

        if (isIntU8(token(0), token(2), token(4), token(6)))
        {
            const I32 a = integer(0);
            const I32 b = integer(2);
            const I32 c = integer(4);
            const I32 d = integer(6);

            char buf[16] = {};
            if (const int l = snprintf(buf, 16, "%d.%d.%d.%d", a, b, c, d);
                l > 0)
            {
                buf[l] = 0;
                _url.setAuthority({buf, (size_t)l});
            }
        }
        else
            error("invalid ipv4");
    }

    void Parser::ruleDomain()
    {
        OutputStringStream out;
        while (isDomainToken(tokenType(0)))
        {
            switch (tokenType(0))
            {
            case TOK_DOT:
                out.put('.');
                break;
            case TOK_DASH:
                out.put('-');
                break;
            case TOK_UNDERSCORE:
                out.put('_');
                break;
            case TOK_DIGIT:
                out << Char::toString(integer(0));
                break;
            case TOK_ID:
                out << string(0);
                break;
            default:
                error("invalid domain name");
            }
            advanceCursor();
        }

        _url.setAuthority(out.str());
    }

    void Parser::ruleAuthority()
    {
        if (const TokenBase& t0 = token(0);
            t0.type() == TOK_ID)
        {
            // example.com, localhost,
            // a-b.com, a_b.com
            ruleDomain();
        }
        else if (t0.type() == TOK_DIGIT)
        {
            // 0.0.0.0  -> ipv4

            if (const I8 t1 = tokenType(1); t1 == TOK_DOT)
            {
                ruleIpv4();
                advanceCursor(7);
            }
            else
                error("invalid Ipv4 address");
        }
        else if (t0.type() == TOK_HEX)
        {
            // 0000:0000:0000:0000:0000:0000:0000:0000 -> ipv6
        }
    }

    void Parser::rulePath()
    {
        if (tokenType(0) == TOK_SLASH)
        {
            OutputStringStream out;
            while (isPathToken(tokenType(0)))
            {
                // test valid
                const TokenBase& t0 = token(0);
                switch (tokenType(0))
                {
                case TOK_SLASH:
                    out.put('/');
                    break;
                case TOK_DOT:
                    out.put('.');
                    break;
                case TOK_DASH:
                    out.put('-');
                    break;
                case TOK_UNDERSCORE:
                    out.put('_');
                    break;
                case TOK_DIGIT:
                    out << Char::toString(integer(0));
                    break;
                case TOK_ID:
                    out << string(0);
                    break;
                default:
                    error("invalid path token");
                }
                advanceCursor();
            }
            _url.setPath(out.str());
        }
        else
        {
            _url.setPath("/");
        }
    }

    void Parser::ruleOptionalPort()
    {
        if (tokenType(0) == TOK_COLON)
        {
            advanceCursor();
            if (tokenType(0) != TOK_DIGIT)
                error("expected a port number");

            if (const I32 v = integer(0);
                isRangeU16(v))
                _url.setPort((U16)v);
            else
                error("port number is outside the range [0x00, 0xFFFF]");
            advanceCursor();
        }
        else
        {
            // default to port 80
            _url.setPort(80);
        }
    }

    void Parser::ruleNetworkUri()
    {
    }

    void Parser::ruleUri()
    {
        // The first call in scan sets
        // the state of the scanner.
        if (tokenType(0) == TOK_EOF)
            return;

        switch (const Scanner* sc = (Scanner*)_scanner;
                sc->state())
        {
        case Scanner::Absolute:
            _url.setType(Url::Type::Absolute);
            ruleAbsoluteUri();
            break;
        case Scanner::Relative:
            _url.setType(Url::Type::Relative);
            ruleRelativeUri();
            break;
        case Scanner::RelativeNet:
            _url.setType(Url::Type::Network);
            ruleNetworkUri();
            break;
        default:
            error("unknown URL type: ", sc->state());
        }
    }

    bool Parser::isIntU8(const TokenBase& a, const TokenBase& b, const TokenBase& c, const TokenBase& d) const
    {
        return a.type() == TOK_DIGIT && isRangeI8(_scanner->integer(a.index())) &&
               b.type() == TOK_DIGIT && isRangeI8(_scanner->integer(b.index())) &&
               c.type() == TOK_DIGIT && isRangeI8(_scanner->integer(c.index())) &&
               d.type() == TOK_DIGIT && isRangeI8(_scanner->integer(d.index()));
    }

    void Parser::parseImpl(IStream& is)
    {
        _scanner->attach(&is);

        ruleUri();

        // Make this work under the assumption that if
        // any tokens remain after ruleUri returns then
        // it's an error.
        if (tokenType(0) != TOK_EOF)
            error("expected the end of file token");
    }

    void Parser::writeImpl(OStream& is, int format)
    {
    }

    bool Parser::isInvalidScheme(const String& scheme)
    {
        for (const auto& [value, type, size] : ValidSchemes)
        {
            if (scheme == value)
                return false;
        }
        return true;
    }
}  // namespace Rt2::Http::Uri