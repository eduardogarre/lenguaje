#pragma once

#include <string>

namespace Ñ
{
    // Análisis léxico
    enum CategoríaLexema {
        LEXEMA_RESERVADO,
        LEXEMA_IDENTIFICADOR,
        LEXEMA_NOTACIÓN,
        LEXEMA_TEXTO,
        LEXEMA_NÚMERO,

        LEXEMA_FIN
    };

    class Lexema
    {
    public:
        Lexema();

        CategoríaLexema categoría;
        std::string contenido;
    };
}