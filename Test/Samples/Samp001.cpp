#include "Html/Document.h"
#include "Html/Server.h"
#include "Http/ContentType.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Http/Url.h"
#include "Samples/ThisDir.h"

using namespace Rt2;

class Page : public Html::Document
{
public:
    void begin()
    {
        setBackground(Html::Color2);
        setForeground(Html::Color0);

        beginDocument(TestFile("Samp001/header.html"));
        beginContainerDiv(true);
    }

    void end()
    {
        endDiv();
        endDocument(TestFile("Samp001/footer.html"));
    }

    void writeDemo()
    {
        setBackground(Html::Color2);
        setForeground(Html::Color0);

        beginContainerDiv(true);
        beginDivRow();

        set("min-vh-10");
        beginDivCol();
        paragraph("FileBrowser", Html::Medium, Html::AlignStart);
        endDiv();

        beginDivRow();
        setBackground(Html::Color8);
        setForeground(Html::Color0);
        set("p-3");
        set("ms-1");
        beginDivCol();
        paragraph("AAA", Html::Medium, Html::AlignCenter);
        endDiv();

        setBackground(Html::Color7);
        setForeground(Html::Color0);
        set("p-3");
        set("ms-1");
        set("min-vh-90");
        beginDivCol();
        paragraph("BBBB", Html::Medium, Html::AlignCenter);
        endDiv();
        endDiv();

        endDiv();
        endDiv();
    }

    void writeHeader()
    {
        setBackground(Html::Color2);
        setForeground(Html::Color0);

        beginContainerDiv(true);
        beginDivCol();

        paragraph("FileBrowser", Html::Medium, Html::AlignStart);

        endDiv();
        endDiv();
    }
};

class Response final : public Http::RequestListener
{
private:
    PathUtil _curPath{CurrentSourceDirectory};

public:
    static void respondFile(const Http::Response& response, const String& path)
    {
        const PathUtil pu = PathUtil(path);
        if (const Http::ContentType content(pu.lastExtension());
            content.type() != Http::ContentType::Undefined)
        {
            if (InputFileStream ifs(Su::join(TestFile("Samp001/"), path));
                ifs.is_open())
                response.write(ifs, content.type());
            else
                response.writeNotFound();
        }
        else
        {
            response.writeNotFound();
        }
    }

    void handle(const Http::Request& request,
                Http::Response&      response) override
    {
        if (request.method().isTypeOf(Http::Method::Get))
        {
            String path = request.url().path();
            path        = path.empty() ? "index.html" : path;

            if (const Http::ContentType ct(PathUtil{path}.lastExtension());
                ct.type() != Http::ContentType::Undefined)
                respondFile(response, path);
            else
                response.writeNotFound();
        }
        else
            response.writeNotFound();
    }
};

void go()
{
    const Http::Url url("http://127.0.0.1");

    Html::Server s;
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
    catch (...)
    {
        return -5;
    }
}