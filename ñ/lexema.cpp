#include <iostream>
#include <vector>

#include "apoyo.hpp"
#include "lexema.hpp"

Ñ::Lexema::Lexema() {}

void Ñ::muestraLexemas(std::vector<Ñ::Lexema*> _lexemas)
{
    //std::cout << "muestraLexemas()" << std::endl;
    while(!(_lexemas.empty()))
    {
        switch (_lexemas.front()->categoría)
        {
        case Ñ::CategoríaLexema::LEXEMA_RESERVADO:
            std::cout << u8"LEXEMA_RESERVADO ";
            break;
        case Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR:
            std::cout << u8"LEXEMA_IDENTIFICADOR ";
            break;
        case Ñ::CategoríaLexema::LEXEMA_NOTACIÓN:
            std::cout << u8"LEXEMA_NOTACIÓN ";
            break;
        case Ñ::CategoríaLexema::LEXEMA_TEXTO:
            std::cout << u8"LEXEMA_TEXTO ";
            break;
        case Ñ::CategoríaLexema::LEXEMA_NÚMERO:
            std::cout << u8"LEXEMA_NÚMERO ";
            break;
        
        default:
            std::cout << u8"LEXEMA_DESCONOCIDO ";
            break;
        }
        std::cout << "[" << _lexemas.front()->contenido << "]" << std::endl;
        Ñ::pop_front(_lexemas);
    }
}