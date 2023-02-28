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

    enum ColorIndex
    {
        Color0 = 0,
        Color1,
        Color2,
        Color3,
        Color4,
        Color5,
        Color6,
        Color7,
        Color8,
        Color9,
    };

    class Document
    {
    private:
        int                _sectionCount{0};
        OutputStringStream _out;
        String             _data;
        ColorIndex         _bg{Color0};
        ColorIndex         _fg{Color9};
        StringArray        _style;

    public:
        Document();

        ~Document();

        void set(TextAlignment al);
        void set(TextSize size);
        void set(const String& val);

        void beginDocument(const String& header);

        void endDocument(const String& footer);

        void beginContainerDiv(bool stretch = true);


        void beginDivRow(TextAlignment al = AlignStart);

        void beginDivCol(TextAlignment al = AlignStart);

        void endDiv();

        void beginSection(const String& title);

        void endSection();

        void br();

        void paragraph(const String& text, TextSize size = Medium, TextAlignment al = AlignStart);

        void setBackground(ColorIndex ci) { _bg = ci; }
        void setForeground(ColorIndex ci) { _fg = ci; }

        const String& flush();
    };

}  // namespace Rt2::Html
