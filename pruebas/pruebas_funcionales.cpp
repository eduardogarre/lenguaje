#include "pruebas.hpp"

#include "ñ/ñ.hpp"

#include <vector>

TEST(PruebasFuncionales, declaracionesVariables)
{
    Ñ::TablaSímbolos* tablaSímbolos = new Ñ::TablaSímbolos;
    Ñ::Léxico* léxico = new Ñ::Léxico;
    Ñ::Sintaxis* sintaxis = new Ñ::Sintaxis;
    std::vector<Ñ::Lexema*> lexemas;
    Ñ::Nodo* nodos;
    Ñ::Resultado rSemántico;
    Ñ::Resultado rIntérprete;
    std::string expresión;

    expresión = "nat a;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("a"));
    delete nodos, lexemas;

    expresión = "ent b;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("b"));
    delete nodos, lexemas;

    expresión = "real c;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("c"));
    delete nodos, lexemas;

    expresión = "bool d;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("d"));
    delete nodos, lexemas;

    ASSERT_TRUE(tablaSímbolos->identificadorDisponible("e"));
    ASSERT_TRUE(tablaSímbolos->identificadorDisponible("h"));
    ASSERT_TRUE(tablaSímbolos->identificadorDisponible("o"));
    ASSERT_TRUE(tablaSímbolos->identificadorDisponible("z"));

    delete sintaxis, léxico, tablaSímbolos;
}

TEST(PruebasFuncionales, definicionesVariables)
{
    Ñ::TablaSímbolos* tablaSímbolos = new Ñ::TablaSímbolos;
    Ñ::Léxico* léxico = new Ñ::Léxico;
    Ñ::Sintaxis* sintaxis = new Ñ::Sintaxis;
    std::vector<Ñ::Lexema*> lexemas;
    Ñ::Nodo* nodos;
    Ñ::Resultado rSemántico;
    Ñ::Resultado rIntérprete;
    Ñ::Resultado rValor;
    Ñ::Nodo* valor;
    Ñ::Literal* literal;
    std::string expresión;

    expresión = "nat a = 288;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("a"));
    rValor = tablaSímbolos->leeValor("a");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "288");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "ent b = 42;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("b"));
    rValor = tablaSímbolos->leeValor("b");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "42");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "real c = -2;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("c"));
    rValor = tablaSímbolos->leeValor("c");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "-2");
    delete nodos, lexemas, literal, rValor.nodo();

    delete sintaxis, léxico, tablaSímbolos;
}

TEST(PruebasFuncionales, operacionesAritmeticas)
{
    Ñ::TablaSímbolos* tablaSímbolos = new Ñ::TablaSímbolos;
    Ñ::Léxico* léxico = new Ñ::Léxico;
    Ñ::Sintaxis* sintaxis = new Ñ::Sintaxis;
    std::vector<Ñ::Lexema*> lexemas;
    Ñ::Nodo* nodos;
    Ñ::Resultado rSemántico;
    Ñ::Resultado rIntérprete;
    Ñ::Resultado rValor;
    Ñ::Nodo* valor;
    Ñ::Literal* literal;
    std::string expresión;

    expresión = "nat a = 1 + 1;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("a"));
    rValor = tablaSímbolos->leeValor("a");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "2");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "nat b = 2 + 3;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("b"));
    rValor = tablaSímbolos->leeValor("b");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "5");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "nat c = 1 - 1;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("c"));
    rValor = tablaSímbolos->leeValor("c");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "0");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "nat d = 3 - 5;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("d"));
    rValor = tablaSímbolos->leeValor("d");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "-2");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "nat e = 1 - 1 + 1;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("e"));
    rValor = tablaSímbolos->leeValor("e");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "1");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "nat f = 5 - 2 + 3;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("f"));
    rValor = tablaSímbolos->leeValor("f");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "6");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "nat g = 1 - 1 - 1;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("g"));
    rValor = tablaSímbolos->leeValor("g");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "-1");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "nat h = 8 - 2 + 2;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("h"));
    rValor = tablaSímbolos->leeValor("h");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "8");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "nat i = -1 + 2;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("i"));
    rValor = tablaSímbolos->leeValor("i");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "1");
    delete nodos, lexemas, literal, rValor.nodo();

    expresión = "nat j = -1 + 2 - 3;";
    lexemas = léxico->analiza(expresión);
    nodos = sintaxis->analiza(lexemas);
    rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
    ASSERT_FALSE(rSemántico.error());
    rIntérprete = Ñ::interpretaNodos(nodos, tablaSímbolos);
    ASSERT_FALSE(tablaSímbolos->identificadorDisponible("j"));
    rValor = tablaSímbolos->leeValor("j");
    ASSERT_FALSE(rValor.error());
    valor = rValor.nodo();
    ASSERT_EQ(valor->categoría, Ñ::CategoríaNodo::NODO_LITERAL);
    literal = (Ñ::Literal*)valor;
    EXPECT_EQ(literal->dato, "-2");
    delete nodos, lexemas, literal, rValor.nodo();

    delete sintaxis, léxico, tablaSímbolos;
}