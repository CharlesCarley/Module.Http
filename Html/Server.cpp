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
#include "Html/Server.h"
#include <csignal>
#include "ExitSignal.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Sockets/Connection.h"
#include "Sockets/SocketStream.h"
#include "Threads/Task.h"
#include "Utils/Exception.h"

namespace Rt2::Html
{
    using namespace Sockets;
    using namespace Net;

    Server::Server()
    {
        ensureInitialized();
    }

    Server::~Server()
    {
    }

    void Server::setListener(RequestListener* listener)
    {
        _requestListener = listener;
    }

    bool Server::start(const String& address, uint16_t port)
    {
        _srv = create(AddrINet, Stream);
        if (_srv == InvalidSocket)
            throw Exception("Failed to create server socket");

        constexpr char opt = 1;
        if (setOption(_srv,
                      SocketLevel,
                      ReuseAddress,
                      &opt,
                      sizeof(char)) != Ok)
        {
            throw Exception("Failed to set socket option");
        }

        SocketInputAddress host;
        constructInputAddress(host, AddrINet, port, address);

        if (Net::bind(_srv, host) != Ok)
            throw Exception("Failed to bind server socket to ", address, ':', port);

        if (listen(_srv, 100) != Ok)
            throw Exception("Failed to listen on the server socket");

        return true;
    }

    void Server::runSignaled() const
    {
        const ExitSignal sig(_srv);
        while (!sig.signaled())
        {
            Threads::Task::start(
                [=]
                { acceptConnections(); });
        }
    }

    void Server::acceptConnections() const
    {
        Connection client;
        if (const auto sock = accept(_srv, client); sock != InvalidSocket)
            tryProcess(sock);
    }

    void Server::tryProcess(const Socket& sock) const
    {
        try
        {
            if (_requestListener)
            {
                Http::Request     request;
                SocketInputStream ss(sock);
                request.read(ss);
                Http::Response response(sock);
                _requestListener->handle(request, response);
            }

            close(sock);
        }
        catch (Exception& ex)
        {
            Console::writeLine(ex.what());
        }
    }

    void Server::runDetached() const
    {
        Threads::Task::start(
            [=]
            {
                runSignaled();
            });
    }
}  // namespace Rt2::Html
