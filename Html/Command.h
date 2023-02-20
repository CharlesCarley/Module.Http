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
#include "Utils/String.h"

namespace Rt2::Html
{
    extern void lineBreak(OStream& output);

    extern void space(OStream& output, int i);

    extern void beginDivSection(OStream& output, const char* name);

    extern void endDivSection(OStream& output, const char* name);

    extern void beginSection(OStream& output, const String& name, int depth);

    extern void endSection(OStream& output);

    extern void beginBlockQuote(OStream& output);

    extern void endBlockQuote(OStream& output);

    extern void horizontalRule(OStream& output);

    extern void anchor(OStream& output, const String& id);

    extern void code(OStream& output, const String& code, const String& type = "txt");

    extern void beginParagraph(OStream& output);

    extern void endParagraph(OStream& output);

    extern void paragraph(OStream& output, const String& str);

    extern void inlineText(OStream& output, const String& str, const String& className = "");

    extern void inlineImage(OStream& output, const String& src, const String& className = "");

    extern void typewriterText(OStream& output, const String& str);

    extern void boldText(OStream& output, const String& str);

    extern void italicText(OStream& output, const String& str);

    extern void linkImage(OStream& output, const String& image, const String& reference);

    extern void embedImage(OStream& output, const String& reference);

    extern void comment(OStream& output, const String& str);

    extern void heading(OStream& output, int index, const String& heading);

    extern void beginSpan(OStream& output, const String& className);

    extern void endSpan(OStream& output);

    extern void beginLink(OStream& output, const String& ref, const String& className = "");

    extern void endLink(OStream& output);

    extern void beginOrderedList(OStream& output);

    extern void endOrderedList(OStream& output);

    extern void beginListItem(OStream& output);

    extern void endListItem(OStream& output);

    extern void beginHeading(OStream& output, int index);

    extern void endHeading(OStream& output, int index);

}  // namespace Rt2::Html
