#pragma once

#include <map>
#include <string>

#include "ñ/ñ.hpp"

// Creo un nodo para contener la tabla de símbolos
class NTablaSímbolos : Ñ::Nodo
{
public:
	std::map<std::string, Ñ::Símbolo>* tablaSímbolos;

	NTablaSímbolos(std::map<std::string, Ñ::Símbolo>* tabla);
	NTablaSímbolos(const NTablaSímbolos& nodo);
	~NTablaSímbolos();

	void muestra();
};