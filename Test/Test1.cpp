#include <cstdio>
#include "Html/Server.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Http/Uri/Parser.h"
#include "Http/Uri/Scanner.h"
#include "Http/Uri/Token.h"
#include "Sockets/ClientSocket.h"
#include "Sockets/SocketStream.h"
#include "ThisDir.h"
#include "Threads/Task.h"
#include "Threads/Thread.h"
#include "Utils/String.h"
#include "gtest/gtest.h"

using namespace Rt2;

GTEST_TEST(Http, Uri_001)
{
    StringStream ss;
    ss << "/foo";
    Http::Uri::Scanner scn;
    scn.attach(&ss);

    TokenBase t0;
    // clang-format off
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_SLASH);
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_ID);
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_EOF);
    // clang-format on

    EXPECT_EQ(scn.state(), Http::Uri::Scanner::Relative);
}

GTEST_TEST(Http, Uri_002)
{
    StringStream ss;
    ss << "file:///foo";
    Http::Uri::Scanner scn;
    scn.attach(&ss);

    TokenBase t0;
    // clang-format off
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_ID);
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_COLON);
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_SLASH);
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_SLASH);
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_SLASH);
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_ID);
    scn.scan(t0); EXPECT_EQ(t0.type(), Http::Uri::TOK_EOF);
    // clang-format on
    EXPECT_EQ(scn.state(), Http::Uri::Scanner::Absolute);
}

GTEST_TEST(Http, Uri_003)
{
    StringStream ss;
    ss << "http://127.0.0.1/foo";
    Http::Uri::Parser p;
    p.read(ss);
    Http::Url url = p.url();

    EXPECT_EQ(url.scheme(), "http");
    EXPECT_EQ(url.authority(), "127.0.0.1");
    EXPECT_EQ(url.path(), "/foo");
}

GTEST_TEST(Http, Uri_004)
{
    EXPECT_NO_THROW({
        StringStream ss;
        ss << "127.0.0.1:54321/foo";
        Http::Uri::Parser p;
        p.read(ss);
        Http::Url url = p.url();

        EXPECT_EQ(url.scheme(), "http");  // defaults to http
        EXPECT_EQ(url.authority(), "127.0.0.1");
        EXPECT_EQ(url.path(), "/foo");
        EXPECT_EQ(url.port(), 54321);
    });
}

GTEST_TEST(Http, Url_001)
{

    EXPECT_ANY_THROW({ Http::Url u("https://"); });
    EXPECT_ANY_THROW({ Http::Url u("http://foo-"); });
    EXPECT_ANY_THROW({ Http::Url u("http://foo-bar-"); });
    EXPECT_ANY_THROW({ Http::Url u("http://foo-bar-.com-:9876"); });
    EXPECT_ANY_THROW({ Http::Url u("http://foo-bar-"); });

    EXPECT_NO_THROW({ Http::Url u("foo.com"); });
    EXPECT_NO_THROW({
        Http::Url u("file://");
        EXPECT_EQ(u.scheme(), "file");
        EXPECT_EQ(u.path(), "/");
    });
    EXPECT_NO_THROW({
        const Http::Url u("http://foo.bar:8080");
        EXPECT_EQ(u.scheme(), "http");
        EXPECT_EQ(u.authority(), "foo.bar");
        EXPECT_EQ(u.port(), 8080);
        EXPECT_EQ(u.path(), "/");
    });
    EXPECT_NO_THROW({
        const Http::Url u("http://foo.bar:8080/a/b/c/d");

        EXPECT_EQ(u.scheme(), "http");
        EXPECT_EQ(u.authority(), "foo.bar");
        EXPECT_EQ(u.port(), 8080);
        EXPECT_EQ(u.path(), "/a/b/c/d");
    });
}

GTEST_TEST(Http, Http_001)
{
    Http::Request sc;
    StringStream  ss;
    ss << "GET http://127.0.0.1/index.html HTTP/1.1\n";
    sc.read(ss);
    EXPECT_EQ(sc.method().type(), Http::Method::Get);
    EXPECT_EQ(sc.method().name(), "GET");

    const Http::Url& v = sc.url();
    EXPECT_EQ(v.scheme(), "http");
    EXPECT_EQ(v.authority(), "127.0.0.1");
    EXPECT_EQ(v.port(), 80);
    EXPECT_EQ(v.path(), "/index.html");
}
