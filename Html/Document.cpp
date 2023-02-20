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
#include "Utils/Path.h"



namespace Rt2::Html
{
    HtmlDocumentWriter::HtmlDocumentWriter() :
        _sectionDepth(1)
    {
    }

    HtmlDocumentWriter::~HtmlDocumentWriter() = default;

    void HtmlDocumentWriter::beginDocument(OStream& output, const String& title)
    {
        output << R"(<!DOCTYPE html>)" << std::endl;
        output << R"(<html>)" << std::endl;
        output << "<head>" << std::endl;
        output << R"(<meta http-equiv="Content-Type" content="text/xhtml;charset=UTF-8"/>)" << std::endl;
        output << R"(<meta http-equiv="X-UA-Compatible" content="IE=9" />)" << std::endl;
        output << R"(<meta http-equiv="Content-Type" content="text/xhtml;charset=UTF-8"/>)" << std::endl;
        output << R"(<meta name="robots" content="noindex" />)" << std::endl;
        output << R"(<meta name="generator" content="MdDox"/>)" << std::endl;
        output << R"(<meta name="viewport" content="width=device-width, initial-scale=1"/>)" << std::endl;
        output << "<title>" << title << "</title>" << std::endl;
        output << "</head>" << std::endl;
        output << "<body>" << std::endl;

        Html::beginDivSection(output, "document");
        Html::beginDivSection(output, "document-content");
        Html::heading(output, 1, title);
    }

    void HtmlDocumentWriter::endDocument(OStream& output, const String& docSource)
    {
        Html::endDivSection(output, "document-content");
        Html::endDivSection(output, "document");

        output << "</body>" << std::endl;
        output << "</html>" << std::endl;
    }

    void HtmlDocumentWriter::addSection(OStream& output, const String& title, int depth)
    {
        Html::heading(output, depth, title);
    }

    void HtmlDocumentWriter::writeSection(OStream& output, const String& title) const
    {
        Html::heading(output, _sectionDepth, title);
    }

    void HtmlDocumentWriter::beginSection(OStream& output, const String& title, const int depth)
    {
        if (depth < 0)
            _sectionDepth++;
        else
            _sectionDepth = depth;

        if (_sectionDepth > 6)
            _sectionDepth = 6;

        writeSection(output, title);
    }

    void HtmlDocumentWriter::endSection(OStream& output)
    {
        --_sectionDepth;
        if (_sectionDepth < 0)
            _sectionDepth = 0;
    }

    void HtmlDocumentWriter::beginSectionBar(OStream& output)
    {
        Html::beginDivSection(output, "section-bar");
    }

    void HtmlDocumentWriter::endSectionBar(OStream& output)
    {
        Html::endDivSection(output, "section-bar");
    }

    void HtmlDocumentWriter::beginMethod(OStream& output, const String& title, const String& id)
    {
        _sectionDepth++;
        Html::heading(output, _sectionDepth, title);
    }

    void HtmlDocumentWriter::endMethod(OStream& output)
    {
        endSection(output);
    }

    void HtmlDocumentWriter::beginList(OStream& output, const String& header)
    {
        if (!header.empty())
        {
            Html::beginDivSection(output, "list-heading");
            Html::boldText(output, header);
            Html::endDivSection(output, "list-heading");
        }

        Html::beginOrderedList(output);
    }

    void HtmlDocumentWriter::endList(OStream& output)
    {
        Html::endOrderedList(output);
    }

    void HtmlDocumentWriter::beginParagraph(OStream& output)
    {
        Html::beginParagraph(output);
    }

    void HtmlDocumentWriter::endParagraph(OStream& output)
    {
        Html::endParagraph(output);
    }

    void HtmlDocumentWriter::beginBlockQuote(OStream& output)
    {
        Html::beginBlockQuote(output);
    }

    void HtmlDocumentWriter::endBlockQuote(OStream& output)
    {
        Html::endBlockQuote(output);
    }

    void HtmlDocumentWriter::beginListItem(OStream& output)
    {
        Html::beginListItem(output);
    }

    void HtmlDocumentWriter::endListItem(OStream& output)
    {
        Html::endListItem(output);
    }

    void HtmlDocumentWriter::paragraph(OStream& output, const String& text)
    {
        Html::paragraph(output, text);
    }

    void HtmlDocumentWriter::inlineText(OStream& output, const String& text)
    {
        Html::inlineText(output, text);
    }

    void HtmlDocumentWriter::boldText(OStream& output, const String& text)
    {
        Html::boldText(output, text);
    }

    void HtmlDocumentWriter::italicText(OStream& output, const String& text)
    {
        Html::italicText(output, text);
    }

    void HtmlDocumentWriter::typewriterText(OStream& output, const String& text)
    {
        Html::typewriterText(output, text);
    }

    void HtmlDocumentWriter::code(OStream& output, const String& text, const String& type)
    {
        Html::code(output, text);
    }

    void HtmlDocumentWriter::image(OStream& output, const String& src)
    {
        Html::embedImage(output, src);
    }

    void HtmlDocumentWriter::listItem(OStream& output, const String& title, const String& href)
    {
        String tVal;
        Su::trimWs(tVal, title);

        if (!href.empty())
        {
            String link;
            Su::replaceAll(link, href, "\\", "/");

            Html::beginListItem(output);
            Html::beginLink(output, link);
            output << tVal;
            Html::endLink(output);
            Html::endListItem(output);
        }
        else
        {
            Html::beginListItem(output);
            output << tVal;
            Html::endListItem(output);
        }
    }

    void HtmlDocumentWriter::listIcon(OStream& output, const String& image, const String& href)
    {
        if (!href.empty())
        {
            const PathUtil path(href);
            Html::linkImage(output, image, path.fullPath());
        }
    }

    void HtmlDocumentWriter::anchor(OStream& output, const String& id)
    {
        Html::anchor(output, id);
    }

    void HtmlDocumentWriter::horizontalRule(OStream& output)
    {
        Html::horizontalRule(output);
    }

    void HtmlDocumentWriter::lineBreak(OStream& output)
    {
        Html::lineBreak(output);
    }

    void HtmlDocumentWriter::linkUrl(OStream& output, const String& title, const String& ref)
    {
    }

    void HtmlDocumentWriter::linkText(OStream& output, const String& title, const String& ref)
    {
    }

}  // namespace Rt2::Html
