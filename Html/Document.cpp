/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "Html/Document.h"
#include "Utils/Char.h"
#include "Utils/StreamMethods.h"
#include "Utils/TextStreamWriter.h"

namespace Rt2::Html
{
    using C = AttrString;

    Document::Document() = default;

    Document::~Document() = default;

    String textAlignOp(const TextAlignment al)
    {
        switch (al)
        {
        default:
        case AlignStart:
            return "text-start";
        case AlignCenter:
            return "text-center";
        case AlignEnd:
            return "text-end";
        }
    }

    String textSizeOp(const TextSize sz)
    {
        String attr;
        attr.push_back('f');
        attr.push_back('s');
        attr.push_back('-');
        attr.append(Char::toString(sz));
        return attr;
    }

    String bgOp(const int idx)
    {
        String attr;
        attr.push_back('b');
        attr.append(Char::toString(idx));
        return attr;
    }

    String fgOp(const int idx)
    {
        String attr;
        attr.push_back('f');
        attr.append(Char::toString(idx));
        return attr;
    }

    String displayOp(const int sz)
    {
        String attr;
        attr.append("display-");
        attr.append(Char::toString(Clamp(sz, 1, 6)));
        return attr;
    }

    String headingOp(const int sz)
    {
        String attr;
        attr.push_back('h');
        attr.append(Char::toString(Clamp(sz, 1, 6)));
        return attr;
    }

    String spaceOp(const BoxOp dir, char st, int idx)
    {
        idx = Clamp(idx, 0, 5);

        switch (dir)
        {
        case Top:
            return Su::join(st, "t-", idx);
        case Left:
            return Su::join(st, "l-", idx);
        case Right:
            return Su::join(st, "r-", idx);
        case Bottom:
            return Su::join(st, "b-", idx);
        case Horizontal:
            return Su::join(st, "x-", idx);
        case Vertical:
            return Su::join(st, "y-", idx);
        case All:
        default:
            return Su::join(st, "-", idx);
        }
    }

    String borderOp(const BoxOp dir, int idx)
    {
        idx = Clamp(idx, 0, 5);
        String bdr;
        switch (dir)
        {
        case Top:
            return Su::join("border-top border-", idx);
        case Left:
            return Su::join("border-start border-", idx);
        case Right:
            return Su::join("border-end border-", idx);
        case Bottom:
            return Su::join("border-bottom border-", idx);
        case Horizontal:
            bdr = Su::join("border-top border-", idx);
            return Su::join(bdr, " border-bottom border-", idx);
        case Vertical:
            bdr = Su::join("border-start border-", idx);
            return Su::join(bdr, " border-end border-", idx);
        case All:
        default:
            return Su::join("border border-", idx);
        }
    }

    String borderColorOp(int idx)
    {
        idx = Clamp(idx, 0, 9);
        String r;
        r.push_back('b');
        r.push_back('c');
        r.push_back('-');
        r.append(Char::toString(idx));
        return r;
    }

    String opArray(StringArray& arr)
    {
        bool   first = true;
        String str;
        for (auto& ele : arr)
        {
            if (first)
                first = false;
            else
                str.push_back(' ');
            str.append(ele);
        }

        // so that it can empty the
        // array on the way out.
        arr.clear();
        return str;
    }

    void Document::textAlign(const TextAlignment al)
    {
        _style.push_back(textAlignOp(al));
    }

    void Document::fontSize(const TextSize size)
    {
        _style.push_back(textSizeOp(size));
    }

    void Document::margin(const BoxOp dir, const int idx)
    {
        _style.push_back(spaceOp(dir, 'm', idx));
    }

    void Document::padding(const BoxOp dir, const int idx)
    {
        _style.push_back(spaceOp(dir, 'p', idx));
    }

    void Document::set(const String& val)
    {
        _style.push_back(val);
    }

    void Document::beginDocument(const String& header)
    {
        if (InputFileStream ifs(header);
            ifs.is_open())
            Su::copy(_out, ifs, false, false);
    }

    void Document::endDocument(const String& footer)
    {
        if (InputFileStream ifs(footer);
            ifs.is_open())
            Su::copy(_out, ifs, false, false);
    }

    void Document::begin()
    {
        Ts::print(_out, "<!DOCTYPE html>");
        Ts::print(_out, R"(<html lang="en-us">)");
        Ts::print(_out, R"(<head>)");
        Ts::print(_out, R"(<meta name="viewport" content="width=device-width, initial-scale=1">)");
        Ts::print(_out, R"(<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css")"
                        R"( rel="stylesheet")"
                        R"( integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD")"
                        R"( crossorigin="anonymous">)");
        Ts::print(_out, R"(<link href="/.content/css/site.css" rel="stylesheet">)");
        Ts::print(_out, R"(</head>)");
        Ts::print(_out, R"(<body>)");
    }

    void Document::end()
    {
        Ts::print(_out, R"(<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js")"
                        R"( integrity="sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN")"
                        R"( crossorigin="anonymous"></script>)");
        Ts::print(_out, R"(</body>)");
        Ts::print(_out, R"(</html>)");
    }

    void Document::openTag(const String& tag)
    {
        Ts::print(_out, '<', tag, C("class", opArray(_style)), '>');
    }

    void Document::openRefTag(const String& tag, const String& href)
    {
        Ts::print(_out, '<', tag, C("class", opArray(_style)), C("href", href), '>');
    }

    void Document::refTag(const String& tag,
                          const String& text,
                          const String& href)
    {
        openRefTag(tag, href);
        Ts::print(_out, text);
        closeTag(tag);
    }

    void Document::closeTag(const String& tag)
    {
        Ts::print(_out, '<', '/', tag, '>');
    }

    void Document::tag(const String& tag,
                       const String& text)
    {
        openTag(tag);
        Ts::print(_out, text);
        closeTag(tag);
    }

    void Document::linkRefTag(const String& tag, const String& text, const String& href)
    {
        openTag(tag);
        refTag("a", text, href);
        closeTag(tag);
    }

    void Document::br()
    {
        Ts::print(_out, "<br/>");
    }

    void Document::display(const String& text, const int idx)
    {
        _style.push_back(displayOp(idx));
        tag("p", text);
    }

    void Document::heading(const String& text, const int idx)
    {
        _style.push_back(headingOp(idx));
        tag("p", text);
    }

    void Document::headingRef(const String& text, const String& ref, const int idx)
    {
        _style.push_back(headingOp(idx));
        refTag("a", text, ref);
    }

    void Document::beginNav(const String& title, const String& home)
    {
        const StringArray tmp = _style;
        _style.clear();

        padding(All, 0);
        margin(All, 0);
        set("navbar navbar-expand-lg");
        openTag("nav");

        _style = tmp;
        set("collapse navbar-collapse");
        openTag("div");

        margin(Left, 2);
        set("fa0");
        refTag("a", title, home);
    }

    void Document::beginNavList()
    {
        set("navbar-nav");
        openTag("ul");
    }

    void Document::navItem(const String& text)
    {
        set("nav-item");
        tag("li", text);
    }

    void Document::navItem(const String& text, const String& ref)
    {
        set("nav-item");
        linkRefTag("li", text, ref);
    }

    void Document::beginGroupList()
    {
        set("list-group list-group-flush");
        openTag("ul");
    }

    void Document::listGroupItem(const String& text)
    {
        set("list-group-item");
        tag("li", text);
    }

    void Document::listGroupItem(const String& text, const String& ref)
    {
        set("list-group-item");
        linkRefTag("li", text, ref);
    }

    void Document::endList()
    {
        closeTag("ul");
    }

    void Document::endNav()
    {
        closeTag("div");
        endList();
        closeTag("nav");
    }

    void Document::border(const BoxOp dir, const int idx)
    {
        _style.push_back(borderOp(dir, idx));
    }

    void Document::backgroundColor(const int idx)
    {
        _style.push_back(bgOp(idx));
    }

    void Document::borderColor(const int idx)
    {
        _style.push_back(borderColorOp(idx));
    }

    void Document::color(const int idx)
    {
        _style.push_back(fgOp(idx));
    }

    void Document::beginContainerDiv(const bool stretch)
    {
        _style.push_back(stretch ? "container-fluid" : "container");
        openTag("div");
    }

    void Document::beginDivRow(const TextAlignment al)
    {
        _style.push_back("row");
        openTag("div");
    }

    void Document::beginDivCol(const TextAlignment al)
    {
        _style.push_back("col");
        openTag("div");
    }

    void Document::beginDiv()
    {
        openTag("div");
    }

    void Document::endDiv()
    {
        closeTag("div");
    }

    void Document::paragraph(const String&       text,
                             const TextSize      size,
                             const TextAlignment al)
    {
        _style.push_back(textSizeOp(size));
        _style.push_back(textAlignOp(al));

        tag("p", text);
    }

    void Document::code(IStream& is)
    {
        OutputStringStream oss;
        Su::copy(oss, is, false);

        tag("pre", oss.str());
    }

    void Document::textRef(const String&       title,
                           const String&       ref,
                           const TextSize      size,
                           const TextAlignment al)
    {
        _style.push_back(textSizeOp(size));
        _style.push_back(textAlignOp(al));

        refTag("a", title, ref);
    }

    const String& Document::flush()
    {
        _data = _out.str();
        _out.str("");
        return _data;
    }
}  // namespace Rt2::Html
