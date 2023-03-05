#include "Html/Document.h"
#include "Html/Server.h"
#include "Http/ContentType.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Http/Url.h"
#include "Utils/CommandLine/Parser.h"
#include "Utils/Directory/Path.h"
#include "Utils/Exception.h"
#include "Utils/StreamMethods.h"
#include "Utils/Win32/CrtUtils.h"

namespace Rt2::HtmlSample
{

    enum Options
    {
        OP_HOST,
        OP_ROOT,
        OP_BRO_ROOT,
        OP_MAX,
    };

    constexpr CommandLine::Switch Switches[OP_MAX] = {
        {    OP_HOST, 0,   "host",     "specify the address and port", false, 1},
        {    OP_ROOT, 0,   "root",  "specify the root server address", false, 1},
        {OP_BRO_ROOT, 0, "browse", "specify the root browser address", false, 1},
    };

    class DirectoryPage
    {
    private:
        Html::Document  _doc;
        Directory::Path _root;
        Http::Request   _request;

    public:
        explicit DirectoryPage(const Directory::Path& root, const Http::Request& request) :
            _root(root),
            _request(request)
        {
        }

        void writeTitle(const Directory::Path& path)
        {
            Directory::Path pth = path.relativeTo(_root);

            StringDeque dirs = path.directories();

            _doc.backgroundColor(-1);
            _doc.padding(Html::All, 1);
            _doc.beginNav("Home", "/");
            _doc.beginNavList();
            _doc.margin(Html::Horizontal, 1);
            _doc.navItem("/");

            if (!dirs.empty())
            {
                String acc = "/";
                while (!dirs.empty())
                {
                    String dir = dirs.front();
                    dirs.pop_front();

                    acc = Su::join(acc, dir, '/');

                    _doc.margin(Html::Horizontal, 1);
                    _doc.navItem(dir, acc);
                    _doc.margin(Html::Horizontal, 1);
                    _doc.navItem("/");
                }
            }
            _doc.endList();
            _doc.endNav();
        }

        void
        writeDirectory(const Directory::Path& path)
        {
            Console::nl();
            Console::setForeground(CS_CYAN);
            Console::writeLine("", Tab(2), path.full());
            Console::nl();

            _doc.beginDivRow();

            _doc.beginDivCol();
            if (path.isDirectory())
            {
                Directory::PathArray items;
                path.list(items, true);
                int i = 0;

                if (!items.empty())
                    _doc.beginGroupList();

                for (const Directory::Path& item : items)
                {
                    Directory::Path local = item.relativeTo(_root);

                    if (!item.isDotDirectory() && !item.isSymLink())
                    {
                        if (++i % 2)
                            _doc.backgroundColor(0);
                        else
                            _doc.backgroundColor(1);

                        _doc.borderColor(1);
                        if (item.isDirectory())
                            _doc.listGroupItem(local.lastDirectory(), local.full());
                        else if (item.isFile())
                            _doc.listGroupItem(local.base(), local.full());
                    }
                }
                if (!items.empty())
                    _doc.endList();
            }
            else
            {
                InputFileStream is;
                if (path.open(is))
                    _doc.code(is);
            }
            _doc.endDiv();

            _doc.beginDivCol();
            _doc.endDiv();

            _doc.endDiv();
        }

        void render(const Http::Response& response)
        {
            const Directory::Path current(_request.path());

            _doc.begin();
            writeTitle(current);

            _doc.beginContainerDiv(true);

            _doc.color(9);
            _doc.backgroundColor(0);
            _doc.margin(Html::Top, 2);
            _doc.padding(Html::All, 0);
            _doc.heading(Su::join("Index of ", '~', _request.path()), 5);
            writeDirectory(_root.append(current));

            _doc.endDiv();
            _doc.end();
            response.write(_doc.flush(), Http::ContentType::TextHtml);
        }
    };

    class App final : public Http::RequestListener
    {
    private:
        Http::Url       _url{};
        Directory::Path _root;
        Directory::Path _browse;

    public:
        bool parse(const int argc, char** argv)
        {
            CommandLine::Parser p;
            if (p.parse(argc, argv, Switches, OP_MAX) < 0)
                return false;

            if (!p.isPresent(OP_HOST))
                throw Exception("The required --host option is not present.");
            if (!p.isPresent(OP_ROOT))
                throw Exception("The required --root option is not present.");
            if (!p.isPresent(OP_BRO_ROOT))
                throw Exception("The required --root option is not present.");

            _url = Http::Url{p.string(OP_HOST)};

            String path = p.string(OP_ROOT);
            if (!Su::endsWith(path, '/'))
                path.push_back('/');
            _root = Directory::Path{path};

            path = p.string(OP_BRO_ROOT);
            if (!Su::endsWith(path, '/'))
                path.push_back('/');

            _browse = Directory::Path{path};

            Console::writeLine(
                "Server Starting : ",
                _url.value());
            Console::writeLine(
                "From Directory  : ",
                _root.relativeTo(CommandLine::Parser::currentDirectory()).full());
            return true;
        }

        void handle(const Http::Request& request,
                    Http::Response&      response) override
        {
            if (Directory::Path rp = _root.append(request.path());
                rp.base() == "site.css")
            {
                if (InputFileStream ifs; rp.open(ifs))
                    response.write(ifs, Http::ContentType::TextCss);
            }
            else
            {
                if (request.method().type() == Http::Method::Get)
                {
                    DirectoryPage page(_browse, request);
                    page.render(response);
                }
            }
        }

        int go()
        {
            Html::Server s;
            s.setRoot(_root.full());

            s.setListener(this);
            s.start(_url.authority(), _url.port());
            s.runSignaled();
            return 0;
        }
    };

}  // namespace Rt2::HtmlSample

int main(const int argc, char** argv)
{
    int rc = 1;
    Rt2::CrtTestMemory();
    try
    {
        if (Rt2::HtmlSample::App a;
            a.parse(argc, argv))
            rc = a.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeError(ex.what());
    }

    Rt2::CrtDump();
    return rc;
}