/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#pragma once

#include <stdint.h>
#include <string>

namespace Ñ
{
    class Posición
    {
    private:
        uint64_t _cursor;
        uint64_t _línea;
        uint64_t _columna;
        uint64_t _longitud;
        std::string _archivo;

    public:
        Posición();

        std::string muestra();
        
        uint64_t cursor();
        uint64_t línea();
        uint64_t columna();
        uint64_t longitud();
        std::string archivo();

        void incCursor();
        void incLínea();
        void empiezaColumna();
        void incColumna();
        void longitud(uint64_t longitud);
        void archivo(std::string archivo);
    };

} // namespace Ñ
