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
#include "Response.h"
#include "Common.h"
#include "Sockets/PlatformSocket.h"
#include "Sockets/SocketStream.h"

namespace Rt2::Http
{
    Response::Response(const Sockets::Net::Socket& sock) :
        _sock(sock)
    {
    }

    void Response::write(IStream&      stream,
                         const String& contentType) const
    {
        OutputStringStream oss;
        while (!stream.eof())
            oss.put((char)stream.get());

        String str = oss.str();

        OutputStringStream resp;
        resp << "HTTP/1.1 200 OK" << Eol;
        resp << "Content-Type: " << contentType << Eol;
        resp << "Content-Length: " << str.size() << Eol;
        resp << Eol << Eol;
        resp << str << '\n'
             << Eol;


        str = resp.str();
        Sockets::Net::writeBuffer(_sock, str.c_str(), str.size());
    }

    void Response::write() const
    {
        Sockets::SocketOutputStream resp(_sock);
        resp << "HTTP/1.1 200 OK";
        resp << Eol << Eol;
    }

    void Response::writeNotFound() const
    {
        Sockets::SocketOutputStream resp(_sock);
        resp << "HTTP/1.1 404 NOT FOUND";
        resp << Eol << Eol;
    }

}  // namespace Rt2::Http
