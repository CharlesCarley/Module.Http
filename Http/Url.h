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
#include "Utils/String.h"

namespace Rt2::Http
{

    enum ValidSchemes
    {
        FileScheme,
        HttpScheme,
    };

    constexpr char Http[4] = {'h', 't', 't', 'p'};
    constexpr U16  Port    = 80;

    class Url
    {
    public:
        enum Type
        {
            Absolute,
            Relative,
            Network
        };

    private:
        String _authority{};
        String _scheme{Http, 4};
        U16    _port{Port};
        String _path{};
        I8     _type{Absolute};

    public:
        Url() = default;

        explicit Url(const String& url);

        void setScheme(const String& scheme);

        void setPath(const String& path);

        void setAuthority(const String& auth);

        void setPort(const U16& port);

        const String& scheme() const;

        const String& authority() const;

        const U16& port() const;

        const String& path() const;

        String value() const;

        I8 type() const;

        void setType(const I8& type);
    };

    inline const String& Url::scheme() const
    {
        return _scheme;
    }

    inline const String& Url::authority() const
    {
        return _authority;
    }

    inline const U16& Url::port() const
    {
        return _port;
    }

    inline const String& Url::path() const
    {
        return _path;
    }

    inline I8 Url::type() const
    {
        return _type;
    }

    inline void Url::setType(const I8& type)
    {
        _type = type;
    }

}  // namespace Rt2::Http
