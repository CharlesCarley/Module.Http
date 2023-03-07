#include "Html/Document.h"
#include "Html/Server.h"
#include "Http/ContentType.h"
#include "Http/Request.h"
#include "Http/Response.h"
#include "Http/Url.h"
#include "Resource.h"
#include "Utils/CommandLine/Parser.h"
#include "Utils/Directory/Path.h"
#include "Utils/Exception.h"
#include "Utils/StreamMethods.h"
#include "Utils/Time.h"
#include "Utils/Win32/CrtUtils.h"

namespace Rt2::HtmlSample
{
    using namespace Directory;

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

    class DirectoryPage : public Html::Document
    {
    private:
        Path            _root;
        Http::Request   _request;
        InputFileStream _curListing;

    public:
        explicit DirectoryPage(const Path& root, const Http::Request& request) :
            _root(root),
            _request(request)
        {
        }

        void logPath(const Path& path) const
        {
            Console::nl();
            Console::setForeground(CS_GREY);
            Console::write("", Tab(2), Hex(Time::now32()));
            Console::setForeground(CS_CYAN);
            Console::writeLine(" ", Tab(2), path.full());
            Console::nl();
        }

        void navListItem(const String& name, const String& href) const
        {
            accent(0);
            margin(Html::Horizontal, 1);
            margin(Html::Vertical, 0);
            navItem(name, href);
            color(7);
            margin(Html::Horizontal, 1);
            margin(Html::Vertical, 0);
            navItem("/");
        }

        void writeHeader(const Path& path) const
        {
            backgroundColor(-5);
            beginHeader();
            beginNav();

            Path        pth  = path.relativeTo(_root);
            StringDeque dirs = path.directories();

            beginNavList();
            navListItem("Home", "/");

            if (!dirs.empty())
            {
                String href = "/";
                while (!dirs.empty())
                {
                    const String& name = dirs.front();
                    href               = Su::join(href, name, '/');
                    navListItem(name, href);
                    dirs.pop_front();
                }
            }

            endList();
            endNav();

            backgroundColor(-4);
            borderColor(0);
            border(Html::Bottom, 1);
            margin(Html::Bottom, 1);
            beginDiv();
            noSpacing();

            color(9);
            textAlign(Html::AlignCenter);

            paragraph(
                Su::join('~', path.full()));
            endDiv();

            endHeader();
        }

        void writeSideBarList(const Path& path) const
        {
            if (const Path dir = path.directoryAsPath();
                dir.isDirectory())
            {
                Directory::PathArray items;
                dir.list(items, true);
                int i = 0;

                if (!items.empty())
                    beginGroupList();

                for (const Path& item : items)
                {
                    if (Path local = item.relativeTo(_root);
                        !local.isDotDirectory() &&
                        !item.isSymLink())
                    {
                        if (++i % 2)
                            backgroundColor(-4);
                        else
                            backgroundColor(-2);

                        borderColor(-2);

                        if (item.isDirectory())
                            listGroupItem(local.lastDirectory(), local.full());
                        else if (item.isFile())
                            listGroupItem(local.base(), local.full());
                    }
                }
                if (!items.empty())
                    endList();
            }
        }

        void writeSideBar(const Path& path) const
        {
            beginDivCol(Html::BreakSmall, 3);
            beginAside();
            writeSideBarList(path);
            endAside();
            endDiv();
        }

        void writeContent(const Path& path)
        {
            beginDivCol();
            beginMain();
            drawListing(path);
            endMain();
            endDiv();
        }

        void drawListing(const Path& path)
        {
            if (const Http::ContentType content(path.extension());
                content.isPlainText())
            {
                if (_curListing.is_open())
                    _curListing.close();

                if (path.open(_curListing))
                {
                    code(_curListing);
                    _curListing.close();
                }
                else
                {
                    backgroundColor(-5);
                    beginContainerDiv(true);
                    endDiv();
                }
            }
            else
            {
                if (path.open(_curListing, true))
                {
                    OutputStringStream oss;
                    Su::copy(oss, _curListing, true);

                    OutputStringStream hex;
                    Console::hexdump(hex, oss.str().data(), (uint32_t)oss.str().size());

                    code(hex.str());
                    _curListing.close();
                }
                else
                {
                    backgroundColor(-5);
                    beginContainerDiv(true);
                    endDiv();
                }
            }
        }

        void writeFooter(const Path& path) const
        {
            beginFooter();
            endFooter();
        }

        void render(const Http::Response& response)
        {
            const Path current(_request.path());
            const Path full = _root.append(current);
            logPath(full);

            String css;
            Resource::getSite(css);
            beginDoc(css);

            overflow(Html::OverFlowHide);
            writeHeader(current);

            noSpacing();
            overflow(Html::OverFlowHide);
            beginContainerDiv(true);
            beginDivRow();

            overflow(Html::OverFlowY);
            writeSideBar(full);

            overflow(Html::OverFlowY);
            writeContent(full);

            endDiv();
            endDiv();
            overflow(Html::OverFlowHide);
            writeFooter(current);

            endDoc();
            response.write(flush(), Http::ContentType::TextHtml);
        }
    };

    class App final : public Http::RequestListener
    {
    private:
        Http::Url _url{};
        Path      _root;
        Path      _browse;

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
            _root = Path{path};

            path = p.string(OP_BRO_ROOT);
            if (!Su::endsWith(path, '/'))
                path.push_back('/');

            _browse = Path{path};

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
            if (const Path rp =
                    _root.append(request.path());
                rp.base() == "site.css")
            {
                if (InputFileStream ifs;
                    rp.open(ifs))
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