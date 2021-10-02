#include <iostream>

#include "apoyo.hpp"
#include "nodo.hpp"
#include "tipo.hpp"

bool Ñ::esNatural(Ñ::Tipo* tipo)
{
	if(	   tipo->tipo == Ñ::CategoríaTipo::TIPO_NATURAL_8
		|| tipo->tipo == Ñ::CategoríaTipo::TIPO_NATURAL_16
		|| tipo->tipo == Ñ::CategoríaTipo::TIPO_NATURAL_32
		|| tipo->tipo == Ñ::CategoríaTipo::TIPO_NATURAL_64)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Ñ::esEntero(Ñ::Tipo* tipo)
{
	if(	   tipo->tipo == Ñ::CategoríaTipo::TIPO_ENTERO_8
		|| tipo->tipo == Ñ::CategoríaTipo::TIPO_ENTERO_16
		|| tipo->tipo == Ñ::CategoríaTipo::TIPO_ENTERO_32
		|| tipo->tipo == Ñ::CategoríaTipo::TIPO_ENTERO_64)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Ñ::esReal(Ñ::Tipo* tipo)
{
	if(	   tipo->tipo == Ñ::CategoríaTipo::TIPO_REAL_32
		|| tipo->tipo == Ñ::CategoríaTipo::TIPO_REAL_64)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Ñ::esVector(Ñ::Tipo* tipo)
{
	return tipo->tipo == Ñ::CategoríaTipo::TIPO_VECTOR;
}

bool Ñ::esBooleano(Ñ::Tipo* tipo)
{
	if( tipo->tipo == Ñ::CategoríaTipo::TIPO_BOOLEANO )
	{
		return true;
	}
	else
	{
		return false;
	}
}

Ñ::Tipo::Tipo() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_TIPO;
}

Ñ::Tipo::~Tipo() {}

void Ñ::Tipo::muestra(TablaSímbolos* tablaSímbolos)
{
	imprimeAjuste();
	std::cout << "(NODO_TIPO) [" + obténNombreDeTipo(this) + "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}

uint64_t Ñ::Tipo::_ramas()
{
	return ((Ñ::Nodo*)this)->ramas.size();
}

uint64_t Ñ::Tipo::tamaño()
{
	return _tamaño;
}

void Ñ::Tipo::tamaño(uint64_t nuevotamaño)
{
	_tamaño = nuevotamaño;
}

Ñ::Tipo* Ñ::Tipo::subtipo()
{
	if(_ramas() == 1)
	{
		return (Ñ::Tipo*)((Ñ::Nodo*)this)->ramas[0];
	}
	else
	{
		return nullptr;
	}
}

Ñ::Tipo* Ñ::obténTipoMínimoComún(Ñ::Tipo* t1, Ñ::Tipo* t2)
{
	Ñ::Tipo* tmc = new Ñ::Tipo;

	switch (t1->tipo)
	{
	case TIPO_NADA:
		return tmc;
		break;
	
	case TIPO_BOOLEANO:
		switch (t2->tipo)
		{
		case TIPO_BOOLEANO:
			tmc->tipo = TIPO_BOOLEANO;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_NATURAL_8:
		switch (t2->tipo)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
			tmc->tipo = TIPO_NATURAL_8;
			return tmc;
			break;
		
		case TIPO_NATURAL_16:
			tmc->tipo = TIPO_NATURAL_16;
			return tmc;
			break;
		
		case TIPO_NATURAL_32:
			tmc->tipo = TIPO_NATURAL_32;
			return tmc;
			break;
		
		case TIPO_NATURAL_64:
			tmc->tipo = TIPO_NATURAL_64;
			return tmc;
			break;
		
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
			tmc->tipo = TIPO_ENTERO_16;
			return tmc;
			break;
		
		case TIPO_ENTERO_32:
			tmc->tipo = TIPO_ENTERO_32;
			return tmc;
			break;
		
		case TIPO_ENTERO_64:
			tmc->tipo = TIPO_ENTERO_64;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_NATURAL_16:
		switch (t2->tipo)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
			tmc->tipo = TIPO_NATURAL_16;
			return tmc;
			break;
		
		case TIPO_NATURAL_32:
			tmc->tipo = TIPO_NATURAL_32;
			return tmc;
			break;
		
		case TIPO_NATURAL_64:
			tmc->tipo = TIPO_NATURAL_64;
			return tmc;
			break;
		
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
		case TIPO_ENTERO_32:
			tmc->tipo = TIPO_ENTERO_32;
			return tmc;
			break;
		
		case TIPO_ENTERO_64:
			tmc->tipo = TIPO_ENTERO_64;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_NATURAL_32:
		switch (t2->tipo)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
		case TIPO_NATURAL_32:
			tmc->tipo = TIPO_NATURAL_32;
			return tmc;
			break;
		
		case TIPO_NATURAL_64:
			tmc->tipo = TIPO_NATURAL_64;
			return tmc;
			break;
		
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
		case TIPO_ENTERO_32:
		case TIPO_ENTERO_64:
			tmc->tipo = TIPO_ENTERO_64;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_NATURAL_64:
		switch (t2->tipo)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
		case TIPO_NATURAL_32:
		case TIPO_NATURAL_64:
			tmc->tipo = TIPO_NATURAL_64;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_ENTERO_8:
		switch (t2->tipo)
		{
		case TIPO_BOOLEANO:
		case TIPO_ENTERO_8:
			tmc->tipo = TIPO_ENTERO_8;
			return tmc;
			break;
		
		case TIPO_NATURAL_8:
		case TIPO_ENTERO_16:
			tmc->tipo = TIPO_ENTERO_16;
			return tmc;
			break;
		
		case TIPO_NATURAL_16:
		case TIPO_ENTERO_32:
			tmc->tipo = TIPO_ENTERO_32;
			return tmc;
			break;
		
		case TIPO_NATURAL_32:
		case TIPO_ENTERO_64:
			tmc->tipo = TIPO_ENTERO_64;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_ENTERO_16:
		switch (t2->tipo)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
			tmc->tipo = TIPO_ENTERO_16;
			return tmc;
			break;
		
		case TIPO_NATURAL_16:
		case TIPO_ENTERO_32:
			tmc->tipo = TIPO_ENTERO_32;
			return tmc;
			break;
		
		case TIPO_NATURAL_32:
		case TIPO_ENTERO_64:
			tmc->tipo = TIPO_ENTERO_64;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_ENTERO_32:
		switch (t2->tipo)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
		case TIPO_ENTERO_32:
			tmc->tipo = TIPO_ENTERO_32;
			return tmc;
			break;
		
		case TIPO_NATURAL_32:
		case TIPO_ENTERO_64:
			tmc->tipo = TIPO_ENTERO_64;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_ENTERO_64:
		switch (t2->tipo)
		{
		case TIPO_BOOLEANO:
		case TIPO_NATURAL_8:
		case TIPO_NATURAL_16:
		case TIPO_NATURAL_32:
		case TIPO_ENTERO_8:
		case TIPO_ENTERO_16:
		case TIPO_ENTERO_32:
		case TIPO_ENTERO_64:
		case TIPO_PUNTERO:
			tmc->tipo = TIPO_ENTERO_64;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_REAL_32:
		switch (t2->tipo)
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
			tmc->tipo = TIPO_REAL_32;
			return tmc;
			break;
		
		default:
			break;
		}
	
	case TIPO_REAL_64:
		switch (t2->tipo)
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
			tmc->tipo = TIPO_REAL_64;
			return tmc;
			break;
		
		default:
			break;
		}

	case TIPO_VECTOR:
		{
			tmc->tamaño(t2->tamaño());
			Ñ::Tipo* subtipo = obténTipoMínimoComún(t1->subtipo(), t2->subtipo());
			((Ñ::Nodo*)tmc)->ramas.push_back((Ñ::Nodo*)subtipo);
		}
		break;
	
	default:
		break;
	}

	return tmc;
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

std::string Ñ::obténNombreDeTipo(Ñ::Tipo* t)
{
	std::string nombre = "";

	if(t == nullptr)
	{
		nombre = "";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_NADA)
	{
		nombre = "nada";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_BOOLEANO)
	{
		nombre = "booleano";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_NATURAL_8)
	{
		nombre = "nat8";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_NATURAL_16)
	{
		nombre = "nat16";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_NATURAL_32)
	{
		nombre = "nat32";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_NATURAL_64)
	{
		nombre = "nat64";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_ENTERO_8)
	{
		nombre = "ent8";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_ENTERO_16)
	{
		nombre = "ent16";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_ENTERO_32)
	{
		nombre = "ent32";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_ENTERO_64)
	{
		nombre = "ent64";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_REAL_32)
	{
		nombre = "real32";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_REAL_64)
	{
		nombre = "real64";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_PUNTERO)
	{
		Ñ::Nodo* n = (Ñ::Nodo*)t;
		uint64_t tamaño = n->ramas.size();
		if(tamaño < 1)
		{
			return "";
		}
		Ñ::Nodo* subnodo = n->ramas[0];
		Ñ::Tipo* subtipo = (Ñ::Tipo*)subnodo;
		nombre = obténNombreDeTipo(subtipo);
		nombre += "*";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_TEXTO)
	{
		nombre = "txt";
	}
	else if(t->tipo == Ñ::CategoríaTipo::TIPO_VECTOR)
	{
		Ñ::Nodo* n = (Ñ::Nodo*)t;
		uint64_t tamaño = n->ramas.size();
		if(tamaño < 1)
		{
			return "";
		}
		Ñ::Nodo* subnodo = n->ramas[0];
		Ñ::Tipo* subtipo = (Ñ::Tipo*)subnodo;
		nombre = obténNombreDeTipo(subtipo);
		nombre += "[";
		nombre += std::to_string(t->tamaño());
		nombre += "]";
	}

	return nombre;
}

Ñ::Tipo* Ñ::obténTipoDeLiteral(Ñ::Literal* literal)
{
	if(literal == nullptr)
	{
		return nullptr;
	}
	
	if(((Ñ::Nodo*)literal)->categoría != Ñ::CategoríaNodo::NODO_LITERAL)
	{
		return nullptr;
	}

	Ñ::Tipo* tipo = new Ñ::Tipo;
	tipo->tipo = literal->tipo;

	if(tipo->tipo == Ñ::CategoríaTipo::TIPO_VECTOR)
	{
		uint64_t tamaño = ((Ñ::Nodo*)literal)->ramas.size();

		if(tamaño < 1)
		{
			delete tipo;
			return nullptr;
		}
		else
		{
			Ñ::Tipo* subtipo = nullptr;
			for(Ñ::Nodo* subliteral : ((Ñ::Nodo*)literal)->ramas)
			{
				if(subtipo != nullptr)
				{
					subtipo = obténTipoMínimoComún(subtipo, obténTipoDeLiteral((Ñ::Literal*)subliteral));
				}
				else
				{
					subtipo = obténTipoDeLiteral((Ñ::Literal*)subliteral);
				}
			}
				
			((Ñ::Nodo*)tipo)->ramas.push_back((Ñ::Nodo*)subtipo);
			tipo->tamaño(tamaño);

			return tipo;
		}
	}
}

Ñ::Tipo* Ñ::obténTipoDeValor(Ñ::Valor* valor)
{
	if(valor == nullptr)
	{
		return nullptr;
	}
	
	if(((Ñ::Nodo*)valor)->categoría != Ñ::CategoríaNodo::NODO_VALOR)
	{
		return nullptr;
	}

	Ñ::Tipo* tipo = new Ñ::Tipo;
	tipo->tipo = valor->tipo;

	if(tipo->tipo == Ñ::CategoríaTipo::TIPO_VECTOR)
	{
		uint64_t tamaño = ((Ñ::Nodo*)valor)->ramas.size();
		
		if(tamaño < 1)
		{
			delete tipo;
			return nullptr;
		}
		else
		{
			Ñ::Tipo* subtipo = nullptr;
			for(Ñ::Nodo* subvalor : ((Ñ::Nodo*)valor)->ramas)
			{
				if(subtipo != nullptr)
				{
					subtipo = obténTipoMínimoComún(subtipo, obténTipoDeValor((Ñ::Valor*)subvalor));
				}
				else
				{
					subtipo = obténTipoDeValor((Ñ::Valor*)subvalor);
				}
			}
				
			((Ñ::Nodo*)tipo)->ramas.push_back((Ñ::Nodo*)subtipo);
			tipo->tamaño(tamaño);

			return tipo;
		}
	}
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
	else if(nombre == "real32")
	{
		return Ñ::CategoríaTipo::TIPO_REAL_32;
	}
	else if(nombre == "real64")
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

bool Ñ::tiposAsignables(Ñ::Tipo* lia, Ñ::Tipo* lda)
{
	switch (lia->tipo)
	{
	case TIPO_BOOLEANO:
		switch (lda->tipo)
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
		switch (lda->tipo)
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
		switch (lda->tipo)
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
		switch (lda->tipo)
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
		switch (lda->tipo)
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
		switch (lda->tipo)
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
		switch (lda->tipo)
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
		switch (lda->tipo)
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
		switch (lda->tipo)
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
		switch (lda->tipo)
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
		switch (lda->tipo)
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

	case TIPO_VECTOR:
		switch (lda->tipo)
		{
		case TIPO_VECTOR:
			if(((Ñ::Nodo*)lia)->ramas.size() == ((Ñ::Nodo*)lda)->ramas.size())
			{
				for(int i = 0; i < ((Ñ::Nodo*)lia)->ramas.size(); i++)
				{
					Ñ::Tipo* sublia = (Ñ::Tipo*)((Ñ::Nodo*)lia)->ramas[i];
					Ñ::Tipo* sublda = (Ñ::Tipo*)((Ñ::Nodo*)lda)->ramas[i];
					if(!tiposAsignables(sublia, sublda))
					{
						return false;
					}
				}
				
				if(lia->tamaño() != lda->tamaño())
				{
					return false;
				}
			}
			else
			{
				return false;
			}
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