#include <map>
#include <string>

#include "nodos.hpp"

NTablaSímbolos::NTablaSímbolos(std::map<std::string, Ñ::Símbolo>* tabla) : tablaSímbolos(tabla)
{
	categoría = Ñ::CategoríaNodo::NODO_EXPANDIDO;
}

NTablaSímbolos::NTablaSímbolos(const NTablaSímbolos& nodo)
{
	categoría = Ñ::CategoríaNodo::NODO_EXPANDIDO;
}

NTablaSímbolos::~NTablaSímbolos()
{
	for(uint32_t i = 0; i < ramas.size(); i++)
	{
		delete ramas[i];
	}
}