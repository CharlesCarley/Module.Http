#include "Html/Document.h"
#include "Html/Server.h"
#include "Http/ContentType.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Http/Url.h"
#include "Samples/ThisDir.h"
#include "Utils/Exception.h"

using namespace Rt2;

class Response final : public Http::RequestListener
{
private:
    PathUtil _curPath{CurrentSourceDirectory};

public:
    static void respondFile(const Http::Response&    response,
                            const Http::ContentType& content,
                            const String&            path)
    {
        if (InputFileStream ifs(Su::join(TestFile("Samp001/"), path));
            ifs.is_open())
            response.write(ifs, content.type());
        else
            response.writeNotFound();
    }

    void handle(const Http::Request& request,
                Http::Response&      response) override
    {
        if (request.method().isTypeOf(Http::Method::Get))
        {
            String path = request.url().path();

            path = path.empty() || path == "/" ? "index.html" : path;

            if (const Http::ContentType ct(PathUtil{path}.lastExtension());
                ct.type() != Http::ContentType::Undefined)
                respondFile(response, ct, path);
            else
                response.writeNotFound();
        }
        else
            response.writeNotFound();
    }
};

void go()
{
    const Http::Url url("http://127.0.0.1:8080");
    Html::Server    s;
    s.setRoot(TestFile("Samp001"));

    Response l;
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
    catch (Exception& ex)
    {
        Console::writeError(ex.what());
        return -5;
    }
}