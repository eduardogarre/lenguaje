#pragma once

#include <string>
#include <vector>

#include "lexema.hpp"

namespace Ñ
{
    class Léxico // Análisis léxico
    {
    public:
        std::vector<Lexema*> analiza(std::string comando);

// Compilación condicional: si estamos en pruebas, expongo las funciones privadas de la clase Léxico
#ifdef EVALUANDO_PRUEBAS
    public:
#else
    private:
#endif
        uint64_t cursor = 0;
        uint64_t línea = 0;
        uint64_t columna = 0;
        uint64_t lexema = 0;
        std::vector<Ñ::Lexema*> lexemas;

        void incrementaCursor(std::string txt);
        std::string siguienteCarácter(std::string txt);
        bool comentario(std::string txt);
        bool _comentario1L(std::string txt);
        bool _comentarioXL(std::string txt);
        bool nuevaLínea(std::string txt);
        bool espacio(std::string txt);
        bool notación(std::string txt);
        bool _nombre(std::string txt);
        bool reservada(std::string txt);
        bool _notacióncientífica(std::string txt);
        bool _númerodecimales(std::string txt);
        bool _número(std::string txt);
        bool número(std::string txt);
        bool texto(std::string txt);
        bool identificador(std::string txt);
    };

// Compilación condicional: si estamos en pruebas, expongo las funciones privadas de la clase Léxico
#ifdef EVALUANDO_PRUEBAS
    bool esdígito(std::string c);
    bool espuntuación(std::string c);
    bool esnuevalínea(std::string c);
    bool esespacio(std::string c);
    bool esalfa(std::string c);
    bool esalfanum(std::string c);
#endif
}