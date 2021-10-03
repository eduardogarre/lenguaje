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