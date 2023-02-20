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
#pragma once
#include "Http/RequestListener.h"
#include "Sockets/PlatformSocket.h"

namespace Rt2::Html
{

    using Socket          = Sockets::Net::Socket;
    using RequestListener = Http::RequestListener;

    class Server
    {
    private:
        Socket           _srv{Sockets::Net::InvalidSocket};
        RequestListener* _requestListener{nullptr};

        void acceptConnections() const;
        void tryProcess(const Socket & sock) const;

    public:
        Server();
        ~Server();

        void setListener(RequestListener* listener);

        bool start(const String& address, uint16_t port);

        void runSignaled() const;

        void runDetached() const;
    };

}  // namespace Rt2::Html
