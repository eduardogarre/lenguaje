#pragma once

#include <map>
#include <string>

#include "ñ/ñ.hpp"

// Creo un nodo para contener la tabla de símbolos
class NTablaSímbolos : Ñ::Nodo
{
public:
	Ñ::TablaSímbolos* tablaSímbolos;

	NTablaSímbolos(Ñ::TablaSímbolos* tabla);
	NTablaSímbolos(const NTablaSímbolos& nodo);
	~NTablaSímbolos();

	void muestra();
};