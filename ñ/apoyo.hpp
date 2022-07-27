/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#pragma once

#include <cassert>
#include <vector>

namespace Ñ
{
    template <typename T>
    void pop_front(std::vector<T> &vec)
    {
        assert(!vec.empty());
        vec.erase(vec.begin());
    }

    inline int64_t potencia(int64_t x, uint64_t p)
    {
        if (p == 0)
        {
            return 1;
        }
        if (p == 1)
        {
            return x;
        }

        int64_t tmp = potencia(x, p / 2);

        if (p % 2 == 0)
        {
            return tmp * tmp;
        }
        else
        {
            return x * tmp * tmp;
        }
    }

    inline char *deStrAPtrChars(std::string txt)
    {
        char *texto = (char *)malloc(txt.size() + 1);
        strcpy(texto, txt.c_str());
        return texto;
    }
}