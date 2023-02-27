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
#include "ContentType.h"
#include "Sockets/PlatformSocket.h"
#include "Sockets/SocketStream.h"
#include "Utils/Exception.h"

namespace Rt2::Http
{
    constexpr const char* HttpVer    = "HTTP/1.1 ";
    constexpr size_t      HttpVerLen = 9;

    Response::Response(const Sockets::Net::Socket& sock) :
        _sock(sock)
    {
    }

    void Response::write(const String& data, const ContentType& contentType) const
    {
        try
        {
            OutputStringStream oss;
            oss.write(data.c_str(), data.size());
            oss.put('\n');
            oss.put('\n');

            Sockets::SocketOutputStream resp(_sock);
            writeCode(resp, 200);
            writeContent(resp, oss.str(), contentType);
        }
        catch (Exception& ex)
        {
            Sockets::SocketOutputStream resp(_sock);
            writeCode(resp, 404);
            writeContent(resp, ex.what(), ContentType::TextPlain);
        }
    }

    void Response::write(IStream& stream, const ContentType& contentType) const
    {
        try
        {
            OutputStringStream oss;
            Su::copy(oss, stream, false);
            oss.put('\n');
            oss.put('\n');

            Sockets::SocketOutputStream resp(_sock);
            writeCode(resp, 200);
            writeContent(resp, oss.str(), contentType);
        }
        catch (Exception& ex)
        {
            Sockets::SocketOutputStream resp(_sock);
            writeCode(resp, 404);
            writeContent(resp, ex.what(), ContentType::TextPlain);
        }
    }

    void Response::write() const
    {
        Sockets::SocketOutputStream resp(_sock);
        writeCode(resp, 200);
    }

    void Response::writeNotFound() const
    {
        Sockets::SocketOutputStream resp(_sock);
        writeCode(resp, 404);
    }

    void Response::writeCode(OStream& out, const int code)
    {
        if (code == 200)
        {
            out.write(HttpVer, HttpVerLen);
            out << code << " OK" << Eol;
        }
        else if (code == 404)
        {
            out.write(HttpVer, HttpVerLen);
            out << code << " NOT FOUND" << Eol;
        }
    }

    void Response::writeContent(OStream& out, const String& content, const ContentType& contentType)
    {
        out << "Content-Type: " << contentType.string() << Eol;
        out << "Content-Length: " << content.size() << Eol;
        out << Eol << Eol;
        out << content;
    }

}  // namespace Rt2::Http
