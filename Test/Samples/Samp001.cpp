#include "Html/Server.h"
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
        void handle(const Http::Request& request,
                    Http::Response&      response) override
        {
            if (request.method().isTypeOf(Http::Method::Get))
            {
                if (const String& path = request.url().path(); 
                    path == "/" || path == "/index.html")
                {
                    if (InputFileStream ifs(TestFile("Samp001/index.html")); 
                        ifs.is_open())
                        response.write(ifs, "text/html");
                }
            }
            else
            {
                response.writeNotFound();
            }
        }
    };

    const Http::Url url("http://127.0.0.1:5000/");

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