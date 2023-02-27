#include "Html/Document.h"
#include "Html/Server.h"
#include "Http/ContentType.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Http/Url.h"
#include "Samples/ThisDir.h"

using namespace Rt2;

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
            {
                response.write(ifs, content.type());
            }
        }
        else
        {
            response.writeNotFound();
        }
    }

    static void respondMain(const Http::Response& response, const String& path)
    {
        PathUtil fileName(path);

        Html::Document doc;
        doc.setBackground(Html::Color3);
        doc.setForeground(Html::Color0);

        doc.beginDocument(TestFile("Samp001/header.html"));
        doc.beginContainerDiv(true);
        doc.beginDivCol();
        doc.paragraph(fileName.directory(), Html::Medium, Html::AlignStart);
        doc.endDiv();
        doc.endDiv();

        doc.setBackground(Html::Color0);
        doc.setForeground(Html::Color5);

        doc.beginContainerDiv(false);

        doc.beginDivRow();
        doc.paragraph(fileName.fullPath(), Html::Small, Html::AlignStart);
        doc.endDiv();

        doc.beginDivRow();
        doc.paragraph(fileName.fullPath(), Html::Small, Html::AlignCenter);
        doc.endDiv();
        doc.beginDivRow();
        doc.paragraph(fileName.fullPath(), Html::Small, Html::AlignEnd);
        doc.endDiv();

        doc.endDiv();

        doc.endDocument(TestFile("Samp001/footer.html"));
        response.write(doc.flush(), Http::ContentType::TextHtml);
    }

    void handle(const Http::Request& request,
                Http::Response&      response) override
    {
        if (request.method().isTypeOf(Http::Method::Get))
        {
            if (String path = request.url().path();
                path == "/" || path.empty())
            {
                if (!path.empty() && path[0] == '/')
                    path = path.substr(1, path.size());
                respondMain(response, Su::join(CurrentSourceDirectory, path));
            }
            else
                respondFile(response, path);
        }
        else
        {
            response.writeNotFound();
        }
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