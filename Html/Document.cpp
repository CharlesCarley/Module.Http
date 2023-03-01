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
#include "Html/Command.h"
#include "Utils/Char.h"
#include "Utils/Path.h"
#include "Utils/StreamMethods.h"
#include "Utils/TextStreamWriter.h"

namespace Rt2::Html
{

    String textSize(TextSize sz)
    {
        return Su::join("fs-", (int)sz);
    }

    String textAlign(const TextAlignment al)
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

    String toArray(StringArray& arr)
    {
        bool   f = true;
        String str;
        for (auto& ele : arr)
        {
            if (f)
            {
                f = false;
            }
            else
                str.push_back(' ');
            str.append(ele);
        }
        arr.clear();
        return str;
    }

    String background(const ColorIndex idx)
    {
        return Su::join('b', idx);
    }

    String foreground(const ColorIndex idx)
    {
        return Su::join('f', idx);
    }
    Document::Document() = default;

    Document::~Document() = default;

    void Document::set(TextAlignment al)
    {
        _style.push_back(textAlign(al));
    }

    void Document::set(TextSize size)
    {
        _style.push_back(textSize(size));
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

    void Document::beginContainerDiv(const bool stretch)
    {
        _style.push_back(stretch ? "container-fluid" : "container");
        _style.push_back(background(_bg));
        _style.push_back(foreground(_fg));
        Ts::print(_out, "<div", AttrString("class", toArray(_style)), ">");
    }

    void Document::beginDivRow(const TextAlignment al)
    {
        _style.push_back("row");
        _style.push_back(background(_bg));
        _style.push_back(foreground(_fg));
        Ts::print(_out, "<div", AttrString("class", toArray(_style)), ">");
    }

    void Document::beginDivCol(const TextAlignment al)
    {
        _style.push_back("col");
        _style.push_back(background(_bg));
        _style.push_back(foreground(_fg));
        Ts::print(_out, "<div", AttrString("class", toArray(_style)), ">");
    }

    void Document::endDiv()
    {
        Ts::print(_out, "</div>");
    }

    void Document::beginSection(const String& title)
    {
        _sectionCount = Min(++_sectionCount, 6);
        Ts::print(_out,
                  "<h",
                  _sectionCount,
                  '>',
                  title,
                  "</h",
                  _sectionCount,
                  '>');
    }

    void Document::endSection()
    {
        _sectionCount = Max(--_sectionCount, 0);
    }

    void Document::br()
    {
        Ts::print(_out, "<br/>");
    }

    void Document::paragraph(const String& text, const TextSize size, const TextAlignment al)
    {
        _style.push_back(textSize(size));
        _style.push_back(textAlign(al));
        _style.push_back(foreground(_fg));

        Ts::print(_out,
                  "<p",
                  AttrString("class", toArray(_style)),
                  ">",
                  text,
                  "</p>");
    }

    const String& Document::flush()
    {
        _data = _out.str();
        _out.str("");
        return _data;
    }

}  // namespace Rt2::Html
