#include <iostream>

#include "apoyo.hpp"
#include "nodo.hpp"
#include "tipo.hpp"

Ñ::Tipo::Tipo() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_TIPO;
}

Ñ::Tipo::~Tipo() {}

void Ñ::Tipo::muestra()
{
	imprimeAjuste();
	std::cout << "(NODO_TIPO) [" + obténNombreDeTipo(tipo) + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

Ñ::Tipo* Ñ::creaTipoBásico(Ñ::CategoríaTipo tipo)
{
	Ñ::Tipo* t = new Ñ::Tipo;
	t->tipo = tipo;
	return t;
}

Ñ::Resultado Ñ::creaFirmaFunción(Ñ::Nodo* nodo)
{
	Ñ::Resultado resultado;
	Ñ::Nodo* tipoRetorno;
	Ñ::Nodo* argumentos;
	Ñ::Nodo* firmaFunción;

    if(nodo == nullptr)
    {
        resultado.error("El nodo es un puntero nulo, esperaba una declaración o una definición de función.");
        return resultado;
    }
	
    if(nodo->categoría == Ñ::CategoríaNodo::NODO_DEFINE_FUNCIÓN)
    {
		if(nodo->ramas.size() != 3)
		{
			resultado.error("El árbol de nodos es incorrecto, la definición de una función debe tener 3 ramas: 'tipo', 'argumentos' y 'bloque'.");
			return resultado;
		}

		tipoRetorno = duplicaÁrbol(nodo->ramas[0]);
        argumentos = duplicaÁrbol(nodo->ramas[1]);
    }
	else if(nodo->categoría == Ñ::CategoríaNodo::NODO_DECLARA_FUNCIÓN)
    {
		if(nodo->ramas.size() != 2)
		{
			resultado.error("El árbol de nodos es incorrecto, la definición de una función debe tener 3 ramas: 'tipo', 'argumentos' y 'bloque'.");
			return resultado;
		}
		
		tipoRetorno = duplicaÁrbol(nodo->ramas[0]);
        argumentos = duplicaÁrbol(nodo->ramas[1]);
    }
	else
	{
        resultado.error("El árbol de nodos es incorrecto, esperaba una declaración o una definición de función.");
        return resultado;
    }
	
	firmaFunción = (Ñ::Nodo*)(new Ñ::Tipo);
	firmaFunción->ramas.push_back(tipoRetorno);
	firmaFunción->ramas.push_back(argumentos);

	resultado.éxito();
	resultado.nodo(firmaFunción);
	return resultado;
}

std::string Ñ::obténNombreDeTipo(Ñ::CategoríaTipo t)
{
	std::string nombre = "";

	if(t == Ñ::CategoríaTipo::TIPO_NADA)
	{
		nombre = "nada";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_BOOLEANO)
	{
		nombre = "booleano";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_NATURAL_8)
	{
		nombre = "nat8";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_NATURAL_16)
	{
		nombre = "nat16";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_NATURAL_32)
	{
		nombre = "nat32";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_NATURAL_64)
	{
		nombre = "nat64";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_ENTERO_8)
	{
		nombre = "ent8";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_ENTERO_16)
	{
		nombre = "ent16";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_ENTERO_32)
	{
		nombre = "ent32";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_ENTERO_64)
	{
		nombre = "ent64";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_PUNTERO)
	{
		nombre = "puntero";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_REAL_32)
	{
		nombre = "real32";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_REAL_64)
	{
		nombre = "real64";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_TEXTO)
	{
		nombre = "txt";
	}
	else if(t == Ñ::CategoríaTipo::TIPO_VECTOR)
	{
		nombre = "[]";
	}

	return nombre;
}

Ñ::CategoríaTipo Ñ::obténTipoDeNombre(std::string nombre)
{
	if(nombre == "puntero")
	{
		return Ñ::CategoríaTipo::TIPO_PUNTERO;
	}
	else if(nombre == "bool")
	{
		return Ñ::CategoríaTipo::TIPO_BOOLEANO;
	}
	else if(nombre == "booleano")
	{
		return Ñ::CategoríaTipo::TIPO_BOOLEANO;
	}
	else if(nombre == "nat8")
	{
		return Ñ::CategoríaTipo::TIPO_NATURAL_8;
	}
	else if(nombre == "nat16")
	{
		return Ñ::CategoríaTipo::TIPO_NATURAL_16;
	}
	else if(nombre == "nat32")
	{
		return Ñ::CategoríaTipo::TIPO_NATURAL_32;
	}
	else if(nombre == "nat64")
	{
		return Ñ::CategoríaTipo::TIPO_NATURAL_64;
	}
	else if(nombre == "natural" || nombre == "nat")
	{
		return Ñ::CategoríaTipo::TIPO_NATURAL_64;
	}
	else if(nombre == "ent8")
	{
		return Ñ::CategoríaTipo::TIPO_ENTERO_8;
	}
	else if(nombre == "ent16")
	{
		return Ñ::CategoríaTipo::TIPO_ENTERO_16;
	}
	else if(nombre == "ent32")
	{
		return Ñ::CategoríaTipo::TIPO_ENTERO_32;
	}
	else if(nombre == "ent64")
	{
		return Ñ::CategoríaTipo::TIPO_ENTERO_64;
	}
	else if(nombre == "entero" || nombre == "ent")
	{
		return Ñ::CategoríaTipo::TIPO_ENTERO_64;
	}
	else if(nombre == "rea32")
	{
		return Ñ::CategoríaTipo::TIPO_REAL_32;
	}
	else if(nombre == "rea64")
	{
		return Ñ::CategoríaTipo::TIPO_REAL_64;
	}
	else if(nombre == "real")
	{
		return Ñ::CategoríaTipo::TIPO_REAL_64;
	}
	else if(nombre == "txt")
	{
		return Ñ::CategoríaTipo::TIPO_TEXTO;
	}
	else if(nombre == "[]")
	{
		return Ñ::CategoríaTipo::TIPO_VECTOR;
	}
	else // nombre == "nada" y resto de combinaciones
	{
		return Ñ::CategoríaTipo::TIPO_NADA;
	}
}

Ñ::CategoríaTipo Ñ::obténMínimoNaturalVálido(uint64_t n)
{
	uint64_t probando;

	probando = Ñ::potencia(2, 8);
	if(probando >= n)
	{
		return Ñ::CategoríaTipo::TIPO_NATURAL_8;
	}

	probando = Ñ::potencia(2, 16);
	if(probando >= n)
	{
		return Ñ::CategoríaTipo::TIPO_NATURAL_16;
	}

	probando = Ñ::potencia(2, 32);
	if(probando >= n)
	{
		return Ñ::CategoríaTipo::TIPO_NATURAL_32;
	}

	return Ñ::CategoríaTipo::TIPO_NATURAL_64;
}

Ñ::CategoríaTipo Ñ::obténMínimoEnteroVálido(int64_t e)
{
	int64_t máx;
	int64_t mín;

	máx = Ñ::potencia(2, 7) - 1;
	mín = - Ñ::potencia(2, 7);
	if(máx >= e && mín <= e)
	{
		return Ñ::CategoríaTipo::TIPO_ENTERO_8;
	}

	máx = Ñ::potencia(2, 15) - 1;
	mín = - Ñ::potencia(2, 15);
	if(máx >= e && mín <= e)
	{
		return Ñ::CategoríaTipo::TIPO_ENTERO_16;
	}

	máx = Ñ::potencia(2, 31) - 1;
	mín = - Ñ::potencia(2, 31);
	if(máx >= e && mín <= e)
	{
		return Ñ::CategoríaTipo::TIPO_ENTERO_32;
	}

	return Ñ::CategoríaTipo::TIPO_ENTERO_64;
}

bool Ñ::tiposAsignables(Ñ::CategoríaTipo lia, Ñ::CategoríaTipo lda)
{
	switch (lia)
	{
	case TIPO_PUNTERO:
		switch (lda)
		{
		case TIPO_ENTERO_64:
		case TIPO_PUNTERO:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_TEXTO:
		switch (lda)
		{
		case TIPO_TEXTO:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_BOOLEANO:
		switch (lda)
		{
		case TIPO_BOOLEANO:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_NATURAL_8:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_NATURAL_16:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_NATURAL_32:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
		case TIPO_NATURAL_32:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_NATURAL_64:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
		case TIPO_NATURAL_32:
		case TIPO_NATURAL_64:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_ENTERO_8:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_ENTERO_8:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_ENTERO_16:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
		case TIPO_NATURAL_8:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_ENTERO_32:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
		case TIPO_ENTERO_32:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_ENTERO_64:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
		case TIPO_ENTERO_32:
		case TIPO_ENTERO_64:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
		case TIPO_NATURAL_32:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_REAL_32:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
		case TIPO_ENTERO_32:
		case TIPO_ENTERO_64:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
		case TIPO_NATURAL_32:
		case TIPO_NATURAL_64:
		case TIPO_REAL_32:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	case TIPO_REAL_64:
		switch (lda)
		{
		case TIPO_BOOLEANO:
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
		case TIPO_ENTERO_32:
		case TIPO_ENTERO_64:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
		case TIPO_NATURAL_32:
		case TIPO_NATURAL_64:
		case TIPO_REAL_32:
		case TIPO_REAL_64:
			return true;
			break;
		
		default:
			return false;
			break;
		}
		break;
	
	default:
		return false;
		break;
	}
}