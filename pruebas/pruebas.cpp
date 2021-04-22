#include "gtest/gtest.h"
#include "../ñ/nodo.hpp"

/*
TEST(PruebasNodos, DuplicaNodos)
{
    Ñ::Literal* literal1 = new Ñ::Literal();
    Ñ::Literal* literal2;
    literal1->dato = "hola";
    literal2 = (Ñ::Literal*) Ñ::duplicaNodo((Ñ::Nodo*)literal1);
    EXPECT_EQ(literal1->dato, literal2->dato);
}
*/

TEST(Prueba, Ejemplo)
{
    EXPECT_EQ(1, 1);
}