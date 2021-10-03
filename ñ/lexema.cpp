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