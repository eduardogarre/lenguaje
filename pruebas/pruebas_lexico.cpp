#include "pruebas.hpp"

#include "ñ/lexico.hpp"

#include <vector>

TEST(PruebasLexico, CadenaVacia)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"");
    EXPECT_EQ(lexemas.size(), 1);
    EXPECT_EQ(lexemas[0]->contenido, u8"");
    EXPECT_EQ(lexemas[0]->contenido, "");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);
    for(auto l : lexemas) { delete l; }
    delete léxico;

	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza("");
    EXPECT_EQ(lexemas.size(), 1);
    EXPECT_EQ(lexemas[0]->contenido, u8"");
    EXPECT_EQ(lexemas[0]->contenido, "");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);
    for(auto l : lexemas) { delete l; }
    delete léxico;
}

TEST(PruebasLexico, Numeros)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

    // Número Natural
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"1");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"1");
    EXPECT_EQ(lexemas[0]->contenido, "1");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Número Real
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"3.14159268");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"3.14159268");
    EXPECT_EQ(lexemas[0]->contenido, "3.14159268");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Número Científico
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"6.023e23");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"6.023e23");
    EXPECT_EQ(lexemas[0]->contenido, "6.023e23");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
    
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"6.023E23");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"6.023E23");
    EXPECT_EQ(lexemas[0]->contenido, "6.023E23");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"6.023e-23");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"6.023e-23");
    EXPECT_EQ(lexemas[0]->contenido, "6.023e-23");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
    
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"6.023E-23");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"6.023E-23");
    EXPECT_EQ(lexemas[0]->contenido, "6.023E-23");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
}

TEST(PruebasLexico, PalabrasReservadas)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

    // cierto
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"cierto");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"cierto");
    EXPECT_EQ(lexemas[0]->contenido, "cierto");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // falso
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"falso");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"falso");
    EXPECT_EQ(lexemas[0]->contenido, "falso");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // var
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"var");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"var");
    EXPECT_EQ(lexemas[0]->contenido, "var");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // bool
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"bool");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"bool");
    EXPECT_EQ(lexemas[0]->contenido, "bool");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // entero
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"entero");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"entero");
    EXPECT_EQ(lexemas[0]->contenido, "entero");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // ent8
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"ent8");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"ent8");
    EXPECT_EQ(lexemas[0]->contenido, "ent8");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // ent16
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"ent16");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"ent16");
    EXPECT_EQ(lexemas[0]->contenido, "ent16");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // ent32
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"ent32");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"ent32");
    EXPECT_EQ(lexemas[0]->contenido, "ent32");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // ent64
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"ent64");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"ent64");
    EXPECT_EQ(lexemas[0]->contenido, "ent64");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // natural
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"natural");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"natural");
    EXPECT_EQ(lexemas[0]->contenido, "natural");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // nat8
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"nat8");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat8");
    EXPECT_EQ(lexemas[0]->contenido, "nat8");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // nat8
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"nat8");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat8");
    EXPECT_EQ(lexemas[0]->contenido, "nat8");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // nat16
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"nat16");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat16");
    EXPECT_EQ(lexemas[0]->contenido, "nat16");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // nat32
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"nat32");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat32");
    EXPECT_EQ(lexemas[0]->contenido, "nat32");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // nat64
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"nat64");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat64");
    EXPECT_EQ(lexemas[0]->contenido, "nat64");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // real
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"real");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"real");
    EXPECT_EQ(lexemas[0]->contenido, "real");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // rea16
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"rea16");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"rea16");
    EXPECT_EQ(lexemas[0]->contenido, "rea16");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // rea32
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"rea32");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"rea32");
    EXPECT_EQ(lexemas[0]->contenido, "rea32");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // rea64
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"rea64");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"rea64");
    EXPECT_EQ(lexemas[0]->contenido, "rea64");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // txt
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"txt");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"txt");
    EXPECT_EQ(lexemas[0]->contenido, "txt");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
}

TEST(PruebasLexico, Identificadores)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

    // identificador
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"identificador");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"identificador");
    EXPECT_EQ(lexemas[0]->contenido, "identificador");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // _nombre
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"_nombre");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"_nombre");
    EXPECT_EQ(lexemas[0]->contenido, "_nombre");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // prueba1234
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"prueba1234");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"prueba1234");
    EXPECT_EQ(lexemas[0]->contenido, "prueba1234");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // variable_de_prueba
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"variable_de_prueba");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"variable_de_prueba");
    EXPECT_EQ(lexemas[0]->contenido, "variable_de_prueba");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
}

TEST(PruebasLexico, Notacion)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

    // Punto
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8".");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8".");
    EXPECT_EQ(lexemas[0]->contenido, ".");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Coma
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8",");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8",");
    EXPECT_EQ(lexemas[0]->contenido, ",");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Dos puntos
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8":");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8":");
    EXPECT_EQ(lexemas[0]->contenido, ":");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Punto y coma
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8";");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8";");
    EXPECT_EQ(lexemas[0]->contenido, ";");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Guión
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"-");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"-");
    EXPECT_EQ(lexemas[0]->contenido, "-");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Suma
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"+");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"+");
    EXPECT_EQ(lexemas[0]->contenido, "+");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Barra
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"/");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"/");
    EXPECT_EQ(lexemas[0]->contenido, "/");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Barra invertida
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"\\");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"\\");
    EXPECT_EQ(lexemas[0]->contenido, "\\");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Asterisco
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"*");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"*");
    EXPECT_EQ(lexemas[0]->contenido, "*");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Comilla simple
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"'");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"'");
    EXPECT_EQ(lexemas[0]->contenido, "'");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Barra vertical
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"|");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"|");
    EXPECT_EQ(lexemas[0]->contenido, "|");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Arroba
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"@");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"@");
    EXPECT_EQ(lexemas[0]->contenido, "@");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Euro
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"€");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"€");
    EXPECT_EQ(lexemas[0]->contenido, u8"\u20AC");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"\u20AC");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"\u20AC");
    EXPECT_EQ(lexemas[0]->contenido, u8"€");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Dólar
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"$");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"$");
    EXPECT_EQ(lexemas[0]->contenido, "$");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Porciento
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"%");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"%");
    EXPECT_EQ(lexemas[0]->contenido, "%");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // et
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"&");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"&");
    EXPECT_EQ(lexemas[0]->contenido, "&");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Abre paréntesis
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"(");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"(");
    EXPECT_EQ(lexemas[0]->contenido, "(");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Cierra paréntesis)
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8")");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8")");
    EXPECT_EQ(lexemas[0]->contenido, ")");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Igual
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"=");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"=");
    EXPECT_EQ(lexemas[0]->contenido, "=");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Abre interrogación
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"¿");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"¿");
    EXPECT_EQ(lexemas[0]->contenido, "¿");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Cierra interrogación
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"?");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"?");
    EXPECT_EQ(lexemas[0]->contenido, "?");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Abre exclamación
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"¡");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"¡");
    EXPECT_EQ(lexemas[0]->contenido, "¡");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Cierra exclamación
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"!");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"!");
    EXPECT_EQ(lexemas[0]->contenido, "!");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Abre corchete
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"[");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"[");
    EXPECT_EQ(lexemas[0]->contenido, "[");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Cierra corchete
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"]");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"]");
    EXPECT_EQ(lexemas[0]->contenido, "]");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Abre llave
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"{");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"{");
    EXPECT_EQ(lexemas[0]->contenido, "{");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Cierra llave
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"}");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"}");
    EXPECT_EQ(lexemas[0]->contenido, "}");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Caret / acento circunflejo
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"^");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"^");
    EXPECT_EQ(lexemas[0]->contenido, "^");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Menor que
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"<");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"<");
    EXPECT_EQ(lexemas[0]->contenido, "<");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;


    // Mayor que
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8">");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8">");
    EXPECT_EQ(lexemas[0]->contenido, ">");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
}

TEST(PruebasLexico, MultiplesLexemas)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

    // Declaración de variable
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"nat32 a;");
    EXPECT_EQ(lexemas.size(), 4);

    EXPECT_EQ(lexemas[0]->contenido, u8"nat32");
    EXPECT_EQ(lexemas[0]->contenido, "nat32");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"a");
    EXPECT_EQ(lexemas[1]->contenido, "a");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[2]->contenido, u8";");
    EXPECT_EQ(lexemas[2]->contenido, ";");
    EXPECT_EQ(lexemas[2]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[3]->contenido, u8"");
    EXPECT_EQ(lexemas[3]->contenido, "");
    EXPECT_EQ(lexemas[3]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // Declaración y asignación de variable
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"ent8 b = 288;");
    EXPECT_EQ(lexemas.size(), 6);

    EXPECT_EQ(lexemas[0]->contenido, u8"ent8");
    EXPECT_EQ(lexemas[0]->contenido, "ent8");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"b");
    EXPECT_EQ(lexemas[1]->contenido, "b");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[2]->contenido, u8"=");
    EXPECT_EQ(lexemas[2]->contenido, "=");
    EXPECT_EQ(lexemas[2]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[3]->contenido, u8"288");
    EXPECT_EQ(lexemas[3]->contenido, "288");
    EXPECT_EQ(lexemas[3]->categoría, Ñ::CategoríaLexema::LEXEMA_NÚMERO);

    EXPECT_EQ(lexemas[4]->contenido, u8";");
    EXPECT_EQ(lexemas[4]->contenido, ";");
    EXPECT_EQ(lexemas[4]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[5]->contenido, u8"");
    EXPECT_EQ(lexemas[5]->contenido, "");
    EXPECT_EQ(lexemas[5]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // Declaración de una variable y asignación del resultado de una función
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"rea64 c = aleatorio();");
    EXPECT_EQ(lexemas.size(), 8);

    EXPECT_EQ(lexemas[0]->contenido, u8"rea64");
    EXPECT_EQ(lexemas[0]->contenido, "rea64");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_RESERVADO);

    EXPECT_EQ(lexemas[1]->contenido, u8"c");
    EXPECT_EQ(lexemas[1]->contenido, "c");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[2]->contenido, u8"=");
    EXPECT_EQ(lexemas[2]->contenido, "=");
    EXPECT_EQ(lexemas[2]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[3]->contenido, u8"aleatorio");
    EXPECT_EQ(lexemas[3]->contenido, "aleatorio");
    EXPECT_EQ(lexemas[3]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[4]->contenido, u8"(");
    EXPECT_EQ(lexemas[4]->contenido, "(");
    EXPECT_EQ(lexemas[4]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[5]->contenido, u8")");
    EXPECT_EQ(lexemas[5]->contenido, ")");
    EXPECT_EQ(lexemas[5]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[6]->contenido, u8";");
    EXPECT_EQ(lexemas[6]->contenido, ";");
    EXPECT_EQ(lexemas[6]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[7]->contenido, u8"");
    EXPECT_EQ(lexemas[7]->contenido, "");
    EXPECT_EQ(lexemas[7]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;

    // Llamada a una función con un argumento
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"escribe(\"hola, mundo\n\");");
    EXPECT_EQ(lexemas.size(), 6);

    EXPECT_EQ(lexemas[0]->contenido, u8"escribe");
    EXPECT_EQ(lexemas[0]->contenido, "escribe");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR);

    EXPECT_EQ(lexemas[1]->contenido, u8"(");
    EXPECT_EQ(lexemas[1]->contenido, "(");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[2]->contenido, u8"hola, mundo\n");
    EXPECT_EQ(lexemas[2]->contenido, "hola, mundo\n");
    EXPECT_EQ(lexemas[2]->categoría, Ñ::CategoríaLexema::LEXEMA_TEXTO);

    EXPECT_EQ(lexemas[3]->contenido, u8")");
    EXPECT_EQ(lexemas[3]->contenido, ")");
    EXPECT_EQ(lexemas[3]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[4]->contenido, u8";");
    EXPECT_EQ(lexemas[4]->contenido, ";");
    EXPECT_EQ(lexemas[4]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[5]->contenido, u8"");
    EXPECT_EQ(lexemas[5]->contenido, "");
    EXPECT_EQ(lexemas[5]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
}