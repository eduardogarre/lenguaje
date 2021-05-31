#include <iostream>

#include "tipo.hpp"

Ñ::Tipo::Tipo() : Ñ::Nodo()
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

	return nombre;
}