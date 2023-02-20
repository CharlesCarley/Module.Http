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
#include "Utils/FileSystem.h"
#include "Utils/String.h"

namespace Rt2::Html
{
    class HtmlDocumentWriter
    {
    private:
        int _sectionDepth;

    protected:
        void writeSection(OStream& output, const String& title) const;

    public:
        HtmlDocumentWriter();

        ~HtmlDocumentWriter();

        void beginDocument(OStream& output, const String& title);

        void endDocument(OStream& output, const String& docSource = "");

        void addSection(OStream& output, const String& title, int depth);

        void beginSection(OStream& output, const String& title, int depth = -1);

        void endSection(OStream& output);

        void beginSectionBar(OStream& output);

        void endSectionBar(OStream& output);

        void beginMethod(OStream& output, const String& title, const String& id);

        void endMethod(OStream& output);

        void beginList(OStream& output, const String& header);

        void endList(OStream& output);

        void beginParagraph(OStream& output);

        void endParagraph(OStream& output);

        void beginBlockQuote(OStream& output);

        void endBlockQuote(OStream& output);

        void beginListItem(OStream& output);

        void endListItem(OStream& output);

        void paragraph(OStream& output, const String& text);

        void inlineText(OStream& output, const String& text);

        void boldText(OStream& output, const String& text);

        void italicText(OStream& output, const String& text);

        void typewriterText(OStream& output, const String& text);

        void code(OStream& output, const String& text, const String& type = ".txt");

        void image(OStream& output, const String& src);

        void listItem(OStream& output, const String& title, const String& ref);

        void listIcon(OStream& output, const String& image, const String& ref);

        void anchor(OStream& output, const String& id);

        void horizontalRule(OStream& output);

        void lineBreak(OStream& output);

        void linkUrl(OStream& output, const String& title, const String& ref);

        void linkText(OStream& output, const String& title, const String& ref);
    };
}  // namespace Rt2::Html
