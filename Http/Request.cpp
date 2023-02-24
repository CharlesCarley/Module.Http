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
#include "Http/Request.h"
#include "Http/Common.h"
#include "Url.h"
#include "Utils/Exception.h"

namespace Rt2::Http
{
    Request::Request() :
        _method(Method::Get)
    {
    }

    void Request::setUrl(const Url& url)
    {
        _url = url;
    }

    void Request::setMethod(const Method& method)
    {
        _method = method;
    }

    void Request::extractHeader(IStream& in)
    {
        // header <method> <relative-url> <version> CRLF
        String method;
        in >> method;
        if (!method.empty())
        {
            setMethod(Method(method));

            String url;
            in >> url;
            _url = Url(url);

            String version;
            in >> version;
            (void)in.get();
        }
    }

    void Request::read(IStream& in)
    {
        // header <method> <relative-url> <version> CRLF
        if (!in.eof())
        {
            extractHeader(in);

            Console::writeLine("Method: ", _method.string());
            Console::writeLine("URL   : ", _url.value());

            // ignore the rest
            while (!in.eof())
                (void)in.get();
        }
    }

    void Request::write(OStream& out) const
    {
        out << _method.string();
        out << ' ' << _url.value() << ' ' << "HTTP/1.1" << Eol;
    }

    String Request::toString() const
    {
        OutputStringStream ss;
        write(ss);
        return ss.str();
    }
}  // namespace Rt2::Http
