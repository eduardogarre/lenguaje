#include "pruebas.hpp"

#include "ñ/nodo.hpp"

#include <vector>

TEST(PruebasNodo, sonArbolesDuplicados)
{
    Ñ::Nodo* n1;
    Ñ::Nodo* n2;
    Ñ::Nodo* n3;
    Ñ::Nodo* n4;
    Ñ::Nodo* n5;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();

    // Debe descartar si cualquiera de los objetos es nulo
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(NULL, n2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, NULL));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(NULL, NULL));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(nullptr, n2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, nullptr));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(nullptr, nullptr));

    // Debe reconocer que los 2 objetos son iguales
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    // Debe descartarlos si son el mismo objeto en la misma dirección de memoria
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n1));
    delete n1, n2;
    
    // Debe funcionar en clases derivadas
    Ñ::Literal* l1 = new Ñ::Literal();
    Ñ::Literal* l2 = new Ñ::Literal();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)l1, (Ñ::Nodo*)l2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)l1, (Ñ::Nodo*)l1));
    // Debe comprobar el contenido de los nodos
    l1->dato = "prueba";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)l1, (Ñ::Nodo*)l2));
    l2->dato = "prueba";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)l1, (Ñ::Nodo*)l2));
    delete l1, l2;
    

    Ñ::Identificador* id1 = new Ñ::Identificador();
    Ñ::Identificador* id2 = new Ñ::Identificador();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)id1, (Ñ::Nodo*)id2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)id1, (Ñ::Nodo*)id1));
    // Debe comprobar el contenido de los nodos
    id1->id = "prueba";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)id1, (Ñ::Nodo*)id2));
    id2->id = "prueba";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)id1, (Ñ::Nodo*)id2));
    delete id1, id2;
    

    Ñ::Tipo* t1 = new Ñ::Tipo();
    Ñ::Tipo* t2 = new Ñ::Tipo();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)t1, (Ñ::Nodo*)t2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)t1, (Ñ::Nodo*)t1));
    // Debe comprobar el contenido de los nodos
    t1->tipo = "prueba";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)t1, (Ñ::Nodo*)t2));
    t2->tipo = "prueba";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)t1, (Ñ::Nodo*)t2));
    t1->vector = true;
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)t1, (Ñ::Nodo*)t2));
    t2->vector = true;
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)t1, (Ñ::Nodo*)t2));
    delete t1, t2;
    

    Ñ::OpSumaResta* osr1 = new Ñ::OpSumaResta();
    Ñ::OpSumaResta* osr2 = new Ñ::OpSumaResta();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)osr1, (Ñ::Nodo*)osr2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)osr1, (Ñ::Nodo*)osr1));
    // Debe comprobar el contenido de los nodos
    osr1->operación = "+";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)osr1, (Ñ::Nodo*)osr2));
    osr2->operación = "+";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)osr1, (Ñ::Nodo*)osr2));
    osr1->operación = "-";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)osr1, (Ñ::Nodo*)osr2));
    osr2->operación = "-";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)osr1, (Ñ::Nodo*)osr2));
    delete osr1, osr2;
    

    Ñ::OpMultiplicaciónDivisión* omd1 = new Ñ::OpMultiplicaciónDivisión();
    Ñ::OpMultiplicaciónDivisión* omd2 = new Ñ::OpMultiplicaciónDivisión();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)omd1, (Ñ::Nodo*)omd2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)omd1, (Ñ::Nodo*)omd1));
    omd1->operación = "*";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)omd1, (Ñ::Nodo*)omd2));
    omd2->operación = "*";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)omd1, (Ñ::Nodo*)omd2));
    omd1->operación = "/";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)omd1, (Ñ::Nodo*)omd2));
    omd2->operación = "/";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)omd1, (Ñ::Nodo*)omd2));
    delete omd1, omd2;
    

    Ñ::Factor* fx1 = new Ñ::Factor();
    Ñ::Factor* fx2 = new Ñ::Factor();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)fx1, (Ñ::Nodo*)fx2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)fx1, (Ñ::Nodo*)fx1));
    fx1->factor = "288";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)fx1, (Ñ::Nodo*)fx2));
    fx2->factor = "288";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)fx1, (Ñ::Nodo*)fx2));
    fx1->factor = "prueba";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)fx1, (Ñ::Nodo*)fx2));
    fx2->factor = "prueba";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)fx1, (Ñ::Nodo*)fx2));
    delete fx1, fx2;
    

    Ñ::DeclaraVariable* dv1 = new Ñ::DeclaraVariable();
    Ñ::DeclaraVariable* dv2 = new Ñ::DeclaraVariable();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)dv1, (Ñ::Nodo*)dv2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)dv1, (Ñ::Nodo*)dv1));
    dv1->variable = "prueba";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)dv1, (Ñ::Nodo*)dv2));
    dv2->variable = "prueba";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)dv1, (Ñ::Nodo*)dv2));
    delete dv1, dv2;
    

    Ñ::Asigna* as1 = new Ñ::Asigna();
    Ñ::Asigna* as2 = new Ñ::Asigna();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)as1, (Ñ::Nodo*)as2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)as1, (Ñ::Nodo*)as1));
    delete as1, as2;
    

    Ñ::Argumento* ar1 = new Ñ::Argumento();
    Ñ::Argumento* ar2 = new Ñ::Argumento();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)ar1, (Ñ::Nodo*)ar2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)ar1, (Ñ::Nodo*)ar1));
    delete ar1, ar2;
    

    Ñ::Argumentos* ars1 = new Ñ::Argumentos();
    Ñ::Argumentos* ars2 = new Ñ::Argumentos();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)ars1, (Ñ::Nodo*)ars2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)ars1, (Ñ::Nodo*)ars1));
    delete ars1, ars2;
    

    Ñ::LlamaFunción* lfn1 = new Ñ::LlamaFunción();
    Ñ::LlamaFunción* lfn2 = new Ñ::LlamaFunción();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)lfn1, (Ñ::Nodo*)lfn2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)lfn1, (Ñ::Nodo*)lfn1));
    lfn1->función = "prueba";
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)lfn1, (Ñ::Nodo*)lfn2));
    lfn2->función = "prueba";
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)lfn1, (Ñ::Nodo*)lfn2));
    delete lfn1, lfn2;
    

    Ñ::Expresión* ex1 = new Ñ::Expresión();
    Ñ::Expresión* ex2 = new Ñ::Expresión();
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)ex1, (Ñ::Nodo*)ex2));
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados((Ñ::Nodo*)ex1, (Ñ::Nodo*)ex1));
    delete ex1, ex2;
    

    // Debe comprobar que los nodos tengan el mismo número de hijos
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = new Ñ::Nodo();
    n4 = new Ñ::Nodo();
    n5 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n5);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n5, n4, n3, n2, n1;
    
    

    // Debe comprobar que los nodos tengan hijos del mismo tipo
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Literal());
    n4 = (Ñ::Nodo*)(new Ñ::Literal());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Literal());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    // Debe comprobar que los nodos hijos tengan el mismo contenido
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Literal());
    n4 = (Ñ::Nodo*)(new Ñ::Literal());
    ((Ñ::Literal*)n3)->dato = "prueba";
    ((Ñ::Literal*)n4)->dato = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Literal());
    n4 = (Ñ::Nodo*)(new Ñ::Literal());
    ((Ñ::Literal*)n3)->dato = "asdf";
    ((Ñ::Literal*)n4)->dato = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Identificador());
    n4 = (Ñ::Nodo*)(new Ñ::Identificador());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Identificador());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Identificador());
    n4 = (Ñ::Nodo*)(new Ñ::Identificador());
    ((Ñ::Identificador*)n3)->id = "prueba";
    ((Ñ::Identificador*)n4)->id = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Identificador());
    n4 = (Ñ::Nodo*)(new Ñ::Identificador());
    ((Ñ::Identificador*)n3)->id = "asdf";
    ((Ñ::Identificador*)n4)->id = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Tipo());
    n4 = (Ñ::Nodo*)(new Ñ::Tipo());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Tipo());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Tipo());
    n4 = (Ñ::Nodo*)(new Ñ::Tipo());
    ((Ñ::Tipo*)n3)->tipo = "prueba";
    ((Ñ::Tipo*)n4)->tipo = "prueba";
    ((Ñ::Tipo*)n3)->vector = true;
    ((Ñ::Tipo*)n4)->vector = true;
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Tipo());
    n4 = (Ñ::Nodo*)(new Ñ::Tipo());
    ((Ñ::Tipo*)n3)->tipo = "asdf";
    ((Ñ::Tipo*)n4)->tipo = "prueba";
    ((Ñ::Tipo*)n3)->vector = true;
    ((Ñ::Tipo*)n4)->vector = true;
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Tipo());
    n4 = (Ñ::Nodo*)(new Ñ::Tipo());
    ((Ñ::Tipo*)n3)->tipo = "prueba";
    ((Ñ::Tipo*)n4)->tipo = "prueba";
    ((Ñ::Tipo*)n3)->vector = false;
    ((Ñ::Tipo*)n4)->vector = true;
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::OpSumaResta());
    n4 = (Ñ::Nodo*)(new Ñ::OpSumaResta());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::OpSumaResta());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::OpSumaResta());
    n4 = (Ñ::Nodo*)(new Ñ::OpSumaResta());
    ((Ñ::OpSumaResta*)n3)->operación = "prueba";
    ((Ñ::OpSumaResta*)n4)->operación = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::OpSumaResta());
    n4 = (Ñ::Nodo*)(new Ñ::OpSumaResta());
    ((Ñ::OpSumaResta*)n3)->operación = "asdf";
    ((Ñ::OpSumaResta*)n4)->operación = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::OpMultiplicaciónDivisión());
    n4 = (Ñ::Nodo*)(new Ñ::OpMultiplicaciónDivisión());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::OpMultiplicaciónDivisión());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::OpMultiplicaciónDivisión());
    n4 = (Ñ::Nodo*)(new Ñ::OpMultiplicaciónDivisión());
    ((Ñ::OpMultiplicaciónDivisión*)n3)->operación = "prueba";
    ((Ñ::OpMultiplicaciónDivisión*)n4)->operación = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::OpMultiplicaciónDivisión());
    n4 = (Ñ::Nodo*)(new Ñ::OpMultiplicaciónDivisión());
    ((Ñ::OpMultiplicaciónDivisión*)n3)->operación = "asdf";
    ((Ñ::OpMultiplicaciónDivisión*)n4)->operación = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Factor());
    n4 = (Ñ::Nodo*)(new Ñ::Factor());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Factor());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Factor());
    n4 = (Ñ::Nodo*)(new Ñ::Factor());
    ((Ñ::Factor*)n3)->factor = "prueba";
    ((Ñ::Factor*)n4)->factor = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Factor());
    n4 = (Ñ::Nodo*)(new Ñ::Factor());
    ((Ñ::Factor*)n3)->factor = "asdf";
    ((Ñ::Factor*)n4)->factor = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    n4 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    n4 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    ((Ñ::DeclaraVariable*)n3)->variable = "prueba";
    ((Ñ::DeclaraVariable*)n4)->variable = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    n4 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    ((Ñ::DeclaraVariable*)n3)->variable = "asdf";
    ((Ñ::DeclaraVariable*)n4)->variable = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Asigna());
    n4 = (Ñ::Nodo*)(new Ñ::Asigna());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Asigna());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Asigna());
    n4 = (Ñ::Nodo*)(new Ñ::Asigna());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Argumento());
    n4 = (Ñ::Nodo*)(new Ñ::Argumento());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Argumento());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Argumento());
    n4 = (Ñ::Nodo*)(new Ñ::Argumento());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Argumentos());
    n4 = (Ñ::Nodo*)(new Ñ::Argumentos());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Argumentos());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Argumentos());
    n4 = (Ñ::Nodo*)(new Ñ::Argumentos());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    n4 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    n4 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    ((Ñ::LlamaFunción*)n3)->función = "prueba";
    ((Ñ::LlamaFunción*)n4)->función = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    n4 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    ((Ñ::LlamaFunción*)n3)->función = "asdf";
    ((Ñ::LlamaFunción*)n4)->función = "prueba";
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Expresión());
    n4 = (Ñ::Nodo*)(new Ñ::Expresión());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Expresión());
    n4 = new Ñ::Nodo();
    n1->ramas.push_back(n3);
    n2->ramas.push_back(n4);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;

    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n3 = (Ñ::Nodo*)(new Ñ::Expresión());
    n4 = (Ñ::Nodo*)(new Ñ::Expresión());
    n1->ramas.push_back(n3);
    EXPECT_FALSE(Ñ::sonÁrbolesDuplicados(n1, n2));
    n2->ramas.push_back(n4);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, n2));
    delete n4, n3, n2, n1;
}

TEST(PruebasNodo, duplicaArbol)
{
    Ñ::Nodo* n1;
    Ñ::Nodo* n2;
    Ñ::Nodo* n3;
    Ñ::Nodo* r;

    n1 = new Ñ::Nodo();
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n1;
    
    n1 = new Ñ::Nodo();
    n2 = new Ñ::Nodo();
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::Literal());
    ((Ñ::Literal*)n2)->dato = "prueba";
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::Identificador());
    ((Ñ::Identificador*)n2)->id = "prueba";
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::Tipo());
    ((Ñ::Tipo*)n2)->tipo = "prueba";
    ((Ñ::Tipo*)n2)->vector = true;
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::OpSumaResta());
    ((Ñ::OpSumaResta*)n2)->operación = "prueba";
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::OpMultiplicaciónDivisión());
    ((Ñ::OpMultiplicaciónDivisión*)n2)->operación = "prueba";
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::Factor());
    ((Ñ::Factor*)n2)->factor = "prueba";
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::DeclaraVariable());
    ((Ñ::DeclaraVariable*)n2)->variable = "prueba";
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::Asigna());
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::Argumento());
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::Argumentos());
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::LlamaFunción());
    ((Ñ::LlamaFunción*)n2)->función = "prueba";
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
    
    n1 = new Ñ::Nodo();
    n2 = (Ñ::Nodo*)(new Ñ::Expresión());
    n1->ramas.push_back(n2);
    r = Ñ::duplicaÁrbol(n1);
    EXPECT_TRUE(Ñ::sonÁrbolesDuplicados(n1, r));
    delete r, n2, n1;
}