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