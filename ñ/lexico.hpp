#pragma once

#include <string>
#include <vector>

#include "lexema.hpp"

namespace Ñ
{
    // Análisis léxico
    std::vector<Ñ::Lexema*> analizaLéxico(std::string comando);

// Compilación condicional: si estamos en pruebas, expongo las funciones privadas de lexico.cpp
#if EVALUANDO_PRUEBAS
    void incrementaCursor(std::string txt);
    std::string siguienteCarácter(std::string txt);
    bool esdígito(std::string c);
    bool espuntuación(std::string c);
    bool esnuevalínea(std::string c);
    bool esespacio(std::string c);
    bool esalfa(std::string c);
    bool esalfanum(std::string c);
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
#endif
}