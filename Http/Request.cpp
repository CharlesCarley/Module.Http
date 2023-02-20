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
#include "Utils/Exception.h"

namespace Rt2::Http
{
    Request::Request() :
        _method(Get)
    {
    }

    void Request::extractHeader(IStream& in)
    {
        // header <method> <relative-url> <version> CRLF
        String method;
        in >> method;
        if (method == "GET")
            _method = Get;
        else if (method == "HEAD")
            _method = Head;
        else if (method == "PUT")
            _method = Put;
        else if (method == "POST")
            _method = Post;
        else if (method == "DELETE")
            _method = Delete;
        else if (method == "CONNECT")
            _method = Connect;
        else
            throw Exception("undefined method ", method);

        in >> _url;

        String version;
        in >> version;
        (void)in.get();
    }

    void Request::read(IStream& in)
    {
        // header <method> <relative-url> <version> CRLF
        extractHeader(in);

        Console::writeLine("Method: ", _method);
        Console::writeLine("URL   : ", _url);

        // ignore the rest
        while (!in.eof())
            (void)in.get();
    }
}  // namespace Rt2::Http
