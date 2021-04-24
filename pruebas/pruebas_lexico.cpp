#include "pruebas.hpp"

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
    EXPECT_TRUE(Ñ::espuntuación("\""));
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
    EXPECT_TRUE(Ñ::espuntuación(u8"\""));
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
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"");
    ASSERT_EQ(lexemas.size(), 1);
    EXPECT_EQ(lexemas[0]->contenido, u8"");
    EXPECT_EQ(lexemas[0]->contenido, "");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);
    for(auto l : lexemas) { delete l; }
    delete léxico;

	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza("");
    ASSERT_EQ(lexemas.size(), 1);
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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

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
    ASSERT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8">");
    EXPECT_EQ(lexemas[0]->contenido, ">");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_NOTACIÓN);

    EXPECT_EQ(lexemas[1]->contenido, u8"");
    EXPECT_EQ(lexemas[1]->contenido, "");
    EXPECT_EQ(lexemas[1]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
}

TEST(PruebasLexico, Reservada)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

    // Reservada
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"");
    ASSERT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"");
    EXPECT_EQ(lexemas[0]->contenido, "");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
}

TEST(PruebasLexico, Números)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

    // Reservada
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"");
    ASSERT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"");
    EXPECT_EQ(lexemas[0]->contenido, "");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
}

TEST(PruebasLexico, Texto)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

    // Reservada
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"");
    ASSERT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"");
    EXPECT_EQ(lexemas[0]->contenido, "");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

    for(auto l : lexemas) { delete l; }
    delete léxico;
}

TEST(PruebasLexico, Comentarios)
{
    Ñ::Léxico* léxico;
    std::vector<Ñ::Lexema*> lexemas;

    // Reservada
	léxico = new Ñ::Léxico();
    lexemas = léxico->analiza(u8"");
    ASSERT_EQ(lexemas.size(), 2);

    EXPECT_EQ(lexemas[0]->contenido, u8"");
    EXPECT_EQ(lexemas[0]->contenido, "");
    EXPECT_EQ(lexemas[0]->categoría, Ñ::CategoríaLexema::LEXEMA_FIN);

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
    ASSERT_EQ(lexemas.size(), 4);

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
    ASSERT_EQ(lexemas.size(), 6);

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
    ASSERT_EQ(lexemas.size(), 8);

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
    ASSERT_EQ(lexemas.size(), 6);

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