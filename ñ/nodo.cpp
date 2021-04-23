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

Ñ::OpSumaResta::OpSumaResta() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_OP_SUMA_RESTA;
}

Ñ::OpSumaResta::OpSumaResta(const Ñ::OpSumaResta& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_OP_SUMA_RESTA;
}

Ñ::OpSumaResta::~OpSumaResta() {}

void Ñ::OpSumaResta::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_OP_SUMA_RESTA) [" + operación + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos, los términos
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::OpMultiplicaciónDivisión::OpMultiplicaciónDivisión() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_OP_MULTIPLICACIÓN_DIVISIÓN;
}

Ñ::OpMultiplicaciónDivisión::OpMultiplicaciónDivisión(const Ñ::OpMultiplicaciónDivisión& nodo) : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_OP_MULTIPLICACIÓN_DIVISIÓN;
}

Ñ::OpMultiplicaciónDivisión::~OpMultiplicaciónDivisión() {}

void Ñ::OpMultiplicaciónDivisión::muestra()
{
	imprimeAjuste();
	std::cout << u8"(NODO_OP_MULTIPLICACIÓN_DIVISIÓN) [" + operación + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	// Queda imprimir los hijos, los factores
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
	std::cout << "(NODO_FACTOR) [" + factor + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
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
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_FACTOR)
	{
		((Ñ::Factor*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_MULTIPLICACIÓN_DIVISIÓN)
	{
		((Ñ::OpMultiplicaciónDivisión*)nodo)->muestra();
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_SUMA_RESTA)
	{
		((Ñ::OpSumaResta*)nodo)->muestra();
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

	ajuste--;
}


Ñ::Nodo* Ñ::duplicaNodo(Ñ::Nodo* nodo)
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
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_FACTOR)
	{
		Ñ::Factor* n = (Ñ::Factor*)nodo;
		Ñ::Factor* f = new Ñ::Factor();
		f->factor = n->factor;

		duplicado = (Ñ::Nodo*)f;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_MULTIPLICACIÓN_DIVISIÓN)
	{
		Ñ::OpMultiplicaciónDivisión* n = (Ñ::OpMultiplicaciónDivisión*)nodo;
		Ñ::OpMultiplicaciónDivisión* o = new Ñ::OpMultiplicaciónDivisión();
		o->operación = n->operación;

		duplicado = (Ñ::Nodo*)o;
	}
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_OP_SUMA_RESTA)
	{
		Ñ::OpSumaResta* n = (Ñ::OpSumaResta*)nodo;
		Ñ::OpSumaResta* o = new Ñ::OpSumaResta();
		o->operación = n->operación;

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
	else
	{
		std::cout << "Error, no he reconocido el nodo. Devuelvo nullptr." << std::endl;
		return nullptr;
	}

	// Ahora duplico las ramas del nodo
	for(auto r : nodo->ramas)
	{
		Ñ::Nodo* n = duplicaNodo(r);
		if(n != nullptr)
		{
			duplicado->ramas.push_back(n);
		}
	}

	return duplicado;
}