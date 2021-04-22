#include "gtest/gtest.h"

#define EVALUANDO_PRUEBAS 1

#include "ñ/lexico.hpp"

#include <vector>


TEST(PruebasLexico, incrementaCursor)
{

}

TEST(PruebasLexico, siguienteCarácter)
{

}

TEST(PruebasLexico, esdígito)
{
    EXPECT_TRUE(Ñ::esdígito("0"));
    EXPECT_TRUE(Ñ::esdígito("1"));
    EXPECT_TRUE(Ñ::esdígito("2"));
    EXPECT_TRUE(Ñ::esdígito("3"));
    EXPECT_TRUE(Ñ::esdígito("4"));
    EXPECT_TRUE(Ñ::esdígito("5"));
    EXPECT_TRUE(Ñ::esdígito("6"));
    EXPECT_TRUE(Ñ::esdígito("7"));
    EXPECT_TRUE(Ñ::esdígito("8"));
    EXPECT_TRUE(Ñ::esdígito("9"));
    EXPECT_TRUE(Ñ::esdígito("0"));
    EXPECT_TRUE(Ñ::esdígito("0"));

    EXPECT_FALSE(Ñ::esdígito(""));
    EXPECT_FALSE(Ñ::esdígito("a"));
    EXPECT_FALSE(Ñ::esdígito(","));
    EXPECT_FALSE(Ñ::esdígito("_"));
    EXPECT_FALSE(Ñ::esdígito("!"));
    EXPECT_FALSE(Ñ::esdígito("natural"));
    EXPECT_FALSE(Ñ::esdígito("ent32"));
    EXPECT_FALSE(Ñ::esdígito("real64"));
    EXPECT_FALSE(Ñ::esdígito("x86"));
    EXPECT_FALSE(Ñ::esdígito("\\"));
    EXPECT_FALSE(Ñ::esdígito("?"));
    EXPECT_FALSE(Ñ::esdígito(" "));
    EXPECT_FALSE(Ñ::esdígito("\n"));
    EXPECT_FALSE(Ñ::esdígito("\t"));
    EXPECT_FALSE(Ñ::esdígito("\r"));
}

TEST(PruebasLexico, espuntuación)
{
    EXPECT_TRUE(Ñ::espuntuación("."));
    EXPECT_TRUE(Ñ::espuntuación(","));
    EXPECT_TRUE(Ñ::espuntuación(":"));
    EXPECT_TRUE(Ñ::espuntuación(";"));
    EXPECT_TRUE(Ñ::espuntuación("-"));
    EXPECT_TRUE(Ñ::espuntuación("+"));
    EXPECT_TRUE(Ñ::espuntuación("/"));
    EXPECT_TRUE(Ñ::espuntuación("*"));
    EXPECT_TRUE(Ñ::espuntuación("'"));
    EXPECT_TRUE(Ñ::espuntuación("|"));
    EXPECT_TRUE(Ñ::espuntuación("@"));
    EXPECT_TRUE(Ñ::espuntuación("€"));
    EXPECT_TRUE(Ñ::espuntuación("$"));
    EXPECT_TRUE(Ñ::espuntuación("%"));
    EXPECT_TRUE(Ñ::espuntuación("&"));
    EXPECT_TRUE(Ñ::espuntuación("("));
    EXPECT_TRUE(Ñ::espuntuación(")"));
    EXPECT_TRUE(Ñ::espuntuación("="));
    EXPECT_TRUE(Ñ::espuntuación("¿"));
    EXPECT_TRUE(Ñ::espuntuación("?"));
    EXPECT_TRUE(Ñ::espuntuación("¡"));
    EXPECT_TRUE(Ñ::espuntuación("!"));
    EXPECT_TRUE(Ñ::espuntuación("["));
    EXPECT_TRUE(Ñ::espuntuación("]"));
    EXPECT_TRUE(Ñ::espuntuación("{"));
    EXPECT_TRUE(Ñ::espuntuación("}"));
    EXPECT_TRUE(Ñ::espuntuación("^"));
    EXPECT_TRUE(Ñ::espuntuación("<"));
    EXPECT_TRUE(Ñ::espuntuación(">"));
    EXPECT_TRUE(Ñ::espuntuación("\\"));
    
    EXPECT_TRUE(Ñ::espuntuación(u8"."));
    EXPECT_TRUE(Ñ::espuntuación(u8","));
    EXPECT_TRUE(Ñ::espuntuación(u8":"));
    EXPECT_TRUE(Ñ::espuntuación(u8";"));
    EXPECT_TRUE(Ñ::espuntuación(u8"-"));
    EXPECT_TRUE(Ñ::espuntuación(u8"+"));
    EXPECT_TRUE(Ñ::espuntuación(u8"/"));
    EXPECT_TRUE(Ñ::espuntuación(u8"*"));
    EXPECT_TRUE(Ñ::espuntuación(u8"'"));
    EXPECT_TRUE(Ñ::espuntuación(u8"|"));
    EXPECT_TRUE(Ñ::espuntuación(u8"@"));
    EXPECT_TRUE(Ñ::espuntuación(u8"€"));
    EXPECT_TRUE(Ñ::espuntuación(u8"$"));
    EXPECT_TRUE(Ñ::espuntuación(u8"%"));
    EXPECT_TRUE(Ñ::espuntuación(u8"&"));
    EXPECT_TRUE(Ñ::espuntuación(u8"("));
    EXPECT_TRUE(Ñ::espuntuación(u8")"));
    EXPECT_TRUE(Ñ::espuntuación(u8"="));
    EXPECT_TRUE(Ñ::espuntuación(u8"¿"));
    EXPECT_TRUE(Ñ::espuntuación(u8"?"));
    EXPECT_TRUE(Ñ::espuntuación(u8"¡"));
    EXPECT_TRUE(Ñ::espuntuación(u8"!"));
    EXPECT_TRUE(Ñ::espuntuación(u8"["));
    EXPECT_TRUE(Ñ::espuntuación(u8"]"));
    EXPECT_TRUE(Ñ::espuntuación(u8"{"));
    EXPECT_TRUE(Ñ::espuntuación(u8"}"));
    EXPECT_TRUE(Ñ::espuntuación(u8"^"));
    EXPECT_TRUE(Ñ::espuntuación(u8"<"));
    EXPECT_TRUE(Ñ::espuntuación(u8">"));
    EXPECT_TRUE(Ñ::espuntuación(u8"\\"));
    
    EXPECT_FALSE(Ñ::espuntuación("1"));
    EXPECT_FALSE(Ñ::espuntuación("9"));
    EXPECT_FALSE(Ñ::espuntuación("a"));
    EXPECT_FALSE(Ñ::espuntuación("natural"));
    EXPECT_FALSE(Ñ::espuntuación("_nat16"));
    EXPECT_FALSE(Ñ::espuntuación(" "));
    EXPECT_FALSE(Ñ::espuntuación("\n"));
    EXPECT_FALSE(Ñ::espuntuación("\t"));
    EXPECT_FALSE(Ñ::espuntuación("\r"));
}

TEST(PruebasLexico, esnuevalínea)
{
    EXPECT_TRUE(Ñ::esnuevalínea("\n"));
    EXPECT_TRUE(Ñ::esnuevalínea("\r"));
    EXPECT_TRUE(Ñ::esnuevalínea("\r\n"));
    EXPECT_TRUE(Ñ::esnuevalínea(u8"\u2028"));
    EXPECT_TRUE(Ñ::esnuevalínea(u8"\u2029"));
    EXPECT_TRUE(Ñ::esnuevalínea(u8"\u000D"));
    EXPECT_TRUE(Ñ::esnuevalínea(u8"\u000A"));
    EXPECT_TRUE(Ñ::esnuevalínea(u8"\u000D\u000A"));
    EXPECT_TRUE(Ñ::esnuevalínea(u8"\u0085"));
    
    EXPECT_FALSE(Ñ::esnuevalínea("\t"));
    EXPECT_FALSE(Ñ::esnuevalínea(" "));
    EXPECT_FALSE(Ñ::esnuevalínea("n"));
    EXPECT_FALSE(Ñ::esnuevalínea("r"));
    EXPECT_FALSE(Ñ::esnuevalínea(""));
    EXPECT_FALSE(Ñ::esnuevalínea("1"));
    EXPECT_FALSE(Ñ::esnuevalínea("\\"));
    EXPECT_FALSE(Ñ::esnuevalínea(","));
}

TEST(PruebasLexico, esespacio)
{
    EXPECT_TRUE(Ñ::esespacio("\n"));
    EXPECT_TRUE(Ñ::esespacio("\r"));
    EXPECT_TRUE(Ñ::esespacio("\r\n"));
    EXPECT_TRUE(Ñ::esespacio(" "));
    EXPECT_TRUE(Ñ::esespacio("\t"));
    EXPECT_TRUE(Ñ::esespacio(u8" "));
    EXPECT_TRUE(Ñ::esespacio(u8"\t"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2028"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2029"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u000D"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u000A"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u000D\u000A"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u0085"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u0020"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u00A0"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u1680"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2000"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2001"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2002"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2003"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2004"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2005"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2006"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2007"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2008"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2009"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u200A"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u202F"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u205F"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u3000"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2028"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u2029"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u0009"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u000B"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u000C"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u000D"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u000A"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u000D\u000A"));
    EXPECT_TRUE(Ñ::esespacio(u8"\u0085"));
    
    EXPECT_FALSE(Ñ::esespacio("n"));
    EXPECT_FALSE(Ñ::esespacio("r"));
    EXPECT_FALSE(Ñ::esespacio(""));
    EXPECT_FALSE(Ñ::esespacio("1"));
    EXPECT_FALSE(Ñ::esespacio("\\"));
    EXPECT_FALSE(Ñ::esespacio(","));
}

TEST(PruebasLexico, esalfa)
{
    EXPECT_TRUE(Ñ::esalfa("a"));
    EXPECT_TRUE(Ñ::esalfa("e"));
    EXPECT_TRUE(Ñ::esalfa("i"));
    EXPECT_TRUE(Ñ::esalfa("o"));
    EXPECT_TRUE(Ñ::esalfa("u"));
    EXPECT_TRUE(Ñ::esalfa("A"));
    EXPECT_TRUE(Ñ::esalfa("E"));
    EXPECT_TRUE(Ñ::esalfa("I"));
    EXPECT_TRUE(Ñ::esalfa("O"));
    EXPECT_TRUE(Ñ::esalfa("U"));
    EXPECT_TRUE(Ñ::esalfa("á"));
    EXPECT_TRUE(Ñ::esalfa("ë"));
    EXPECT_TRUE(Ñ::esalfa("î"));
    EXPECT_TRUE(Ñ::esalfa("õ"));
    EXPECT_TRUE(Ñ::esalfa("ù"));
    EXPECT_TRUE(Ñ::esalfa("Á"));
    EXPECT_TRUE(Ñ::esalfa("Ë"));
    EXPECT_TRUE(Ñ::esalfa("Î"));
    EXPECT_TRUE(Ñ::esalfa("Õ"));
    EXPECT_TRUE(Ñ::esalfa("Ù"));
    EXPECT_TRUE(Ñ::esalfa("ñ"));
    EXPECT_TRUE(Ñ::esalfa("Ñ"));
    EXPECT_TRUE(Ñ::esalfa("ç"));
    EXPECT_TRUE(Ñ::esalfa("Ç"));
    EXPECT_TRUE(Ñ::esalfa("_"));
    EXPECT_TRUE(Ñ::esalfa("B"));
    EXPECT_TRUE(Ñ::esalfa("c"));
    EXPECT_TRUE(Ñ::esalfa("f"));
    EXPECT_TRUE(Ñ::esalfa("W"));
    EXPECT_TRUE(Ñ::esalfa("z"));
    
    EXPECT_FALSE(Ñ::esalfa(""));
    EXPECT_FALSE(Ñ::esalfa("\\"));
    EXPECT_FALSE(Ñ::esalfa(","));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2028"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2029"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u000D"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u000A"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u000D\u000A"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u0085"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u0020"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u00A0"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u1680"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2000"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2001"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2002"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2003"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2004"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2005"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2006"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2007"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2008"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2009"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u200A"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u202F"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u205F"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u3000"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2028"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u2029"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u0009"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u000B"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u000C"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u000D"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u000A"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u000D\u000A"));
    EXPECT_FALSE(Ñ::esalfa(u8"\u0085"));
    EXPECT_FALSE(Ñ::esalfa("."));
    EXPECT_FALSE(Ñ::esalfa(","));
    EXPECT_FALSE(Ñ::esalfa(":"));
    EXPECT_FALSE(Ñ::esalfa(";"));
    EXPECT_FALSE(Ñ::esalfa("-"));
    EXPECT_FALSE(Ñ::esalfa("+"));
    EXPECT_FALSE(Ñ::esalfa("/"));
    EXPECT_FALSE(Ñ::esalfa("*"));
    EXPECT_FALSE(Ñ::esalfa("'"));
    EXPECT_FALSE(Ñ::esalfa("|"));
    EXPECT_FALSE(Ñ::esalfa("@"));
    EXPECT_FALSE(Ñ::esalfa("€"));
    EXPECT_FALSE(Ñ::esalfa("$"));
    EXPECT_FALSE(Ñ::esalfa("%"));
    EXPECT_FALSE(Ñ::esalfa("&"));
    EXPECT_FALSE(Ñ::esalfa("("));
    EXPECT_FALSE(Ñ::esalfa(")"));
    EXPECT_FALSE(Ñ::esalfa("="));
    EXPECT_FALSE(Ñ::esalfa("¿"));
    EXPECT_FALSE(Ñ::esalfa("?"));
    EXPECT_FALSE(Ñ::esalfa("¡"));
    EXPECT_FALSE(Ñ::esalfa("!"));
    EXPECT_FALSE(Ñ::esalfa("["));
    EXPECT_FALSE(Ñ::esalfa("]"));
    EXPECT_FALSE(Ñ::esalfa("{"));
    EXPECT_FALSE(Ñ::esalfa("}"));
    EXPECT_FALSE(Ñ::esalfa("^"));
    EXPECT_FALSE(Ñ::esalfa("<"));
    EXPECT_FALSE(Ñ::esalfa(">"));
    EXPECT_FALSE(Ñ::esalfa("\\"));
    EXPECT_FALSE(Ñ::esalfa("0"));
    EXPECT_FALSE(Ñ::esalfa("1"));
    EXPECT_FALSE(Ñ::esalfa("2"));
    EXPECT_FALSE(Ñ::esalfa("3"));
    EXPECT_FALSE(Ñ::esalfa("4"));
    EXPECT_FALSE(Ñ::esalfa("5"));
    EXPECT_FALSE(Ñ::esalfa("6"));
    EXPECT_FALSE(Ñ::esalfa("7"));
    EXPECT_FALSE(Ñ::esalfa("8"));
    EXPECT_FALSE(Ñ::esalfa("9"));
    EXPECT_FALSE(Ñ::esalfa("0"));
    EXPECT_FALSE(Ñ::esalfa("0"));
}

TEST(PruebasLexico, esalfanum)
{
    EXPECT_TRUE(Ñ::esalfanum("a"));
    EXPECT_TRUE(Ñ::esalfanum("e"));
    EXPECT_TRUE(Ñ::esalfanum("i"));
    EXPECT_TRUE(Ñ::esalfanum("o"));
    EXPECT_TRUE(Ñ::esalfanum("u"));
    EXPECT_TRUE(Ñ::esalfanum("A"));
    EXPECT_TRUE(Ñ::esalfanum("E"));
    EXPECT_TRUE(Ñ::esalfanum("I"));
    EXPECT_TRUE(Ñ::esalfanum("O"));
    EXPECT_TRUE(Ñ::esalfanum("U"));
    EXPECT_TRUE(Ñ::esalfanum("á"));
    EXPECT_TRUE(Ñ::esalfanum("ë"));
    EXPECT_TRUE(Ñ::esalfanum("î"));
    EXPECT_TRUE(Ñ::esalfanum("õ"));
    EXPECT_TRUE(Ñ::esalfanum("ù"));
    EXPECT_TRUE(Ñ::esalfanum("Á"));
    EXPECT_TRUE(Ñ::esalfanum("Ë"));
    EXPECT_TRUE(Ñ::esalfanum("Î"));
    EXPECT_TRUE(Ñ::esalfanum("Õ"));
    EXPECT_TRUE(Ñ::esalfanum("Ù"));
    EXPECT_TRUE(Ñ::esalfanum("ñ"));
    EXPECT_TRUE(Ñ::esalfanum("Ñ"));
    EXPECT_TRUE(Ñ::esalfanum("ç"));
    EXPECT_TRUE(Ñ::esalfanum("Ç"));
    EXPECT_TRUE(Ñ::esalfanum("_"));
    EXPECT_TRUE(Ñ::esalfanum("B"));
    EXPECT_TRUE(Ñ::esalfanum("c"));
    EXPECT_TRUE(Ñ::esalfanum("f"));
    EXPECT_TRUE(Ñ::esalfanum("W"));
    EXPECT_TRUE(Ñ::esalfanum("z"));
    EXPECT_TRUE(Ñ::esalfanum("0"));
    EXPECT_TRUE(Ñ::esalfanum("1"));
    EXPECT_TRUE(Ñ::esalfanum("2"));
    EXPECT_TRUE(Ñ::esalfanum("3"));
    EXPECT_TRUE(Ñ::esalfanum("4"));
    EXPECT_TRUE(Ñ::esalfanum("5"));
    EXPECT_TRUE(Ñ::esalfanum("6"));
    EXPECT_TRUE(Ñ::esalfanum("7"));
    EXPECT_TRUE(Ñ::esalfanum("8"));
    EXPECT_TRUE(Ñ::esalfanum("9"));
    EXPECT_TRUE(Ñ::esalfanum("0"));
    EXPECT_TRUE(Ñ::esalfanum("0"));
    
    EXPECT_FALSE(Ñ::esalfanum(""));
    EXPECT_FALSE(Ñ::esalfanum("\\"));
    EXPECT_FALSE(Ñ::esalfanum(","));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2028"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2029"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u000D"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u000A"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u000D\u000A"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u0085"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u0020"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u00A0"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u1680"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2000"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2001"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2002"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2003"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2004"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2005"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2006"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2007"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2008"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2009"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u200A"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u202F"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u205F"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u3000"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2028"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u2029"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u0009"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u000B"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u000C"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u000D"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u000A"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u000D\u000A"));
    EXPECT_FALSE(Ñ::esalfanum(u8"\u0085"));
    EXPECT_FALSE(Ñ::esalfanum("."));
    EXPECT_FALSE(Ñ::esalfanum(","));
    EXPECT_FALSE(Ñ::esalfanum(":"));
    EXPECT_FALSE(Ñ::esalfanum(";"));
    EXPECT_FALSE(Ñ::esalfanum("-"));
    EXPECT_FALSE(Ñ::esalfanum("+"));
    EXPECT_FALSE(Ñ::esalfanum("/"));
    EXPECT_FALSE(Ñ::esalfanum("*"));
    EXPECT_FALSE(Ñ::esalfanum("'"));
    EXPECT_FALSE(Ñ::esalfanum("|"));
    EXPECT_FALSE(Ñ::esalfanum("@"));
    EXPECT_FALSE(Ñ::esalfanum("€"));
    EXPECT_FALSE(Ñ::esalfanum("$"));
    EXPECT_FALSE(Ñ::esalfanum("%"));
    EXPECT_FALSE(Ñ::esalfanum("&"));
    EXPECT_FALSE(Ñ::esalfanum("("));
    EXPECT_FALSE(Ñ::esalfanum(")"));
    EXPECT_FALSE(Ñ::esalfanum("="));
    EXPECT_FALSE(Ñ::esalfanum("¿"));
    EXPECT_FALSE(Ñ::esalfanum("?"));
    EXPECT_FALSE(Ñ::esalfanum("¡"));
    EXPECT_FALSE(Ñ::esalfanum("!"));
    EXPECT_FALSE(Ñ::esalfanum("["));
    EXPECT_FALSE(Ñ::esalfanum("]"));
    EXPECT_FALSE(Ñ::esalfanum("{"));
    EXPECT_FALSE(Ñ::esalfanum("}"));
    EXPECT_FALSE(Ñ::esalfanum("^"));
    EXPECT_FALSE(Ñ::esalfanum("<"));
    EXPECT_FALSE(Ñ::esalfanum(">"));
    EXPECT_FALSE(Ñ::esalfanum("\\"));
}

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

/*
TEST(PruebasLexico, Notacion)
{
    std::vector<Ñ::Lexema*> lexemas;

    // Punto
    lexemas = Ñ::analizaLéxico(u8".");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8".");
    EXPECT_EQ(lexemas[0]->contenido, ".");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Coma
    lexemas = Ñ::analizaLéxico(u8",");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8",");
    EXPECT_EQ(lexemas[0]->contenido, ",");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Dos puntos
    lexemas = Ñ::analizaLéxico(u8":");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8":");
    EXPECT_EQ(lexemas[0]->contenido, ":");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Punto y coma
    lexemas = Ñ::analizaLéxico(u8";");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8";");
    EXPECT_EQ(lexemas[0]->contenido, ";");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Guión
    lexemas = Ñ::analizaLéxico(u8"-");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"-");
    EXPECT_EQ(lexemas[0]->contenido, "-");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Suma
    lexemas = Ñ::analizaLéxico(u8"+");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"+");
    EXPECT_EQ(lexemas[0]->contenido, "+");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Barra
    lexemas = Ñ::analizaLéxico(u8"/");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"/");
    EXPECT_EQ(lexemas[0]->contenido, "/");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Barra invertida
    lexemas = Ñ::analizaLéxico(u8"\\");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"\\");
    EXPECT_EQ(lexemas[0]->contenido, "\\");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Asterisco
    lexemas = Ñ::analizaLéxico(u8"*");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"*");
    EXPECT_EQ(lexemas[0]->contenido, "*");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Comilla simple
    lexemas = Ñ::analizaLéxico(u8"'");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"'");
    EXPECT_EQ(lexemas[0]->contenido, "'");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Barra vertical
    lexemas = Ñ::analizaLéxico(u8"|");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"|");
    EXPECT_EQ(lexemas[0]->contenido, "|");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Arroba
    lexemas = Ñ::analizaLéxico(u8"@");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"@");
    EXPECT_EQ(lexemas[0]->contenido, "@");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Euro
    lexemas = Ñ::analizaLéxico(u8"€");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"€");
    EXPECT_EQ(lexemas[0]->contenido, "€");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Dólar
    lexemas = Ñ::analizaLéxico(u8"$");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"$");
    EXPECT_EQ(lexemas[0]->contenido, "$");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Porciento
    lexemas = Ñ::analizaLéxico(u8"%");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"%");
    EXPECT_EQ(lexemas[0]->contenido, "%");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // et
    lexemas = Ñ::analizaLéxico(u8"&");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"&");
    EXPECT_EQ(lexemas[0]->contenido, "&");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Abre paréntesis
    lexemas = Ñ::analizaLéxico(u8"(");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"(");
    EXPECT_EQ(lexemas[0]->contenido, "(");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Cierra paréntesis)
    lexemas = Ñ::analizaLéxico(u8")");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8")");
    EXPECT_EQ(lexemas[0]->contenido, ")");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Igual
    lexemas = Ñ::analizaLéxico(u8"=");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"=");
    EXPECT_EQ(lexemas[0]->contenido, "=");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Abre interrogación
    lexemas = Ñ::analizaLéxico(u8"¿");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"¿");
    EXPECT_EQ(lexemas[0]->contenido, "¿");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Cierra interrogación
    lexemas = Ñ::analizaLéxico(u8"?");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"?");
    EXPECT_EQ(lexemas[0]->contenido, "?");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Abre exclamación
    lexemas = Ñ::analizaLéxico(u8"¡");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"¡");
    EXPECT_EQ(lexemas[0]->contenido, "¡");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Cierra exclamación
    lexemas = Ñ::analizaLéxico(u8"!");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"!");
    EXPECT_EQ(lexemas[0]->contenido, "!");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Abre corchete
    lexemas = Ñ::analizaLéxico(u8"[");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"[");
    EXPECT_EQ(lexemas[0]->contenido, "[");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Cierra corchete
    lexemas = Ñ::analizaLéxico(u8"]");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"]");
    EXPECT_EQ(lexemas[0]->contenido, "]");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Abre llave
    lexemas = Ñ::analizaLéxico(u8"{");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"{");
    EXPECT_EQ(lexemas[0]->contenido, "{");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Cierra llave
    lexemas = Ñ::analizaLéxico(u8"}");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"}");
    EXPECT_EQ(lexemas[0]->contenido, "}");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Caret / acento circunflejo
    lexemas = Ñ::analizaLéxico(u8"^");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"^");
    EXPECT_EQ(lexemas[0]->contenido, "^");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Menor que
    lexemas = Ñ::analizaLéxico(u8"<");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"<");
    EXPECT_EQ(lexemas[0]->contenido, "<");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }


    // Mayor que
    lexemas = Ñ::analizaLéxico(u8">");
    EXPECT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8">");
    EXPECT_EQ(lexemas[0]->contenido, ">");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
}
*/