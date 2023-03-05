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
#pragma once
#include "Utils/Definitions.h"
#include "Utils/FileSystem.h"
#include "Utils/String.h"

namespace Rt2::Html
{
    enum TextAlignment
    {
        AlignStart,
        AlignCenter,
        AlignEnd,
    };

    enum TextSize
    {
        ExtraLarge = 1,
        Large      = 2,
        Medium     = 5,
        Small      = 6,
    };

    enum BoxOp
    {
        Left       = 0x01,
        Top        = 0x02,
        Right      = 0x04,
        Bottom     = 0x08,
        Horizontal = Left | Right,
        Vertical   = Top | Bottom,
        All        = Left | Top | Right | Bottom,
    };

    class Document
    {
    private:
        OutputStringStream _out;
        String             _data;
        StringArray        _style;

        void tag(const String& tag, const String& text);

        void linkRefTag(const String& tag, const String& text, const String& href);

        void openTag(const String& tag);

        void openRefTag(const String& tag, const String& href);

        void refTag(const String& tag, const String& text, const String& href);

        void closeTag(const String& tag);

    public:
        Document();

        ~Document();

        void textAlign(TextAlignment al);

        void fontSize(TextSize size);

        void margin(BoxOp dir, int idx);

        void padding(BoxOp dir, int idx);

        void border(BoxOp dir, int idx);

        void backgroundColor(int idx);

        void borderColor(int idx);

        void color(int idx);

        void set(const String& val);

        void beginDocument(const String& header);

        void endDocument(const String& footer);

        void display(const String& text, int idx);

        void heading(const String& text, int idx);

        void headingRef(const String& text, const String& ref, int idx);

        void beginNav(const String& title, const String& home);

        void beginNavList();

        void navItem(const String& text);

        void navItem(const String& text, const String& ref);

        void beginGroupList();

        void listGroupItem(const String& text);

        void listGroupItem(const String& text, const String& ref);

        void endNav();

        void endList();

        void beginContainerDiv(bool stretch = true);

        void beginDivRow(TextAlignment al = AlignStart);

        void beginDivCol(TextAlignment al = AlignStart);

        void beginDiv();

        void endDiv();

        void br();

        void begin();

        void end();

        void code(IStream& is);

        void paragraph(const String& text, TextSize size = Medium, TextAlignment al = AlignStart);

        void textRef(const String& title, const String& ref, TextSize size = Medium, TextAlignment al = AlignStart);

        const String& flush();
    };

}  // namespace Rt2::Html
