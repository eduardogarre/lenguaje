#include "gtest/gtest.h"
#include "../ñ/lexico.hpp"

#include <vector>

TEST(PruebasLexico, CadenaVacia)
{
    std::vector<Ñ::Lexema*> lexemas;

    lexemas = Ñ::analizaLéxico(u8"");
    EXPECT_EQ(lexemas.size(), 1);
    EXPECT_EQ(lexemas[0]->contenido, u8"");
    EXPECT_EQ(lexemas[0]->contenido, "");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);
    for(auto l : lexemas) { delete l; }

    lexemas = Ñ::analizaLéxico("");
    EXPECT_EQ(lexemas.size(), 1);
    EXPECT_EQ(lexemas[0]->contenido, u8"");
    EXPECT_EQ(lexemas[0]->contenido, "");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);
    for(auto l : lexemas) { delete l; }
}

TEST(PruebasLexico, Numeros)
{
    std::vector<Ñ::Lexema*> lexemas;

    // Número Natural
    lexemas = Ñ::analizaLéxico(u8"1");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"1");
    EXPECT_EQ(lexemas[0]->contenido, "1");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Número Real
    lexemas = Ñ::analizaLéxico(u8"3.14159268");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"3.14159268");
    EXPECT_EQ(lexemas[0]->contenido, "3.14159268");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Número Científico
    lexemas = Ñ::analizaLéxico(u8"6.023e23");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"6.023e23");
    EXPECT_EQ(lexemas[0]->contenido, "6.023e23");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    
    lexemas = Ñ::analizaLéxico(u8"6.023E23");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"6.023E23");
    EXPECT_EQ(lexemas[0]->contenido, "6.023E23");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    lexemas = Ñ::analizaLéxico(u8"6.023e-23");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"6.023e-23");
    EXPECT_EQ(lexemas[0]->contenido, "6.023e-23");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    
    lexemas = Ñ::analizaLéxico(u8"6.023E-23");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"6.023E-23");
    EXPECT_EQ(lexemas[0]->contenido, "6.023E-23");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
}

TEST(PruebasLexico, PalabrasReservadas)
{
    std::vector<Ñ::Lexema*> lexemas;

    // cierto
    lexemas = Ñ::analizaLéxico(u8"cierto");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"cierto");
    EXPECT_EQ(lexemas[0]->contenido, "cierto");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // falso
    lexemas = Ñ::analizaLéxico(u8"falso");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"falso");
    EXPECT_EQ(lexemas[0]->contenido, "falso");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // var
    lexemas = Ñ::analizaLéxico(u8"var");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"var");
    EXPECT_EQ(lexemas[0]->contenido, "var");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // bool
    lexemas = Ñ::analizaLéxico(u8"bool");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"bool");
    EXPECT_EQ(lexemas[0]->contenido, "bool");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // entero
    lexemas = Ñ::analizaLéxico(u8"entero");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"entero");
    EXPECT_EQ(lexemas[0]->contenido, "entero");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // ent8
    lexemas = Ñ::analizaLéxico(u8"ent8");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"ent8");
    EXPECT_EQ(lexemas[0]->contenido, "ent8");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // ent16
    lexemas = Ñ::analizaLéxico(u8"ent16");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"ent16");
    EXPECT_EQ(lexemas[0]->contenido, "ent16");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // ent32
    lexemas = Ñ::analizaLéxico(u8"ent32");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"ent32");
    EXPECT_EQ(lexemas[0]->contenido, "ent32");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // ent64
    lexemas = Ñ::analizaLéxico(u8"ent64");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"ent64");
    EXPECT_EQ(lexemas[0]->contenido, "ent64");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // natural
    lexemas = Ñ::analizaLéxico(u8"natural");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"natural");
    EXPECT_EQ(lexemas[0]->contenido, "natural");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // nat8
    lexemas = Ñ::analizaLéxico(u8"nat8");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat8");
    EXPECT_EQ(lexemas[0]->contenido, "nat8");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // nat8
    lexemas = Ñ::analizaLéxico(u8"nat8");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat8");
    EXPECT_EQ(lexemas[0]->contenido, "nat8");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // nat16
    lexemas = Ñ::analizaLéxico(u8"nat16");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat16");
    EXPECT_EQ(lexemas[0]->contenido, "nat16");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // nat32
    lexemas = Ñ::analizaLéxico(u8"nat32");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat32");
    EXPECT_EQ(lexemas[0]->contenido, "nat32");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // nat64
    lexemas = Ñ::analizaLéxico(u8"nat64");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat64");
    EXPECT_EQ(lexemas[0]->contenido, "nat64");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // real
    lexemas = Ñ::analizaLéxico(u8"real");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"real");
    EXPECT_EQ(lexemas[0]->contenido, "real");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // rea16
    lexemas = Ñ::analizaLéxico(u8"rea16");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"rea16");
    EXPECT_EQ(lexemas[0]->contenido, "rea16");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // rea32
    lexemas = Ñ::analizaLéxico(u8"rea32");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"rea32");
    EXPECT_EQ(lexemas[0]->contenido, "rea32");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // rea64
    lexemas = Ñ::analizaLéxico(u8"rea64");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"rea64");
    EXPECT_EQ(lexemas[0]->contenido, "rea64");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // txt
    lexemas = Ñ::analizaLéxico(u8"txt");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"txt");
    EXPECT_EQ(lexemas[0]->contenido, "txt");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
}

TEST(PruebasLexico, Identificadores)
{
    std::vector<Ñ::Lexema*> lexemas;

    // identificador
    lexemas = Ñ::analizaLéxico(u8"identificador");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"identificador");
    EXPECT_EQ(lexemas[0]->contenido, "identificador");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // _nombre
    lexemas = Ñ::analizaLéxico(u8"_nombre");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"_nombre");
    EXPECT_EQ(lexemas[0]->contenido, "_nombre");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // prueba1234
    lexemas = Ñ::analizaLéxico(u8"prueba1234");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"prueba1234");
    EXPECT_EQ(lexemas[0]->contenido, "prueba1234");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }

    // variable_de_prueba
    lexemas = Ñ::analizaLéxico(u8"variable_de_prueba");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"variable_de_prueba");
    EXPECT_EQ(lexemas[0]->contenido, "variable_de_prueba");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
}