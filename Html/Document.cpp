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

    void Document::beginDocument(const String& header)
    {
        if (InputFileStream ifs(header);
            ifs.is_open())
            Su::copy(_out, ifs, false, true);
    }

    void Document::endDocument(const String& footer)
    {
        if (InputFileStream ifs(footer);
            ifs.is_open())
            Su::copy(_out, ifs, false, true);
    }

    void Document::beginContainerDiv()
    {
        Ts::print(_out, "<div ", AttrString("class", "container-fluid default"), ">");
    }

    void Document::beginDivRow()
    {
        Ts::print(_out, "<div ", AttrString("class", "row"), ">");
    }

    void Document::beginDivCol()
    {
        Ts::print(_out, "<div ", AttrString("class", "col"), ">");
    }

    void Document::endDiv()
    {
        Ts::print(_out, "</div>");
    }

    void Document::beginSection(const String& title)
    {
        _sectionCount = Min(++_sectionCount, 6);
        Ts::write(_out, 0, "<h", _sectionCount, '>', title, "</h", _sectionCount, '>');
    }

    void Document::endSection()
    {
        _sectionCount = Max(--_sectionCount, 0);
    }

    void Document::br()
    {
        Ts::print(_out, "<br/>");
    }

    void Document::paragraph(const String& text, int size)
    {
        Ts::print(_out, "<p ", AttrString("class", "par-" + Char::toString(size)), ">", text, "</p>");
    }

    const String& Document::flush()
    {
        _data = _out.str();
        _out.str("");
        return _data;
    }
}  // namespace Rt2::Html
