/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#pragma once

#include <string>

namespace Ñ
{
    extern class Posición;

    // Análisis léxico
    enum CategoríaLexema {
        LEXEMA_RESERVADO,
        LEXEMA_IDENTIFICADOR,
        LEXEMA_NOTACIÓN,
        LEXEMA_TEXTO,
        LEXEMA_NÚMERO,
        LEXEMA_NÚMERO_REAL,

        LEXEMA_FIN
    };

    class Lexema
    {
    private:
        Posición* _posición = nullptr;
    public:
        Lexema(Posición* posición = nullptr);
        ~Lexema();

        CategoríaLexema categoría;
        std::string contenido;

        Posición* posición();
    };
    
    void muestraLexemas(std::vector<Ñ::Lexema*> _lexemas);
}