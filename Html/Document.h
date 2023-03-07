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
#include <stack>
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

    enum BreakSize
    {
        BreakNone,
        BreakSmall,
        BreakMedium,
        BreakLarge,
        BreakExtraLarge,
        BreakFlex,

    };

    enum TextSize
    {
        ExtraLarge = 1,
        Large      = 2,
        Medium     = 5,
        Small      = 6,
    };

    enum Direction
    {
        X_AXIS,
        Y_AXIS,

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

    enum OverFlow
    {
        OverFlowNone,
        OverFlowHide,
        OverFlowAny,
        OverFlowX,
        OverFlowY,
    };

    struct StyleData
    {
        StringArray style;
        StringMap   attrs;
        String      id;
        String      accent;
        void        clear();
    };

    using StyleStack = std::stack<StyleData>;

    class Document
    {
    private:
        mutable OutputStringStream _out;
        String                     _data;
        mutable StyleStack         _stack;

        void tag(const String& tag, const String& text) const;

        void linkRefTag(const String& tag, const String& text, const String& href) const;

        void openTag(const String& tag) const;

        void openRefTag(const String& tag, const String& href) const;

        void refTag(const String& tag, const String& text, const String& href) const;

        void closeTag(const String& tag) const;

        StyleData& top() const;

    public:
        Document();

        ~Document();

        void textAlign(TextAlignment al) const;

        void fontSize(TextSize size) const;

        void margin(BoxOp dir, int idx) const;

        void gutter(BoxOp dir, int idx) const;

        void padding(BoxOp dir, int idx) const;

        void border(BoxOp dir, int idx) const;

        void backgroundColor(int idx) const;

        void borderColor(int idx) const;

        void color(int idx) const;

        void accent(int idx) const;

        void id(const String& val) const;

        void set(const String& val) const;

        void beginDocument(const String& header) const;

        void endDocument(const String& footer) const;

        void display(const String& text, int idx) const;

        void heading(const String& text, int idx) const;

        void headingRef(const String& text, const String& ref, int idx) const;

        void beginNav() const;

        void beginNavList() const;

        void navItem(const String& text) const;

        void navItem(const String& text, const String& ref) const;

        void beginGroupList() const;

        void save() const;

        void copy() const;

        void restore() const;

        void listGroupItem(const String& text) const;

        void listGroupItem(const String& text, const String& ref) const;

        void endNav() const;

        void endList() const;

        void beginHeader() const;

        void endHeader() const;

        void beginAside() const;

        void endAside() const;

        void beginMain() const;

        void endMain() const;

        void beginFooter() const;

        void endFooter() const;

        void flex() const;

        void beginContainerDiv(bool stretch = true) const;

        void beginDivRow(BreakSize br = BreakNone, int idx = 0) const;

        void beginDivCol(BreakSize br = BreakNone, int idx = 0) const;

        void beginDiv() const;

        void endDiv() const;

        void br() const;

        void beginDoc(const String& style) const;

        void endDoc() const;

        void noSpacing() const;

        void overflow(OverFlow v) const;

        void attr(const String& key, const String& val) const;

        void code(IStream& is) const;

        void code(const String& str) const;

        void paragraph(const String& text) const;

        void textRef(const String& title, const String& ref, TextSize size = Medium, TextAlignment al = AlignStart) const;

        void beginTag(const String& tag) const;

        void endTag(const String& tag) const;

        const String& flush();
    };

}  // namespace Rt2::Html
