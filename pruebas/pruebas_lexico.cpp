#include "pruebas.hpp"

#include "ñ/lexico.hpp"

#include <vector>

/*
TEST(PruebasLexico, incrementaCursor)
{

}

TEST(PruebasLexico, siguienteCarácter)
{

}

TEST(PruebasLexico, esdígito)
{
	Ñ::Léxico* léxico = new Ñ::Léxico();

    EXPECT_TRUE(léxico->esdígito("0"));
    EXPECT_TRUE(léxico->esdígito("1"));
    EXPECT_TRUE(léxico->esdígito("2"));
    EXPECT_TRUE(léxico->esdígito("3"));
    EXPECT_TRUE(léxico->esdígito("4"));
    EXPECT_TRUE(léxico->esdígito("5"));
    EXPECT_TRUE(léxico->esdígito("6"));
    EXPECT_TRUE(léxico->esdígito("7"));
    EXPECT_TRUE(léxico->esdígito("8"));
    EXPECT_TRUE(léxico->esdígito("9"));
    EXPECT_TRUE(léxico->esdígito("0"));
    EXPECT_TRUE(léxico->esdígito("0"));

    EXPECT_FALSE(léxico->esdígito(""));
    EXPECT_FALSE(léxico->esdígito("a"));
    EXPECT_FALSE(léxico->esdígito(","));
    EXPECT_FALSE(léxico->esdígito("_"));
    EXPECT_FALSE(léxico->esdígito("!"));
    EXPECT_FALSE(léxico->esdígito("natural"));
    EXPECT_FALSE(léxico->esdígito("ent32"));
    EXPECT_FALSE(léxico->esdígito("real64"));
    EXPECT_FALSE(léxico->esdígito("x86"));
    EXPECT_FALSE(léxico->esdígito("\\"));
    EXPECT_FALSE(léxico->esdígito("?"));
    EXPECT_FALSE(léxico->esdígito(" "));
    EXPECT_FALSE(léxico->esdígito("\n"));
    EXPECT_FALSE(léxico->esdígito("\t"));
    EXPECT_FALSE(léxico->esdígito("\r"));
}

TEST(PruebasLexico, espuntuación)
{
	Ñ::Léxico* léxico = new Ñ::Léxico();

    EXPECT_TRUE(léxico->espuntuación("."));
    EXPECT_TRUE(léxico->espuntuación(","));
    EXPECT_TRUE(léxico->espuntuación(":"));
    EXPECT_TRUE(léxico->espuntuación(";"));
    EXPECT_TRUE(léxico->espuntuación("-"));
    EXPECT_TRUE(léxico->espuntuación("+"));
    EXPECT_TRUE(léxico->espuntuación("/"));
    EXPECT_TRUE(léxico->espuntuación("*"));
    EXPECT_TRUE(léxico->espuntuación("\""));
    EXPECT_TRUE(léxico->espuntuación("'"));
    EXPECT_TRUE(léxico->espuntuación("|"));
    EXPECT_TRUE(léxico->espuntuación("@"));
    EXPECT_TRUE(léxico->espuntuación("€"));
    EXPECT_TRUE(léxico->espuntuación("$"));
    EXPECT_TRUE(léxico->espuntuación("%"));
    EXPECT_TRUE(léxico->espuntuación("&"));
    EXPECT_TRUE(léxico->espuntuación("("));
    EXPECT_TRUE(léxico->espuntuación(")"));
    EXPECT_TRUE(léxico->espuntuación("="));
    EXPECT_TRUE(léxico->espuntuación("¿"));
    EXPECT_TRUE(léxico->espuntuación("?"));
    EXPECT_TRUE(léxico->espuntuación("¡"));
    EXPECT_TRUE(léxico->espuntuación("!"));
    EXPECT_TRUE(léxico->espuntuación("["));
    EXPECT_TRUE(léxico->espuntuación("]"));
    EXPECT_TRUE(léxico->espuntuación("{"));
    EXPECT_TRUE(léxico->espuntuación("}"));
    EXPECT_TRUE(léxico->espuntuación("^"));
    EXPECT_TRUE(léxico->espuntuación("<"));
    EXPECT_TRUE(léxico->espuntuación(">"));
    EXPECT_TRUE(léxico->espuntuación("\\"));
    
    EXPECT_TRUE(léxico->espuntuación(u8"."));
    EXPECT_TRUE(léxico->espuntuación(u8","));
    EXPECT_TRUE(léxico->espuntuación(u8":"));
    EXPECT_TRUE(léxico->espuntuación(u8";"));
    EXPECT_TRUE(léxico->espuntuación(u8"-"));
    EXPECT_TRUE(léxico->espuntuación(u8"+"));
    EXPECT_TRUE(léxico->espuntuación(u8"/"));
    EXPECT_TRUE(léxico->espuntuación(u8"*"));
    EXPECT_TRUE(léxico->espuntuación(u8"\""));
    EXPECT_TRUE(léxico->espuntuación(u8"'"));
    EXPECT_TRUE(léxico->espuntuación(u8"|"));
    EXPECT_TRUE(léxico->espuntuación(u8"@"));
    EXPECT_TRUE(léxico->espuntuación(u8"€"));
    EXPECT_TRUE(léxico->espuntuación(u8"$"));
    EXPECT_TRUE(léxico->espuntuación(u8"%"));
    EXPECT_TRUE(léxico->espuntuación(u8"&"));
    EXPECT_TRUE(léxico->espuntuación(u8"("));
    EXPECT_TRUE(léxico->espuntuación(u8")"));
    EXPECT_TRUE(léxico->espuntuación(u8"="));
    EXPECT_TRUE(léxico->espuntuación(u8"¿"));
    EXPECT_TRUE(léxico->espuntuación(u8"?"));
    EXPECT_TRUE(léxico->espuntuación(u8"¡"));
    EXPECT_TRUE(léxico->espuntuación(u8"!"));
    EXPECT_TRUE(léxico->espuntuación(u8"["));
    EXPECT_TRUE(léxico->espuntuación(u8"]"));
    EXPECT_TRUE(léxico->espuntuación(u8"{"));
    EXPECT_TRUE(léxico->espuntuación(u8"}"));
    EXPECT_TRUE(léxico->espuntuación(u8"^"));
    EXPECT_TRUE(léxico->espuntuación(u8"<"));
    EXPECT_TRUE(léxico->espuntuación(u8">"));
    EXPECT_TRUE(léxico->espuntuación(u8"\\"));
    
    EXPECT_FALSE(léxico->espuntuación("1"));
    EXPECT_FALSE(léxico->espuntuación("9"));
    EXPECT_FALSE(léxico->espuntuación("a"));
    EXPECT_FALSE(léxico->espuntuación("natural"));
    EXPECT_FALSE(léxico->espuntuación("_nat16"));
    EXPECT_FALSE(léxico->espuntuación(" "));
    EXPECT_FALSE(léxico->espuntuación("\n"));
    EXPECT_FALSE(léxico->espuntuación("\t"));
    EXPECT_FALSE(léxico->espuntuación("\r"));
}

TEST(PruebasLexico, esnuevalínea)
{
	Ñ::Léxico* léxico = new Ñ::Léxico();

    EXPECT_TRUE(léxico->esnuevalínea("\n"));
    EXPECT_TRUE(léxico->esnuevalínea("\r"));
    EXPECT_TRUE(léxico->esnuevalínea("\r\n"));
    EXPECT_TRUE(léxico->esnuevalínea(u8"\u2028"));
    EXPECT_TRUE(léxico->esnuevalínea(u8"\u2029"));
    EXPECT_TRUE(léxico->esnuevalínea(u8"\u000D"));
    EXPECT_TRUE(léxico->esnuevalínea(u8"\u000A"));
    EXPECT_TRUE(léxico->esnuevalínea(u8"\u000D\u000A"));
    EXPECT_TRUE(léxico->esnuevalínea(u8"\u0085"));
    
    EXPECT_FALSE(léxico->esnuevalínea("\t"));
    EXPECT_FALSE(léxico->esnuevalínea(" "));
    EXPECT_FALSE(léxico->esnuevalínea("n"));
    EXPECT_FALSE(léxico->esnuevalínea("r"));
    EXPECT_FALSE(léxico->esnuevalínea(""));
    EXPECT_FALSE(léxico->esnuevalínea("1"));
    EXPECT_FALSE(léxico->esnuevalínea("\\"));
    EXPECT_FALSE(léxico->esnuevalínea(","));
}

TEST(PruebasLexico, esespacio)
{
	Ñ::Léxico* léxico = new Ñ::Léxico();

    EXPECT_TRUE(léxico->esespacio("\n"));
    EXPECT_TRUE(léxico->esespacio("\r"));
    EXPECT_TRUE(léxico->esespacio("\r\n"));
    EXPECT_TRUE(léxico->esespacio(" "));
    EXPECT_TRUE(léxico->esespacio("\t"));
    EXPECT_TRUE(léxico->esespacio(u8" "));
    EXPECT_TRUE(léxico->esespacio(u8"\t"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2028"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2029"));
    EXPECT_TRUE(léxico->esespacio(u8"\u000D"));
    EXPECT_TRUE(léxico->esespacio(u8"\u000A"));
    EXPECT_TRUE(léxico->esespacio(u8"\u000D\u000A"));
    EXPECT_TRUE(léxico->esespacio(u8"\u0085"));
    EXPECT_TRUE(léxico->esespacio(u8"\u0020"));
    EXPECT_TRUE(léxico->esespacio(u8"\u00A0"));
    EXPECT_TRUE(léxico->esespacio(u8"\u1680"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2000"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2001"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2002"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2003"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2004"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2005"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2006"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2007"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2008"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2009"));
    EXPECT_TRUE(léxico->esespacio(u8"\u200A"));
    EXPECT_TRUE(léxico->esespacio(u8"\u202F"));
    EXPECT_TRUE(léxico->esespacio(u8"\u205F"));
    EXPECT_TRUE(léxico->esespacio(u8"\u3000"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2028"));
    EXPECT_TRUE(léxico->esespacio(u8"\u2029"));
    EXPECT_TRUE(léxico->esespacio(u8"\u0009"));
    EXPECT_TRUE(léxico->esespacio(u8"\u000B"));
    EXPECT_TRUE(léxico->esespacio(u8"\u000C"));
    EXPECT_TRUE(léxico->esespacio(u8"\u000D"));
    EXPECT_TRUE(léxico->esespacio(u8"\u000A"));
    EXPECT_TRUE(léxico->esespacio(u8"\u000D\u000A"));
    EXPECT_TRUE(léxico->esespacio(u8"\u0085"));
    
    EXPECT_FALSE(léxico->esespacio("n"));
    EXPECT_FALSE(léxico->esespacio("r"));
    EXPECT_FALSE(léxico->esespacio(""));
    EXPECT_FALSE(léxico->esespacio("1"));
    EXPECT_FALSE(léxico->esespacio("\\"));
    EXPECT_FALSE(léxico->esespacio(","));
}

TEST(PruebasLexico, esalfa)
{
	Ñ::Léxico* léxico = new Ñ::Léxico();

    EXPECT_TRUE(léxico->esalfa("a"));
    EXPECT_TRUE(léxico->esalfa("e"));
    EXPECT_TRUE(léxico->esalfa("i"));
    EXPECT_TRUE(léxico->esalfa("o"));
    EXPECT_TRUE(léxico->esalfa("u"));
    EXPECT_TRUE(léxico->esalfa("A"));
    EXPECT_TRUE(léxico->esalfa("E"));
    EXPECT_TRUE(léxico->esalfa("I"));
    EXPECT_TRUE(léxico->esalfa("O"));
    EXPECT_TRUE(léxico->esalfa("U"));
    EXPECT_TRUE(léxico->esalfa("á"));
    EXPECT_TRUE(léxico->esalfa("ë"));
    EXPECT_TRUE(léxico->esalfa("î"));
    EXPECT_TRUE(léxico->esalfa("õ"));
    EXPECT_TRUE(léxico->esalfa("ù"));
    EXPECT_TRUE(léxico->esalfa("Á"));
    EXPECT_TRUE(léxico->esalfa("Ë"));
    EXPECT_TRUE(léxico->esalfa("Î"));
    EXPECT_TRUE(léxico->esalfa("Õ"));
    EXPECT_TRUE(léxico->esalfa("Ù"));
    EXPECT_TRUE(léxico->esalfa("ñ"));
    EXPECT_TRUE(léxico->esalfa("Ñ"));
    EXPECT_TRUE(léxico->esalfa("ç"));
    EXPECT_TRUE(léxico->esalfa("Ç"));
    EXPECT_TRUE(léxico->esalfa("_"));
    EXPECT_TRUE(léxico->esalfa("B"));
    EXPECT_TRUE(léxico->esalfa("c"));
    EXPECT_TRUE(léxico->esalfa("f"));
    EXPECT_TRUE(léxico->esalfa("W"));
    EXPECT_TRUE(léxico->esalfa("z"));
    
    EXPECT_FALSE(léxico->esalfa(""));
    EXPECT_FALSE(léxico->esalfa("\\"));
    EXPECT_FALSE(léxico->esalfa(","));
    EXPECT_FALSE(léxico->esalfa(u8"\u2028"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2029"));
    EXPECT_FALSE(léxico->esalfa(u8"\u000D"));
    EXPECT_FALSE(léxico->esalfa(u8"\u000A"));
    EXPECT_FALSE(léxico->esalfa(u8"\u000D\u000A"));
    EXPECT_FALSE(léxico->esalfa(u8"\u0085"));
    EXPECT_FALSE(léxico->esalfa(u8"\u0020"));
    EXPECT_FALSE(léxico->esalfa(u8"\u00A0"));
    EXPECT_FALSE(léxico->esalfa(u8"\u1680"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2000"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2001"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2002"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2003"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2004"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2005"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2006"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2007"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2008"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2009"));
    EXPECT_FALSE(léxico->esalfa(u8"\u200A"));
    EXPECT_FALSE(léxico->esalfa(u8"\u202F"));
    EXPECT_FALSE(léxico->esalfa(u8"\u205F"));
    EXPECT_FALSE(léxico->esalfa(u8"\u3000"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2028"));
    EXPECT_FALSE(léxico->esalfa(u8"\u2029"));
    EXPECT_FALSE(léxico->esalfa(u8"\u0009"));
    EXPECT_FALSE(léxico->esalfa(u8"\u000B"));
    EXPECT_FALSE(léxico->esalfa(u8"\u000C"));
    EXPECT_FALSE(léxico->esalfa(u8"\u000D"));
    EXPECT_FALSE(léxico->esalfa(u8"\u000A"));
    EXPECT_FALSE(léxico->esalfa(u8"\u000D\u000A"));
    EXPECT_FALSE(léxico->esalfa(u8"\u0085"));
    EXPECT_FALSE(léxico->esalfa("."));
    EXPECT_FALSE(léxico->esalfa(","));
    EXPECT_FALSE(léxico->esalfa(":"));
    EXPECT_FALSE(léxico->esalfa(";"));
    EXPECT_FALSE(léxico->esalfa("-"));
    EXPECT_FALSE(léxico->esalfa("+"));
    EXPECT_FALSE(léxico->esalfa("/"));
    EXPECT_FALSE(léxico->esalfa("*"));
    EXPECT_FALSE(léxico->esalfa("'"));
    EXPECT_FALSE(léxico->esalfa("|"));
    EXPECT_FALSE(léxico->esalfa("@"));
    EXPECT_FALSE(léxico->esalfa("€"));
    EXPECT_FALSE(léxico->esalfa("$"));
    EXPECT_FALSE(léxico->esalfa("%"));
    EXPECT_FALSE(léxico->esalfa("&"));
    EXPECT_FALSE(léxico->esalfa("("));
    EXPECT_FALSE(léxico->esalfa(")"));
    EXPECT_FALSE(léxico->esalfa("="));
    EXPECT_FALSE(léxico->esalfa("¿"));
    EXPECT_FALSE(léxico->esalfa("?"));
    EXPECT_FALSE(léxico->esalfa("¡"));
    EXPECT_FALSE(léxico->esalfa("!"));
    EXPECT_FALSE(léxico->esalfa("["));
    EXPECT_FALSE(léxico->esalfa("]"));
    EXPECT_FALSE(léxico->esalfa("{"));
    EXPECT_FALSE(léxico->esalfa("}"));
    EXPECT_FALSE(léxico->esalfa("^"));
    EXPECT_FALSE(léxico->esalfa("<"));
    EXPECT_FALSE(léxico->esalfa(">"));
    EXPECT_FALSE(léxico->esalfa("\\"));
    EXPECT_FALSE(léxico->esalfa("0"));
    EXPECT_FALSE(léxico->esalfa("1"));
    EXPECT_FALSE(léxico->esalfa("2"));
    EXPECT_FALSE(léxico->esalfa("3"));
    EXPECT_FALSE(léxico->esalfa("4"));
    EXPECT_FALSE(léxico->esalfa("5"));
    EXPECT_FALSE(léxico->esalfa("6"));
    EXPECT_FALSE(léxico->esalfa("7"));
    EXPECT_FALSE(léxico->esalfa("8"));
    EXPECT_FALSE(léxico->esalfa("9"));
    EXPECT_FALSE(léxico->esalfa("0"));
    EXPECT_FALSE(léxico->esalfa("0"));
}

TEST(PruebasLexico, esalfanum)
{
	Ñ::Léxico* léxico = new Ñ::Léxico();

    EXPECT_TRUE(léxico->esalfanum("a"));
    EXPECT_TRUE(léxico->esalfanum("e"));
    EXPECT_TRUE(léxico->esalfanum("i"));
    EXPECT_TRUE(léxico->esalfanum("o"));
    EXPECT_TRUE(léxico->esalfanum("u"));
    EXPECT_TRUE(léxico->esalfanum("A"));
    EXPECT_TRUE(léxico->esalfanum("E"));
    EXPECT_TRUE(léxico->esalfanum("I"));
    EXPECT_TRUE(léxico->esalfanum("O"));
    EXPECT_TRUE(léxico->esalfanum("U"));
    EXPECT_TRUE(léxico->esalfanum("á"));
    EXPECT_TRUE(léxico->esalfanum("ë"));
    EXPECT_TRUE(léxico->esalfanum("î"));
    EXPECT_TRUE(léxico->esalfanum("õ"));
    EXPECT_TRUE(léxico->esalfanum("ù"));
    EXPECT_TRUE(léxico->esalfanum("Á"));
    EXPECT_TRUE(léxico->esalfanum("Ë"));
    EXPECT_TRUE(léxico->esalfanum("Î"));
    EXPECT_TRUE(léxico->esalfanum("Õ"));
    EXPECT_TRUE(léxico->esalfanum("Ù"));
    EXPECT_TRUE(léxico->esalfanum("ñ"));
    EXPECT_TRUE(léxico->esalfanum("Ñ"));
    EXPECT_TRUE(léxico->esalfanum("ç"));
    EXPECT_TRUE(léxico->esalfanum("Ç"));
    EXPECT_TRUE(léxico->esalfanum("_"));
    EXPECT_TRUE(léxico->esalfanum("B"));
    EXPECT_TRUE(léxico->esalfanum("c"));
    EXPECT_TRUE(léxico->esalfanum("f"));
    EXPECT_TRUE(léxico->esalfanum("W"));
    EXPECT_TRUE(léxico->esalfanum("z"));
    EXPECT_TRUE(léxico->esalfanum("0"));
    EXPECT_TRUE(léxico->esalfanum("1"));
    EXPECT_TRUE(léxico->esalfanum("2"));
    EXPECT_TRUE(léxico->esalfanum("3"));
    EXPECT_TRUE(léxico->esalfanum("4"));
    EXPECT_TRUE(léxico->esalfanum("5"));
    EXPECT_TRUE(léxico->esalfanum("6"));
    EXPECT_TRUE(léxico->esalfanum("7"));
    EXPECT_TRUE(léxico->esalfanum("8"));
    EXPECT_TRUE(léxico->esalfanum("9"));
    EXPECT_TRUE(léxico->esalfanum("0"));
    EXPECT_TRUE(léxico->esalfanum("0"));
    
    EXPECT_FALSE(léxico->esalfanum(""));
    EXPECT_FALSE(léxico->esalfanum("\\"));
    EXPECT_FALSE(léxico->esalfanum(","));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2028"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2029"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u000D"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u000A"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u000D\u000A"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u0085"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u0020"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u00A0"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u1680"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2000"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2001"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2002"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2003"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2004"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2005"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2006"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2007"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2008"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2009"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u200A"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u202F"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u205F"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u3000"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2028"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u2029"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u0009"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u000B"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u000C"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u000D"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u000A"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u000D\u000A"));
    EXPECT_FALSE(léxico->esalfanum(u8"\u0085"));
    EXPECT_FALSE(léxico->esalfanum("."));
    EXPECT_FALSE(léxico->esalfanum(","));
    EXPECT_FALSE(léxico->esalfanum(":"));
    EXPECT_FALSE(léxico->esalfanum(";"));
    EXPECT_FALSE(léxico->esalfanum("-"));
    EXPECT_FALSE(léxico->esalfanum("+"));
    EXPECT_FALSE(léxico->esalfanum("/"));
    EXPECT_FALSE(léxico->esalfanum("*"));
    EXPECT_FALSE(léxico->esalfanum("'"));
    EXPECT_FALSE(léxico->esalfanum("|"));
    EXPECT_FALSE(léxico->esalfanum("@"));
    EXPECT_FALSE(léxico->esalfanum("€"));
    EXPECT_FALSE(léxico->esalfanum("$"));
    EXPECT_FALSE(léxico->esalfanum("%"));
    EXPECT_FALSE(léxico->esalfanum("&"));
    EXPECT_FALSE(léxico->esalfanum("("));
    EXPECT_FALSE(léxico->esalfanum(")"));
    EXPECT_FALSE(léxico->esalfanum("="));
    EXPECT_FALSE(léxico->esalfanum("¿"));
    EXPECT_FALSE(léxico->esalfanum("?"));
    EXPECT_FALSE(léxico->esalfanum("¡"));
    EXPECT_FALSE(léxico->esalfanum("!"));
    EXPECT_FALSE(léxico->esalfanum("["));
    EXPECT_FALSE(léxico->esalfanum("]"));
    EXPECT_FALSE(léxico->esalfanum("{"));
    EXPECT_FALSE(léxico->esalfanum("}"));
    EXPECT_FALSE(léxico->esalfanum("^"));
    EXPECT_FALSE(léxico->esalfanum("<"));
    EXPECT_FALSE(léxico->esalfanum(">"));
    EXPECT_FALSE(léxico->esalfanum("\\"));
}
*/

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
    EXPECT_EQ(lexemas[0]->contenido, "€");
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