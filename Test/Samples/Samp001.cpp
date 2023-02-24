#include "Html/Server.h"
#include "Http/ContentType.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Http/Url.h"
#include "Samples/ThisDir.h"

using namespace Rt2;

void go()
{
    class Listener final : public Http::RequestListener
    {
    public:
        void handle(const Http::Request& request, Http::Response& response) override
        {
            if (request.method().isTypeOf(Http::Method::Get))
            {
                if (const String& path = request.url().path();
                    path == "/" || path == "/index.html")
                {
                    if (InputFileStream ifs(TestFile("Samp001/index.html"));
                        ifs.is_open())
                        response.write(ifs, Http::ContentType::TextHtml);
                }
                else if (path == "/style.css")
                {
                    if (InputFileStream ifs(TestFile("Samp001/style.css"));
                        ifs.is_open())
                        response.write(ifs, Http::ContentType::TextCss);
                }
            }
            else
            {
                response.writeNotFound();
            }
        }
    };

    const Http::Url url("localhost");

    Html::Server s;
    s.setRoot(TestFile("Samp001"));

    Listener l;
    s.setListener(&l);
    s.start(url.authority(), url.port());
    s.runSignaled();
}

int main(int, char**)
{
    try
    {
        go();
        return 0;
    }
    catch (...)
    {
        return -5;
    }
}