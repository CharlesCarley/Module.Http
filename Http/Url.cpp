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
#include "Uri/Parser.h"

namespace Rt2::Http
{
    Url::Url(const String& url)
    {
        Uri::Parser       p;
        InputStringStream ss(url);
        p.read(ss);
        *this = p.url();
    }

    void Url::setScheme(const String& scheme)
    {
        if (!Uri::Parser::isInvalidScheme(scheme))
            _scheme = scheme;
        else
            throw Exception("invalid URL scheme: ", scheme);
    }

    void Url::setPath(const String& path)
    {
        // Some assumed to be valid path (not tested to be valid here)
        // with the form '/' <id[0]> '/' <id[n]>
        // where the last element points to the resource.
        // (Note: there is no max limit on the number of max separators)
        // TODO: Limit the number of max separators
        if (!path.empty())
        {
            if (path[0] != '/')
                _path = Su::join('/', path);
            else
                _path = path;
        }
    }

    void Url::setAuthority(const String& auth)
    {
        // TODO: needs validated when set manually.
        _authority = auth;
    }

    void Url::setPort(const U16& port)
    {
        _port = port;
    }

    String Url::value() const
    {
        // TODO: needs validated when set manually.

        if (!_path.empty())
        {
            if (_path.front() != '/')
                throw Exception("invalid path format");
        }

        return Su::join(_scheme, ':', '/', '/', _authority, ':', _port, _path);
    }

}  // namespace Rt2::Http
