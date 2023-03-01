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
#include <thread>
#include "ExitSignal.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Sockets/SocketStream.h"
#include "Threads/Task.h"
#include "Threads/Thread.h"
#include "Utils/Exception.h"

namespace Rt2::Html
{
    using namespace Sockets;
    using namespace Net;

    Server::Server() = default;

    Server::~Server()
    {
        exit();
    }

    void Server::setListener(RequestListener* listener)
    {
        _requestListener = listener;
    }

    bool Server::start(const String& address, const uint16_t port)
    {
        _srv = new ServerSocket(address, port);
        _srv->connect([=](const Net::Socket& cli)
                      { tryProcess(cli); });
        _srv->start();
        return true;
    }

    void Server::runSignaled() const
    {
        Console::nl();
        Console::setForeground(CS_GREEN);
        Console::write("Server running press");
        Console::setForeground(CS_WHITE);
        Console::write(" Ctrl+C");
        Console::setForeground(CS_GREEN);
        Console::write(" to exit.");
        Console::nl();
        Console::resetColor();

        const ExitSignal sig;
        while (!sig.signaled())
            Threads::Thread::yield();
        _srv->stop();
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
            Console::writeError(ex.what());
        }
    }

    void Server::exit()
    {
        if (_srv)
        {
            _srv->stop();
            while (_srv->isValid())
                Threads::Thread::sleep(1000);
        }
        delete _srv;
        _srv = nullptr;
    }

    void Server::setRoot(const String& root)
    {
        _root = PathUtil(root);
        if (!_root.exists())
            throw Exception("server root directory is invalid");
    }
}  // namespace Rt2::Html
