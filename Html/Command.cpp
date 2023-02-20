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
#include "Html/Command.h"
#include "Html/Document.h"
#include "Utils/Char.h"

namespace Rt2::Html
{
    void lineBreak(OStream& output)
    {
        output << "<br/>" << std::endl;
    }

    void space(OStream& output, int i)
    {
        while (i-- > 0)
            output << ' ';
    }

    void beginDivSection(OStream& output, const char* name)
    {
        comment(output, name);
        output << "<div class=\"" << name << "\">" << std::endl;
    }

    void endDivSection(OStream& output, const char* name)
    {
        output << "</div>" << std::endl;
        comment(output, name);
    }

    void beginSection(OStream& output, const String& name, int depth)
    {
        depth = std::min(std::max(depth, 1), 6);

        const String className = Su::join("section-", depth);
        heading(output, depth, name);
        beginDivSection(output, className.c_str());
    }

    void endSection(OStream& output)
    {
        endDivSection(output, "section");
    }

    void beginBlockQuote(OStream& output)
    {
        output << "<blockquote>" << std::endl;
    }

    void endBlockQuote(OStream& output)
    {
        output << "</blockquote>" << std::endl;
    }

    void code(OStream& output, const String& code, const String& type)
    {
        beginDivSection(output, "code-block");
        output << "<pre><code>";

        if (!code.empty())
        {
            String cpy;
            Su::replaceAll(cpy, cpy, "&", "&amp;");
            Su::replaceAll(cpy, code, ">", "&gt;");
            Su::replaceAll(cpy, cpy, "<", "&lt;");
            Su::replaceAll(cpy, cpy, "\"", "&quot;");
            Su::replaceAll(cpy, cpy, "'", "&apos;");
            output << cpy;

            if (!isNewLine(code.back()))
                output << std::endl;
        }
        else
            output << std::endl;
        output << "</code></pre>" << std::endl;
        endDivSection(output, "code-block");
    }

    void beginParagraph(OStream& output)
    {
        beginDivSection(output, "paragraph");
        beginSpan(output, "paragraph");
    }

    void endParagraph(OStream& output)
    {
        endSpan(output);
        endDivSection(output, "paragraph");
    }

    void paragraph(OStream& output, const String& str)
    {
        beginParagraph(output);
        output << str;
        endParagraph(output);
    }

    void horizontalRule(OStream& output)
    {
        output << "<hr/>" << std::endl;
    }

    void anchor(OStream& output, const String& id)
    {
        String assertLower;
        Su::toLower(assertLower, id);
        output << "<a id=\"" << assertLower << "\"></a>" << std::endl;
    }

    void inlineText(OStream& output, const String& str, const String& className)
    {
        beginSpan(output, className.empty() ? "inline-text" : className);
        output << str;
        endSpan(output);
    }

    void inlineImage(OStream& output, const String& src, const String& className)
    {
        if (!className.empty())
            output << "<img src=\"" << src << "\" class=\"" << className << "\"/>";
        else
            output << "<img src=\"" << src << "\"/>";
    }

    void typewriterText(OStream& output, const String& str)
    {
        String out;
        Su::trimWs(out, str);
        output << "<code class=\"typewriter\">" << out << "</code>" << std::endl;
    }

    void boldText(OStream& output, const String& str)
    {
        String out;
        Su::trimWs(out, str);
        beginSpan(output, "bold-text");
        output << "<b>" << out << "</b>";
        endSpan(output);
    }

    void italicText(OStream& output, const String& str)
    {
        String out;
        Su::trimWs(out, str);

        beginSpan(output, "italic-text");
        output << "<i>" << out << "</i>";
        endSpan(output);
    }

    void linkImage(OStream& output, const String& image, const String& reference)
    {
    }

    void embedImage(OStream& output, const String& reference)
    {
    }

    void comment(OStream& output, const String& str)
    {
        //output << "<!-- " << str << " -->" << std::endl;
    }

    void heading(OStream& output, int index, const String& heading)
    {
        beginHeading(output, index);
        output << heading;
        endHeading(output, index);
    }

    void beginSpan(OStream& output, const String& className)
    {
        if (!className.empty())
            output << "<span class=\"" << className << "\">";
        else
            output << "<span>";
    }

    void endSpan(OStream& output)
    {
        output << "</span>" << std::endl;
    }

    void beginLink(OStream& output, const String& ref, const String& className)
    {
        if (className.empty())
            output << "<a href=\"" << ref << "\">";
        else
            output << "<a href=\"" << ref << "\" class=\"" << className << "\">";
    }

    void endLink(OStream& output)
    {
        output << "</a>" << std::endl;
    }

    void beginOrderedList(OStream& output)
    {
        output << "<ul>" << std::endl;
    }

    void endOrderedList(OStream& output)
    {
        output << "</ul>" << std::endl;
    }

    void beginListItem(OStream& output)
    {
        output << "<li>";
    }

    void endListItem(OStream& output)
    {
        output << "</li>" << std::endl;
    }

    void beginHeading(OStream& output, int index)
    {
        index = std::min(std::max(1, index), 6);
        output << "<h" << index << ">";
    }

    void endHeading(OStream& output, int index)
    {
        index = std::min(std::max(1, index), 6);
        output << "</h" << index << ">" << std::endl;
    }

    
}  // namespace MdDox::Html
