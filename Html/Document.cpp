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
    Document::Document() = default;

    Document::~Document() = default;

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

    String background(const ColorIndex idx)
    {
        return Su::join('b', idx);
    }

    String foreground(const ColorIndex idx)
    {
        return Su::join('f', idx);
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
        const String cont = stretch ? "container-fluid" : "container";
        Ts::print(_out,
                  "<div",
                  AttrString("class",
                             Su::csv(' ',
                                     cont,
                                     background(_bg))),
                  ">");
    }

    void Document::beginDivRow(const TextAlignment al)
    {
        Ts::print(_out,
                  "<div",
                  AttrString("class",
                             Su::csv(' ',
                                     "row",
                                     textAlign(al),
                                     background(_bg))),
                  ">");
    }

    void Document::beginDivCol(const TextAlignment al)
    {
        Ts::print(_out,
                  "<div",
                  AttrString("class",
                             Su::csv(' ',
                                     "col",
                                     textAlign(al),
                                     background(_bg))),
                  ">");
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
        String fontSize = Su::join("fs-", (int)size);
        Ts::print(_out,
                  "<p",
                  AttrString("class",
                             Su::csv(' ', fontSize, textAlign(al), foreground(_fg))),
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
