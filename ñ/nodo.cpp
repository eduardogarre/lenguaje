#include <iostream>

#include "nodo.hpp"

uint32_t ajuste = -1;

void imprimeAjuste()
{
	for(uint32_t i = 0; i < ajuste; i++)
	{
		std::cout << "  ";
	}
}

Ñ::Nodo::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_VACÍO;
}

Ñ::Nodo::Nodo(const Ñ::Nodo& nodo)
{
	categoría = Ñ::CategoríaNodo::NODO_VACÍO;
}

Ñ::Nodo::~Nodo()
{
	for(uint32_t i = 0; i < ramas.size(); i++)
	{
		delete ramas[i];
	}
}

void Ñ::Nodo::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_VACÍO) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Literal::Literal() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_LITERAL;
}

Ñ::Literal::Literal(const Ñ::Literal& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_LITERAL;
}

Ñ::Literal::~Literal() {}

void Ñ::Literal::muestra()
{
	imprimeAjuste();
	std::cout << "(NODO_LITERAL) [" + dato + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Tipo::Tipo() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_TIPO;
}

Ñ::Tipo::Tipo(const Ñ::Tipo& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_TIPO;
}

Ñ::Tipo::~Tipo() {}

void Ñ::Tipo::muestra()
{
	if(vector)
	{
		imprimeAjuste();
		std::cout << "(NODO_TIPO) [" + tipo + "[]] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
		for(auto rama : ramas)
		{
			muestraNodos(rama);
		}
	}
	else
	{
		imprimeAjuste();
		std::cout << "(NODO_TIPO) [" + tipo + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
		for(auto rama : ramas)
		{
			muestraNodos(rama);
		}
	}
}

Ñ::Identificador::Identificador() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_IDENTIFICADOR;
}

Ñ::Identificador::Identificador(const Ñ::Identificador& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_IDENTIFICADOR;
}

Ñ::Identificador::~Identificador() {}

void Ñ::Identificador::muestra()
{
	imprimeAjuste();
	std::cout << "(NODO_IDENTIFICADOR) [" + id + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::LadoIzquierdoAsignación::LadoIzquierdoAsignación() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_LADO_IZQUIERDO_ASIGNACIÓN;
}

Ñ::LadoIzquierdoAsignación::LadoIzquierdoAsignación(const Ñ::LadoIzquierdoAsignación& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_LADO_IZQUIERDO_ASIGNACIÓN;
}

Ñ::LadoIzquierdoAsignación::~LadoIzquierdoAsignación() {}

void Ñ::LadoIzquierdoAsignación::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_LADO_IZQUIERDO_ASIGNACIÓN) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::LadoDerechoAsignación::LadoDerechoAsignación() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_LADO_DERECHO_ASIGNACIÓN;
}

Ñ::LadoDerechoAsignación::LadoDerechoAsignación(const Ñ::LadoDerechoAsignación& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_LADO_DERECHO_ASIGNACIÓN;
}

Ñ::LadoDerechoAsignación::~LadoDerechoAsignación() {}

void Ñ::LadoDerechoAsignación::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_LADO_DERECHO_ASIGNACIÓN) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::OperaciónBinaria::OperaciónBinaria() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_OP_BINARIA;
}

Ñ::OperaciónBinaria::OperaciónBinaria(const Ñ::OperaciónBinaria& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_OP_BINARIA;
}

Ñ::OperaciónBinaria::~OperaciónBinaria() {}

void Ñ::OperaciónBinaria::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_OP_BINARIA) [" + operación + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Igualdad::Igualdad() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_IGUALDAD;
}

Ñ::Igualdad::Igualdad(const Ñ::Igualdad& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_IGUALDAD;
}

Ñ::Igualdad::~Igualdad() {}

void Ñ::Igualdad::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_IGUALDAD) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Comparación::Comparación() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_COMPARACIÓN;
}

Ñ::Comparación::Comparación(const Ñ::Comparación& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_COMPARACIÓN;
}

Ñ::Comparación::~Comparación() {}

void Ñ::Comparación::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_COMPARACIÓN) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Término::Término() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_TÉRMINO;
}

Ñ::Término::Término(const Ñ::Término& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_TÉRMINO;
}

Ñ::Término::~Término() {}

void Ñ::Término::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_TÉRMINO) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos, los términos
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Factor::Factor() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_FACTOR;
}

Ñ::Factor::Factor(const Ñ::Factor& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_FACTOR;
}

Ñ::Factor::~Factor() {}

void Ñ::Factor::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_FACTOR) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos, los factores
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::OperaciónUnaria::OperaciónUnaria() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_OP_UNARIA;
}

Ñ::OperaciónUnaria::OperaciónUnaria(const Ñ::OperaciónUnaria& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_OP_UNARIA;
}

Ñ::OperaciónUnaria::~OperaciónUnaria() {}

void Ñ::OperaciónUnaria::muestra()
{
	imprimeAjuste();
	std::cout << "(NODO_OP_UNARIA) [" + operación + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Primario::Primario() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_PRIMARIO;
}

Ñ::Primario::Primario(const Ñ::Primario& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_PRIMARIO;
}

Ñ::Primario::~Primario() {}

void Ñ::Primario::muestra()
{
	imprimeAjuste();
	std::cout << "(NODO_PRIMARIO) [" + primario + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::DeclaraVariable::DeclaraVariable() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE;
}

Ñ::DeclaraVariable::DeclaraVariable(const Ñ::DeclaraVariable& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE;
}

Ñ::DeclaraVariable::~DeclaraVariable() {}

void Ñ::DeclaraVariable::muestra()
{
	imprimeAjuste();
	std::cout << "(NODO_DECLARA_VARIABLE) [" + variable + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir el hijo, el tipo
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Asigna::Asigna() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_ASIGNA;
}

Ñ::Asigna::Asigna(const Ñ::Asigna& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_ASIGNA;
}

Ñ::Asigna::~Asigna() {}

void Ñ::Asigna::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_ASIGNA) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Argumentos::Argumentos() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_ARGUMENTOS;
}

Ñ::Argumentos::Argumentos(const Ñ::Argumentos& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_ARGUMENTOS;
}

Ñ::Argumentos::~Argumentos() {}

void Ñ::Argumentos::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_ARGUMENTOS) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Argumento::Argumento() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_ARGUMENTO;
}

Ñ::Argumento::Argumento(const Ñ::Argumento& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_ARGUMENTO;
}

Ñ::Argumento::~Argumento() {}

void Ñ::Argumento::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_ARGUMENTO) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::LlamaFunción::LlamaFunción() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN;
}

Ñ::LlamaFunción::LlamaFunción(const Ñ::LlamaFunción& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN;
}

Ñ::LlamaFunción::~LlamaFunción() {}

void Ñ::LlamaFunción::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_LLAMA_FUNCIÓN) [" + función + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Expresión::Expresión() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_EXPRESIÓN;
}

Ñ::Expresión::Expresión(const Ñ::Expresión& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_EXPRESIÓN;
}

Ñ::Expresión::~Expresión() {}

void Ñ::Expresión::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_EXPRESIÓN) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Bloque::Bloque() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_BLOQUE;
}

Ñ::Bloque::Bloque(const Ñ::Bloque& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_BLOQUE;
}

Ñ::Bloque::~Bloque() {}

void Ñ::Bloque::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_BLOQUE) - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::DefineFunción::DefineFunción() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN;
}

Ñ::DefineFunción::DefineFunción(const Ñ::DefineFunción& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN;
}

Ñ::DefineFunción::~DefineFunción() {}

void Ñ::DefineFunción::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_DEFINE_FUNCIÓN) [" + función + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Módulo::Módulo() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_MÓDULO;
}

Ñ::Módulo::Módulo(const Ñ::Módulo& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_MÓDULO;
}

Ñ::Módulo::~Módulo() {}

void Ñ::Módulo::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_MÓDULO) [" + módulo + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

void Ñ::borraNodos(Ñ::Nodo* nodos)
{
	for(auto rama : nodos->ramas)
	{
		Ñ::borraNodos(rama);
	}

	delete nodos;
}

void Ñ::muestraNodos(Ñ::Nodo* nodo)
{
	if(nodo == nullptr)
	{
		return;
	}
	
	ajuste++;

	if(nodo->categoría == Ñ::CategoríaNodo::NODO_VACÍO)
	{
		((Ñ::Nodo*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
	{
		((Ñ::Literal*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_TIPO)
	{
		((Ñ::Tipo*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
	{
		((Ñ::Identificador*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_UNARIA)
	{
		((Ñ::OperaciónUnaria*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_BINARIA)
	{
		((Ñ::OperaciónBinaria*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_PRIMARIO)
	{
		((Ñ::Primario*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_TÉRMINO)
	{
		((Ñ::Término*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_FACTOR)
	{
		((Ñ::Factor*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_COMPARACIÓN)
	{
		((Ñ::Comparación*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_IGUALDAD)
	{
		((Ñ::Igualdad*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LADO_DERECHO_ASIGNACIÓN)
	{
		((Ñ::LadoDerechoAsignación*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LADO_IZQUIERDO_ASIGNACIÓN)
	{
		((Ñ::LadoIzquierdoAsignación*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
	{
		((Ñ::Asigna*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
	{
		((Ñ::DeclaraVariable*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTO)
	{
		((Ñ::Argumento*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
	{
		((Ñ::Argumentos*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
	{
		((Ñ::LlamaFunción*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
	{
		((Ñ::Expresión*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
	{
		((Ñ::Bloque*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
	{
		((Ñ::DefineFunción*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
	{
		((Ñ::Módulo*)nodo)->muestra();
	}

	ajuste--;
}

bool Ñ::sonÁrbolesDuplicados(Ñ::Nodo* nodo1, Ñ::Nodo* nodo2)
{
	if(nodo1 == nodo2)
	{
		return false;
	}
	if(nodo1 == nullptr || nodo1 == NULL || nodo2 == nullptr || nodo2 == NULL)
	{
		return false;
	}
	else if(nodo1->ramas.size() != nodo2->ramas.size())
	{
		return false;
	}
	else if(nodo1->categoría == nodo2->categoría)
	{
		for(int i = 0; i < nodo1->ramas.size(); i++)
		{
			bool resultado = Ñ::sonÁrbolesDuplicados(nodo1->ramas[i], nodo2->ramas[i]);
			if(!resultado)
			{
				return false;
			}
		}
	
		Ñ::Literal* l1;
		Ñ::Literal* l2;
		Ñ::Identificador* id1;
		Ñ::Identificador* id2;
		Ñ::Tipo* t1;
		Ñ::Tipo* t2;
		Ñ::LadoIzquierdoAsignación* lia1;
		Ñ::LadoIzquierdoAsignación* lia2;
		Ñ::LadoDerechoAsignación* lda1;
		Ñ::LadoDerechoAsignación* lda2;
		Ñ::Igualdad* ig1;
		Ñ::Igualdad* ig2;
		Ñ::Comparación* cm1;
		Ñ::Comparación* cm2;
		Ñ::Término* tr1;
		Ñ::Término* tr2;
		Ñ::Factor* fc1;
		Ñ::Factor* fc2;
		Ñ::OperaciónBinaria* b1;
		Ñ::OperaciónBinaria* b2;
		Ñ::OperaciónUnaria* u1;
		Ñ::OperaciónUnaria* u2;
		Ñ::Primario* pr1;
		Ñ::Primario* pr2;
		Ñ::DeclaraVariable* dv1;
		Ñ::DeclaraVariable* dv2;
		Ñ::LlamaFunción* lfn1;
		Ñ::LlamaFunción* lfn2;
		Ñ::DefineFunción* dfn1;
		Ñ::DefineFunción* dfn2;
		Ñ::Módulo* m1;
		Ñ::Módulo* m2;

		switch (nodo1->categoría)
		{
		case Ñ::CategoríaNodo::NODO_VACÍO:
			return true;
			break;

		case Ñ::CategoríaNodo::NODO_LITERAL:
			l1 = (Ñ::Literal*)nodo1;
			l2 = (Ñ::Literal*)nodo2;
			if(l1->dato == l2->dato)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		
		case Ñ::CategoríaNodo::NODO_IDENTIFICADOR:
			id1 = (Ñ::Identificador*)nodo1;
			id2 = (Ñ::Identificador*)nodo2;
			if(id1->id == id2->id)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		
		case Ñ::CategoríaNodo::NODO_TIPO:
			t1 = (Ñ::Tipo*)nodo1;
			t2 = (Ñ::Tipo*)nodo2;
			if(t1->tipo == t2->tipo && t1->vector == t2->vector)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;

		case Ñ::CategoríaNodo::NODO_LADO_IZQUIERDO_ASIGNACIÓN:
			return true;
			break;

		case Ñ::CategoríaNodo::NODO_LADO_DERECHO_ASIGNACIÓN:
			return true;
			break;

		case Ñ::CategoríaNodo::NODO_IGUALDAD:
			return true;
			break;

		case Ñ::CategoríaNodo::NODO_COMPARACIÓN:
			return true;
			break;
		
		case Ñ::CategoríaNodo::NODO_TÉRMINO:
			return true;
			break;
		
		case Ñ::CategoríaNodo::NODO_FACTOR:
			return true;
			break;

		case Ñ::CategoríaNodo::NODO_OP_BINARIA:
			b1 = (Ñ::OperaciónBinaria*)nodo1;
			b2 = (Ñ::OperaciónBinaria*)nodo2;
			if(b1->operación == b2->operación)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		
		case Ñ::CategoríaNodo::NODO_OP_UNARIA:
			u1 = (Ñ::OperaciónUnaria*)nodo1;
			u2 = (Ñ::OperaciónUnaria*)nodo2;
			if(u1->operación == u2->operación)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		
		case Ñ::CategoríaNodo::NODO_PRIMARIO:
			pr1 = (Ñ::Primario*)nodo1;
			pr2 = (Ñ::Primario*)nodo2;
			if(pr1->primario == pr2->primario)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		
		case Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE:
			dv1 = (Ñ::DeclaraVariable*)nodo1;
			dv2 = (Ñ::DeclaraVariable*)nodo2;
			if(dv1->variable == dv2->variable)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		
		case Ñ::CategoríaNodo::NODO_ASIGNA:
			return true;
			break;
		
		case Ñ::CategoríaNodo::NODO_ARGUMENTO:
			return true;
			break;
		
		case Ñ::CategoríaNodo::NODO_ARGUMENTOS:
			return true;
			break;
		
		case Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN:
			lfn1 = (Ñ::LlamaFunción*)nodo1;
			lfn2 = (Ñ::LlamaFunción*)nodo2;
			if(lfn1->función == lfn2->función)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		
		case Ñ::CategoríaNodo::NODO_EXPRESIÓN:
			return true;
			break;
		
		case Ñ::CategoríaNodo::NODO_BLOQUE:
			return true;
			break;
		
		case Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN:
			dfn1 = (Ñ::DefineFunción*)nodo1;
			dfn2 = (Ñ::DefineFunción*)nodo2;
			if(dfn1->función == dfn2->función)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		
		case Ñ::CategoríaNodo::NODO_MÓDULO:
			m1 = (Ñ::Módulo*)nodo1;
			m2 = (Ñ::Módulo*)nodo2;
			if(m1->módulo == m2->módulo)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		
		default:
			return false;
			break;
		}
	}
	else
	{
		return false;
	}
}

Ñ::Nodo* Ñ::duplicaÁrbol(Ñ::Nodo* nodo)
{
	if(nodo == nullptr)
	{
		return nullptr;
	}

	Ñ::Nodo* duplicado = nullptr;

	// Creo los nodos
	if(nodo->categoría == Ñ::CategoríaNodo::NODO_VACÍO)
	{
		duplicado = new Ñ::Nodo();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
	{
		Ñ::Literal* n = (Ñ::Literal*)nodo;
		Ñ::Literal* l = new Ñ::Literal();
		l->dato = n->dato;

		duplicado = (Ñ::Nodo*)l;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_TIPO)
	{
		Ñ::Tipo* n = (Ñ::Tipo*)nodo;
		Ñ::Tipo* t = new Ñ::Tipo();
		t->tipo = n->tipo;
		t->vector = n->vector;

		duplicado = (Ñ::Nodo*)t;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_IDENTIFICADOR)
	{
		Ñ::Identificador* n = (Ñ::Identificador*)nodo;
		Ñ::Identificador* i = new Ñ::Identificador();
		i->id = n->id;

		duplicado = (Ñ::Nodo*)i;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_BINARIA)
	{
		Ñ::OperaciónBinaria* n = (Ñ::OperaciónBinaria*)nodo;
		Ñ::OperaciónBinaria* o = new Ñ::OperaciónBinaria();
		o->operación = n->operación;

		duplicado = (Ñ::Nodo*)o;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_UNARIA)
	{
		Ñ::OperaciónUnaria* n = (Ñ::OperaciónUnaria*)nodo;
		Ñ::OperaciónUnaria* o = new Ñ::OperaciónUnaria();
		o->operación = n->operación;

		duplicado = (Ñ::Nodo*)o;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_PRIMARIO)
	{
		Ñ::Primario* n = (Ñ::Primario*)nodo;
		Ñ::Primario* p = new Ñ::Primario();
		p->primario = n->primario;

		duplicado = (Ñ::Nodo*)p;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_FACTOR)
	{
		Ñ::Factor* n = (Ñ::Factor*)nodo;
		Ñ::Factor* o = new Ñ::Factor();

		duplicado = (Ñ::Nodo*)o;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_TÉRMINO)
	{
		Ñ::Término* n = (Ñ::Término*)nodo;
		Ñ::Término* o = new Ñ::Término();

		duplicado = (Ñ::Nodo*)o;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_COMPARACIÓN)
	{
		Ñ::Comparación* n = (Ñ::Comparación*)nodo;
		Ñ::Comparación* o = new Ñ::Comparación();

		duplicado = (Ñ::Nodo*)o;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_IGUALDAD)
	{
		Ñ::Igualdad* n = (Ñ::Igualdad*)nodo;
		Ñ::Igualdad* o = new Ñ::Igualdad();

		duplicado = (Ñ::Nodo*)o;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LADO_DERECHO_ASIGNACIÓN)
	{
		Ñ::LadoDerechoAsignación* n = (Ñ::LadoDerechoAsignación*)nodo;
		Ñ::LadoDerechoAsignación* o = new Ñ::LadoDerechoAsignación();

		duplicado = (Ñ::Nodo*)o;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LADO_IZQUIERDO_ASIGNACIÓN)
	{
		Ñ::LadoIzquierdoAsignación* n = (Ñ::LadoIzquierdoAsignación*)nodo;
		Ñ::LadoIzquierdoAsignación* o = new Ñ::LadoIzquierdoAsignación();

		duplicado = (Ñ::Nodo*)o;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ASIGNA)
	{
		Ñ::Asigna* a = new Ñ::Asigna();
		duplicado = (Ñ::Nodo*)a;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_VARIABLE)
	{
		Ñ::DeclaraVariable* n = (Ñ::DeclaraVariable*)nodo;
		Ñ::DeclaraVariable* d = new Ñ::DeclaraVariable();
		d->variable = n->variable;

		duplicado = (Ñ::Nodo*)d;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTO)
	{
		Ñ::Argumento* a = new Ñ::Argumento();
		duplicado = (Ñ::Nodo*)a;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
	{
		Ñ::Argumentos* a = new Ñ::Argumentos();
		duplicado = (Ñ::Nodo*)a;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_LLAMA_FUNCIÓN)
	{
		Ñ::LlamaFunción* n = (Ñ::LlamaFunción*)nodo;
		Ñ::LlamaFunción* f = new Ñ::LlamaFunción();
		f->función = n->función;

		duplicado = (Ñ::Nodo*)f;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_EXPRESIÓN)
	{
		Ñ::Expresión* e = new Ñ::Expresión();
		duplicado = (Ñ::Nodo*)e;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_BLOQUE)
	{
		Ñ::Bloque* b = new Ñ::Bloque();
		duplicado = (Ñ::Nodo*)b;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
	{
		Ñ::DefineFunción* n = (Ñ::DefineFunción*)nodo;
		Ñ::DefineFunción* f = new Ñ::DefineFunción();
		f->función = n->función;

		duplicado = (Ñ::Nodo*)f;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_MÓDULO)
	{
		Ñ::Módulo* n = (Ñ::Módulo*)nodo;
		Ñ::Módulo* m = new Ñ::Módulo();
		m->módulo = n->módulo;

		duplicado = (Ñ::Nodo*)m;
	}
	else
	{
		std::cout << "Error, no he reconocido el nodo. Devuelvo nullptr." << std::endl;
		return nullptr;
	}

	// Ahora duplico las ramas del nodo
	for(auto r : nodo->ramas)
	{
		Ñ::Nodo* n = duplicaÁrbol(r);
		if(n != nullptr)
		{
			duplicado->ramas.push_back(n);
		}
	}

	return duplicado;
}