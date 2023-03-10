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
#include "Http/Uri/Scanner.h"
#include "Http/Url.h"
#include "ParserBase/ParserBase.h"
#include "Token.h"
#include "Utils/Definitions.h"
#include "Utils/String.h"

namespace Rt2::Http::Uri
{
    class Parser final : public ParserBase
    {
    private:
        Url _url;

        void ruleAbsoluteUri();
        void ruleOptionalUserPassword();
        void ruleRelativeUri();

        void ruleIpv4();
        void ruleDomain();
        void ruleAuthority();
        void rulePath();

        void ruleOptionalPort();
        void ruleNetworkUri();
        void ruleUri();

        bool isIntU8(const TokenBase& a,
                     const TokenBase& b,
                     const TokenBase& c,
                     const TokenBase& d) const;

    public:
        Parser();

        ~Parser() override;

        const Url& url() const { return _url; }

        void parseImpl(IStream& is) override;

        void writeImpl(OStream& is, int format) override;

        static bool isInvalidScheme(const String& scheme);
    };
}  // namespace Rt2::Http::Uri