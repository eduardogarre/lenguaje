#pragma once

#include <string>

#include "posicion.hpp"

namespace Ñ
{
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
        Posición _posición;
    public:
        Lexema(Posición posición = {});

        CategoríaLexema categoría;
        std::string contenido;

        Posición posición();
    };
    
    void muestraLexemas(std::vector<Ñ::Lexema*> _lexemas);
}