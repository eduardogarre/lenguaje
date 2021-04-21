#include "gtest/gtest.h"
#include "../ñ/nodo.hpp"

TEST(PruebasNodos, DuplicaNodos)
{
    Ñ::Literal* lit1 = new Ñ::Literal();
    Ñ::Literal* lit2;
    lit1->dato = "hola";
    lit2 = (Ñ::Literal*) Ñ::duplicaNodo((Ñ::Nodo*)lit1);
    EXPECT_EQ(lit1->dato, lit2->dato);
}