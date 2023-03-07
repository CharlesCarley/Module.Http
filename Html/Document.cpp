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
#include "Test/Samples/Resource.h"
#include "Utils/Char.h"
#include "Utils/StreamMethods.h"
#include "Utils/TextStreamWriter.h"

namespace Rt2::Html
{
    using C = AttrString;
    using M = AttributeMap;

    Document::Document()
    {
        save();
    }

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

    String faOp(const int idx)
    {
        String attr;
        attr.push_back('f');
        attr.push_back('a');
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
            return Su::join(st, "s-", idx);
        case Right:
            return Su::join(st, "e-", idx);
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

    String breakOp(const String& type, const BreakSize br, int idx)
    {
        switch (br)
        {
        case BreakFlex:
            return Su::join(type, "-flex");
        case BreakSmall:
            return Su::join(type, "-sm-", idx);
        case BreakMedium:
            return Su::join(type, "-md-", idx);
        case BreakLarge:
            return Su::join(type, "-lg-", idx);
        case BreakExtraLarge:
            return Su::join(type, "-xl-", idx);
        case BreakNone:
        default:
            return type;
        }
    }

    String overflowOp(OverFlow op)
    {
        switch (op)
        {
        case OverFlowHide:
            return "of-0";
        case OverFlowAny:
            return "of-1";
        case OverFlowX:
            return "of-x";
        case OverFlowY:
            return "of-y";
        case OverFlowNone:
        default:
            return "";
        }
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

    void Document::textAlign(const TextAlignment al) const
    {
        top().style.push_back(textAlignOp(al));
    }

    void Document::fontSize(const TextSize size) const
    {
        top().style.push_back(textSizeOp(size));
    }

    void Document::margin(const BoxOp dir, const int idx) const
    {
        top().style.push_back(spaceOp(dir, 'm', idx));
    }

    void Document::gutter(BoxOp dir, int idx) const
    {
        top().style.push_back(spaceOp(dir, 'g', idx));
    }

    void Document::padding(const BoxOp dir, const int idx) const
    {
        top().style.push_back(spaceOp(dir, 'p', idx));
    }

    void Document::set(const String& val) const
    {
        top().style.push_back(val);
    }

    void Document::beginDocument(const String& header) const
    {
        if (InputFileStream ifs(header);
            ifs.is_open())
            Su::copy(_out, ifs, false, false);
    }

    void Document::endDocument(const String& footer) const
    {
        if (InputFileStream ifs(footer);
            ifs.is_open())
            Su::copy(_out, ifs, false, false);
    }

    void Document::beginDoc(const String& style) const
    {
        Ts::print(_out, "<!DOCTYPE html>");
        Ts::print(_out, R"(<html lang="en-us" data-bs-theme="dark">)");
        Ts::print(_out, R"(<head>)");
        Ts::print(_out, R"(<meta name="viewport" content="width=device-width, initial-scale=1">)");
        Ts::print(_out, R"(<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css")"
                        R"( rel="stylesheet")"
                        R"( integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD")"
                        R"( crossorigin="anonymous">)");

        save();
        if (!style.empty())
            tag("style", style);
        Ts::print(_out, R"(</head>)");
        restore();

        openTag("body");
    }

    void Document::endDoc() const
    {
        Ts::print(_out, R"(<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js")"
                        R"( integrity="sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN")"
                        R"( crossorigin="anonymous"></script>)");
        Ts::print(_out, R"(</body>)");
        Ts::print(_out, R"(</html>)");
    }

    void Document::noSpacing() const
    {
        set("m-0 p-0");
    }

    void Document::overflow(const OverFlow v) const
    {
        set(overflowOp(v));
    }

    void Document::attr(const String& key, const String& val) const
    {
        if (top().attrs.find(key) == top().attrs.end())
            top().attrs[key] = val;
    }

    void Document::openTag(const String& tag) const
    {
        Ts::print(_out,
                  '<',
                  tag,
                  ' ',
                  C("class", opArray(top().style)),
                  ' ',
                  C("id", top().id),
                  ' ',
                  M(top().attrs),
                  '>');
        top().clear();
    }

    void Document::openRefTag(const String& tag, const String& href) const
    {
        Ts::print(_out,
                  '<',
                  tag,
                  ' ',
                  C("class", opArray(top().style)),
                  ' ',
                  C("id", top().id),
                  ' ',
                  M(top().attrs),
                  ' ',
                  C("href", href),
                  '>');
        top().clear();
    }

    void Document::refTag(const String& tag,
                          const String& text,
                          const String& href) const
    {
        openRefTag(tag, href);
        Ts::print(_out, text);
        closeTag(tag);
    }

    void Document::closeTag(const String& tag) const
    {
        Ts::print(_out, '<', '/', tag, '>');
    }

    StyleData& Document::top() const
    {
        return _stack.top();
    }

    void StyleData::clear()
    {
        style.clear();
        attrs.clear();
        id.clear();
    }

    void Document::tag(const String& tag,
                       const String& text) const
    {
        openTag(tag);
        Ts::print(_out, text);
        closeTag(tag);
    }

    void Document::linkRefTag(const String& tag, const String& text, const String& href) const
    {
        openTag(tag);
        set(top().accent);
        refTag("a", text, href);
        closeTag(tag);
    }

    void Document::br() const
    {
        Ts::print(_out, "<br/>");
    }

    void Document::display(const String& text, const int idx) const
    {
        top().style.push_back(displayOp(idx));
        tag("p", text);
    }

    void Document::heading(const String& text, const int idx) const
    {
        top().style.push_back(headingOp(idx));
        tag("p", text);
    }

    void Document::headingRef(const String& text, const String& ref, const int idx) const
    {
        top().style.push_back(headingOp(idx));
        refTag("a", text, ref);
    }

    void Document::beginNav() const
    {
        set("navbar navbar-expand");
        openTag("nav");

        set("collapse navbar-collapse");
        openTag("div");
    }

    void Document::endNav() const
    {
        closeTag("div");
        closeTag("nav");
    }

    void Document::beginNavList() const
    {
        padding(All, 1);
        set("navbar-nav");
        openTag("ul");
        margin(Left, 1);
    }

    void Document::navItem(const String& text) const
    {
        set("nav-item");
        tag("li", text);
    }

    void Document::navItem(const String& text, const String& ref) const
    {
        set("nav-item");
        linkRefTag("li", text, ref);
    }

    void Document::beginGroupList() const
    {
        set("list-group list-group-flush");
        openTag("ul");
    }

    void Document::save() const
    {
        _stack.push({});
    }

    void Document::copy() const
    {
        _stack.push(top());
    }

    void Document::restore() const
    {
        if (_stack.size() > 1)
            _stack.pop();
    }

    void Document::listGroupItem(const String& text) const
    {
        set("list-group-item");
        tag("li", text);
    }

    void Document::listGroupItem(const String& text, const String& ref) const
    {
        set("list-group-item");
        linkRefTag("li", text, ref);
    }

    void Document::endList() const
    {
        closeTag("ul");
    }

    void Document::beginHeader() const
    {
        set("sticky-top");
        openTag("header");
    }

    void Document::endHeader() const
    {
        closeTag("header");
    }

    void Document::beginAside() const
    {
        openTag("aside");
    }

    void Document::endAside() const
    {
        closeTag("aside");
    }

    void Document::beginMain() const
    {
        openTag("main");
    }

    void Document::flex() const
    {
        set("d-flex");
    }

    void Document::endMain() const
    {
        closeTag("main");
    }

    void Document::beginFooter() const
    {
        openTag("footer");
    }

    void Document::endFooter() const
    {
        closeTag("footer");
    }

    void Document::border(const BoxOp dir, const int idx) const
    {
        top().style.push_back(borderOp(dir, idx));
    }

    void Document::backgroundColor(const int idx) const
    {
        top().style.push_back(bgOp(idx));
    }

    void Document::borderColor(const int idx) const
    {
        top().style.push_back(borderColorOp(idx));
    }

    void Document::color(const int idx) const
    {
        top().style.push_back(fgOp(idx));
    }

    void Document::accent(const int idx) const
    {
        top().accent = faOp(idx);
    }

    void Document::id(const String& val) const
    {
        top().id = val;
    }

    void Document::beginContainerDiv(const bool stretch) const
    {
        top().style.push_back(stretch ? "container-fluid" : "container");
        openTag("div");
    }

    void Document::beginDivRow(const BreakSize br,
                               const int       idx) const
    {
        top().style.push_back(breakOp("row", br, idx));
        openTag("div");
    }

    void Document::beginDivCol(const BreakSize br,
                               const int       idx) const
    {
        top().style.push_back(breakOp("col", br, idx));
        openTag("div");
    }

    void Document::beginDiv() const
    {
        openTag("div");
    }

    void Document::endDiv() const
    {
        closeTag("div");
    }

    void Document::paragraph(const String& text) const
    {
        tag("p", text);
    }

    void Document::code(IStream& is) const
    {
        OutputStringStream oss;
        Su::copy(oss, is, false);
        tag("pre", oss.str());
    }

    void Document::code(const String& str) const
    {
        tag("pre", str);
    }

    void Document::textRef(const String&       title,
                           const String&       ref,
                           const TextSize      size,
                           const TextAlignment al) const
    {
        top().style.push_back(textSizeOp(size));
        top().style.push_back(textAlignOp(al));

        refTag("a", title, ref);
    }

    void Document::beginTag(const String& tag) const
    {
        openTag(tag);
    }

    void Document::endTag(const String& tag) const
    {
        closeTag(tag);
    }

    const String& Document::flush()
    {
        _data = _out.str();
        _out.str("");
        return _data;
    }
}  // namespace Rt2::Html
