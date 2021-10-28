/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.
*/

#include <iostream>
#include <vector>

#include "apoyo.hpp"
#include "lexema.hpp"
#include "posicion.hpp"

Ñ::Lexema::Lexema(Posición* posición) {
    _posición = new Ñ::Posición;
    if(posición != nullptr)
    {
        *_posición = *posición;
    }
}

Ñ::Lexema::~Lexema() {
    if(_posición != nullptr)
    {
        delete _posición;
    }
}

Ñ::Posición* Ñ::Lexema::posición()
{
    return _posición;
}

void Ñ::muestraLexemas(std::vector<Ñ::Lexema*> _lexemas)
{
    //std::cout << "muestraLexemas()" << std::endl;
    while(!(_lexemas.empty()))
    {
        std::cout << "LIN:" << _lexemas.front()->posición()->línea();
        std::cout << ", COL:" << _lexemas.front()->posición()->columna();
        std::cout << ", CUR:" << _lexemas.front()->posición()->cursor();
        std::cout << ", LON:" << _lexemas.front()->posición()->longitud();

        switch (_lexemas.front()->categoría)
        {
        case Ñ::CategoríaLexema::LEXEMA_RESERVADO:
            std::cout << u8"] [LEX_RESERVADO] [";
            break;
        case Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR:
            std::cout << u8"] [LEX_IDENTIFICADOR] [";
            break;
        case Ñ::CategoríaLexema::LEXEMA_NOTACIÓN:
            std::cout << u8"] [LEX_NOTACIÓN] [";
            break;
        case Ñ::CategoríaLexema::LEXEMA_TEXTO:
            std::cout << u8"] [LEX_TEXTO] [";
            break;
        case Ñ::CategoríaLexema::LEXEMA_NÚMERO:
            std::cout << u8"] [LEX_NÚMERO] [";
            break;
        
        default:
            std::cout << u8"] [LEXEMA_DESCONOCIDO] [";
            break;
        }
        std::cout << _lexemas.front()->contenido << "]" << std::endl;
        Ñ::pop_front(_lexemas);
    }
}