#include <cstdio>
#include "Html/Server.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "ThisDir.h"
#include "Utils/String.h"
#include "gtest/gtest.h"

using namespace Rt2;

GTEST_TEST(Http, Http_001)
{
    Http::Request sc;
    StringStream  ss;
    ss << "GET /index.html HTTP/1.1\n";
    ss << "Host: 127.0.0.1";
    sc.read(ss);
}

GTEST_TEST(Html, Html_001)
{
    class Listener final : public Http::RequestListener
    {
    public:
        void handle(const Http::Request& request,
                    Http::Response&      response) override
        {
            response.writeNotFound();
        }
    };

    Html::Server s;
    Listener l;
    s.setListener(&l);
    s.start("127.0.0.1", 80);
}
