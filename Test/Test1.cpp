#include <cstdio>
#include "Html/Server.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Sockets/ClientSocket.h"
#include "Sockets/SocketStream.h"
#include "ThisDir.h"
#include "Threads/Task.h"
#include "Utils/String.h"
#include "gtest/gtest.h"

using namespace Rt2;

void ExpectThrow(const std::function<void()> fn)
{
    try
    {
        fn();
        FAIL();
    }
    catch (Exception&)
    {
        // empty
    }
}

void ExpectNoThrow(const std::function<void()> fn)
{
    try
    {
        fn();
    }
    catch (Exception&)
    {
        FAIL();
    }
}

GTEST_TEST(Http, Url_001)
{
    ExpectThrow([]
                { Http::Url u("foo.com"); });
    ExpectThrow([]
                { Http::Url u("file://"); });
    ExpectThrow([]
                { Http::Url u("https://"); });
    ExpectThrow([]
                { Http::Url u("http://foo-"); });
    ExpectThrow([]
                { Http::Url u("http://foo-bar-"); });
    ExpectThrow([]
                { Http::Url u("http://foo-bar-.com-:9876"); });
    ExpectThrow([]
                { Http::Url u("http://foo-bar-"); });
    ExpectNoThrow([]
                { Http::Url u("http://foo.bar:8080"); });
    ExpectNoThrow([]
                { Http::Url u("http://foo.bar:8080/a/b/c/d"); });

    const Http::Url u("http://foo.bar:8080/a/b/c/d");

    EXPECT_EQ(u.scheme(), "http");
    EXPECT_EQ(u.authority(), "foo.bar");
    EXPECT_EQ(u.port(), 8080);
    EXPECT_EQ(u.path(), "/a/b/c/d");
}

GTEST_TEST(Http, Http_001)
{
    Http::Request sc;
    StringStream  ss;
    ss << "GET http://127.0.0.1/index.html HTTP/1.1\n";
    sc.read(ss);
}

GTEST_TEST(Html, Html_001)
{
    class Listener final : public Http::RequestListener
    {
        bool _handled{false};

    public:
        void handle(const Http::Request& request,
                    Http::Response&      response) override
        {
            response.writeNotFound();
            _handled = true;
        }

        bool handled() const { return _handled; }
    };

    const Http::Url url("http://127.0.0.1:5000/");

    Html::Server s;
    Listener     l;
    s.setListener(&l);
    s.start(url.authority(), url.port());

    if (const Sockets::ClientSocket socket(url.authority(), url.port());
        socket.isOpen())
    {
        Http::Request req;
        req.setMethod(Http::Get);
        req.setUrl(url);
        socket.write(req.toString());
    }
    s.runSignaled();
    s.exit();
    EXPECT_TRUE(l.handled());
}
