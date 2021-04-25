#include "pruebas.hpp"

#include "ñ/lexema.hpp"
#include "ñ/nodo.hpp"
#include "ñ/sintaxis.hpp"

#include <vector>

TEST(PruebasSintaxis, literal)
{
    Ñ::Nodo* r;
    std::vector<Ñ::Lexema*> l;
    Ñ::Lexema* l1;
    Ñ::Lexema* l2;
    Ñ::Lexema* l3;
    Ñ::Lexema* l4;
    Ñ::Lexema* l5;
    Ñ::Lexema* l6;
    Ñ::Lexema* l7;
    Ñ::Lexema* l8;
    Ñ::Lexema* l9;
    Ñ::Nodo* n;
    Ñ::Nodo* n1;
    Ñ::Nodo* n2;
    Ñ::Nodo* n3;
    Ñ::Nodo* n4;
    Ñ::Nodo* n5;
    Ñ::Nodo* n6;
    Ñ::Nodo* n7;
    Ñ::Nodo* n8;
    Ñ::Nodo* n9;
    
    // Declaración
    l1 = new Ñ::Lexema();
    l1->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
    l1->contenido = "natural";
    l.push_back(l1);

    l2 = new Ñ::Lexema();
    l2->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
    l2->contenido = "a";
    l.push_back(l2);

    l3 = new Ñ::Lexema();
    l3->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l3->contenido = ";";
    l.push_back(l3);

    l4 = new Ñ::Lexema();
    l4->categoría = Ñ::CategoríaLexema::LEXEMA_FIN;
    l.push_back(l4);

    n = (Ñ::Nodo*)(new Ñ::Expresión());
    n1 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    ((Ñ::DeclaraVariable*)n1)->variable = "a";
    n2 = (Ñ::Nodo*)(new Ñ::Tipo());
    ((Ñ::Tipo*)n2)->tipo = "natural";
    ((Ñ::Tipo*)n2)->vector = false;
    n1->ramas.push_back(n2);
    n->ramas.push_back(n1);

    r = Ñ::analizaSintaxis(l);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n, r));

    l.clear();
    delete r, n2, n1, n, l4, l3, l2, l1;
    
    // Asignación
    l1 = new Ñ::Lexema();
    l1->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
    l1->contenido = "b";
    l.push_back(l1);

    l2 = new Ñ::Lexema();
    l2->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l2->contenido = "=";
    l.push_back(l2);

    l3 = new Ñ::Lexema();
    l3->categoría = Ñ::CategoríaLexema::LEXEMA_NÚMERO;
    l3->contenido = "288";
    l.push_back(l3);

    l4 = new Ñ::Lexema();
    l4->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l4->contenido = ";";
    l.push_back(l4);

    l5 = new Ñ::Lexema();
    l5->categoría = Ñ::CategoríaLexema::LEXEMA_FIN;
    l.push_back(l5);

    n = (Ñ::Nodo*)(new Ñ::Expresión());
    n1 = (Ñ::Nodo*)(new Ñ::Asigna());
    n2 = (Ñ::Nodo*)(new Ñ::Identificador());
    ((Ñ::Identificador*)n2)->id = "b";
    n3 = (Ñ::Nodo*)(new Ñ::Literal());
    ((Ñ::Literal*)n3)->dato = "288";
    n1->ramas.push_back(n2);
    n1->ramas.push_back(n3);
    n->ramas.push_back(n1);

    r = Ñ::analizaSintaxis(l);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n, r));

    l.clear();
    delete r, n3, n2, n1, n, l5, l4, l3, l2, l1;
    
    // Asignación
    l1 = new Ñ::Lexema();
    l1->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
    l1->contenido = "c";
    l.push_back(l1);

    l2 = new Ñ::Lexema();
    l2->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l2->contenido = "=";
    l.push_back(l2);

    l3 = new Ñ::Lexema();
    l3->categoría = Ñ::CategoríaLexema::LEXEMA_TEXTO;
    l3->contenido = "prueba";
    l.push_back(l3);

    l4 = new Ñ::Lexema();
    l4->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l4->contenido = ";";
    l.push_back(l4);

    l5 = new Ñ::Lexema();
    l5->categoría = Ñ::CategoríaLexema::LEXEMA_FIN;
    l.push_back(l5);

    n = (Ñ::Nodo*)(new Ñ::Expresión());
    n1 = (Ñ::Nodo*)(new Ñ::Asigna());
    n2 = (Ñ::Nodo*)(new Ñ::Identificador());
    ((Ñ::Identificador*)n2)->id = "c";
    n3 = (Ñ::Nodo*)(new Ñ::Literal());
    ((Ñ::Literal*)n3)->dato = "prueba";
    n1->ramas.push_back(n2);
    n1->ramas.push_back(n3);
    n->ramas.push_back(n1);

    r = Ñ::analizaSintaxis(l);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n, r));

    l.clear();
    delete r, n3, n2, n1, n, l5, l4, l3, l2, l1;
    
    // Declaración y asignación
    l1 = new Ñ::Lexema();
    l1->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
    l1->contenido = "natural";
    l.push_back(l1);

    l2 = new Ñ::Lexema();
    l2->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
    l2->contenido = "b";
    l.push_back(l2);

    l3 = new Ñ::Lexema();
    l3->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l3->contenido = "=";
    l.push_back(l3);

    l4 = new Ñ::Lexema();
    l4->categoría = Ñ::CategoríaLexema::LEXEMA_NÚMERO;
    l4->contenido = "288";
    l.push_back(l4);

    l5 = new Ñ::Lexema();
    l5->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l5->contenido = ";";
    l.push_back(l5);

    l6 = new Ñ::Lexema();
    l6->categoría = Ñ::CategoríaLexema::LEXEMA_FIN;
    l.push_back(l6);

    n = (Ñ::Nodo*)(new Ñ::Expresión());
    n1 = (Ñ::Nodo*)(new Ñ::Asigna());
    n2 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    ((Ñ::DeclaraVariable*)n2)->variable = "b";
    n3 = (Ñ::Nodo*)(new Ñ::Tipo());
    ((Ñ::Tipo*)n3)->tipo = "natural";
    ((Ñ::Tipo*)n3)->vector = false;
    n4 = (Ñ::Nodo*)(new Ñ::Literal());
    ((Ñ::Literal*)n4)->dato = "288";
    n2->ramas.push_back(n3);
    n1->ramas.push_back(n2);
    n1->ramas.push_back(n4);
    n->ramas.push_back(n1);

    r = Ñ::analizaSintaxis(l);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n, r));

    l.clear();
    delete r, n4, n3, n2, n1, n, l6, l5, l4, l3, l2, l1;
    
    // Llama función
    l1 = new Ñ::Lexema();
    l1->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
    l1->contenido = "apaga";
    l.push_back(l1);

    l2 = new Ñ::Lexema();
    l2->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l2->contenido = "(";
    l.push_back(l2);

    l3 = new Ñ::Lexema();
    l3->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l3->contenido = ")";
    l.push_back(l3);

    l4 = new Ñ::Lexema();
    l4->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l4->contenido = ";";
    l.push_back(l4);

    l5 = new Ñ::Lexema();
    l5->categoría = Ñ::CategoríaLexema::LEXEMA_FIN;
    l.push_back(l5);

    n = (Ñ::Nodo*)(new Ñ::Expresión());
    n1 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    ((Ñ::LlamaFunción*)n1)->función = "apaga";
    n->ramas.push_back(n1);

    r = Ñ::analizaSintaxis(l);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n, r));

    l.clear();
    delete r, n2, n1, n, l5, l4, l3, l2, l1;
    
    // Llama función con argumento
    l1 = new Ñ::Lexema();
    l1->categoría = Ñ::CategoríaLexema::LEXEMA_IDENTIFICADOR;
    l1->contenido = "escribe";
    l.push_back(l1);

    l2 = new Ñ::Lexema();
    l2->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l2->contenido = "(";
    l.push_back(l2);

    l3 = new Ñ::Lexema();
    l3->categoría = Ñ::CategoríaLexema::LEXEMA_TEXTO;
    l3->contenido = "hola, mundo\n";
    l.push_back(l3);

    l4 = new Ñ::Lexema();
    l4->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l4->contenido = ")";
    l.push_back(l4);

    l5 = new Ñ::Lexema();
    l5->categoría = Ñ::CategoríaLexema::LEXEMA_NOTACIÓN;
    l5->contenido = ";";
    l.push_back(l5);

    l6 = new Ñ::Lexema();
    l6->categoría = Ñ::CategoríaLexema::LEXEMA_FIN;
    l.push_back(l6);

    n = (Ñ::Nodo*)(new Ñ::Expresión());
    n1 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    ((Ñ::LlamaFunción*)n1)->función = "escribe";
    n2 = (Ñ::Nodo*)(new Ñ::Argumentos());
    n3 = (Ñ::Nodo*)(new Ñ::Literal());
    ((Ñ::Literal*)n3)->dato = "hola, mundo\n";
    n2->ramas.push_back(n3);
    n1->ramas.push_back(n2);
    n->ramas.push_back(n1);

    r = Ñ::analizaSintaxis(l);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n, r));
    Ñ::muestraNodos(n);
    Ñ::muestraNodos(r);

    l.clear();
    delete r, n2, n1, n, l5, l4, l3, l2, l1;
}