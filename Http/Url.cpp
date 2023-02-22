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
#include "Http/Url.h"
#include "Utils/Char.h"
#include "Utils/Exception.h"

namespace Rt2::Http
{
    class UrlScanner
    {
    private:
        void scanAuthority(
            const String& work,
            size_t&       stPort,
            size_t&       stPath);

        size_t scanPort(String& work, size_t st);

    public:
        String scheme;
        String authority;
        U16    port{80};
        String path;

        void scan(const String& str);
    };

    void UrlScanner::scanAuthority(const String& work,
                                   size_t&       stPort,
                                   size_t&       stPath)
    {
        // no: username:password @

        stPath = Npos;
        stPort = Npos;

        for (size_t i = 0; i < work.size(); ++i)
        {
            char ch = work[i];
            if (ch == '/')
            {
                stPath = i;
                break;
            }

            if (ch == ':')
            {
                stPort = i;
                break;
            }

            switch (ch)
            {
            case '.':
            case '-':
            case Digits09:
            case LowerCaseAz:
            case UpperCaseAz:
                authority.push_back(ch);
                break;
            default:
                throw Exception("invalid character: ", ch);
            }
        }

        if (authority.empty())
            authority = "127.0.0.1";
        else
        {
            if (authority.back() == '-')
                throw Exception("invalid authority: ", authority);
        }
    }

    size_t UrlScanner::scanPort(String& work, size_t st)
    {
        work = work.substr(st + 1, work.size());
        st   = Npos;
        String pn;

        for (size_t i = 0; i < work.size(); ++i)
        {
            if (const char ch = work[i];
                isDecimal(ch))
                pn.push_back(ch);
            else
            {
                st = i;
                break;
            }
        }
        port = Char::toUint16(pn);
        return st;
    }

    void UrlScanner::scan(const String& str)
    {
        // scheme :// authority:port / path

        String work = str;
        scheme      = work.substr(0, 4);
        if (scheme != "http")  // http, only for now
            scheme = "http";
        else
        {
            work = str.substr(4, str.size());
            if (work.substr(0, 3) != "://")
                throw Exception("invalid path");

            work = work.substr(3, str.size());
        }

        size_t stPath = Npos;
        size_t stPort = Npos;

        scanAuthority(work, stPort, stPath);

        if (stPort != Npos)
            stPath = scanPort(work, stPort);

        if (stPath < work.size())
            path = work.substr(stPath, work.size());
    }

    Url::Url(const String& url)
    {
        UrlScanner uc;
        uc.scan(url);

        _scheme    = uc.scheme;
        _port      = uc.port;
        _authority = uc.authority;
        _path      = uc.path;
    }

    void Url::setScheme(const String& scheme)
    {
        if (scheme == "http")
            _scheme = scheme;
    }

    void Url::setPath(const String& path)
    {
        // TODO: needs validated
        _path = path;
    }

    void Url::setAuthority(const String& auth)
    {
        // TODO: needs validated
        _authority = auth;
    }

    void Url::setPort(const U16& port)
    {
        // TODO: needs validated
        _port = port;
    }

    String Url::value() const
    {
        String jr = Su::join(_scheme, ':', '/', '/', _authority, ':', _port, _path);
        // TODO: needs validated
        return jr;
    }

}  // namespace Rt2::Http
