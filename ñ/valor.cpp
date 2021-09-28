#include <algorithm>
#include <iostream>
#include <string>

#include "nodo.hpp"
#include "resultado.hpp"
#include "tipo.hpp"
#include "valor.hpp"

Ñ::Valor::Valor() : Ñ::Nodo()
{
	categoría = Ñ::CategoríaNodo::NODO_VALOR;
	tipo = Ñ::CategoríaTipo::TIPO_NADA;
}

Ñ::Valor::~Valor() {}


Ñ::CategoríaTipo Ñ::Valor::obténTipo()
{
	return tipo;
}



std::string Ñ::Valor::texto()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_TEXTO)
	{
		return _texto;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::texto(std::string texto)
{
	tipo = Ñ::CategoríaTipo::TIPO_TEXTO;
	_texto = texto;
}

bool Ñ::Valor::esTexto()
{
	return tipo == Ñ::CategoríaTipo::TIPO_TEXTO;
}



uint8_t Ñ::Valor::nat8()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_NATURAL_8)
	{
		return dato.nat8;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::nat8(uint8_t nat8)
{
	tipo = Ñ::CategoríaTipo::TIPO_NATURAL_8;
	dato.nat8 = nat8;
}

bool Ñ::Valor::esNat8()
{
	return tipo == Ñ::CategoríaTipo::TIPO_NATURAL_8;
}



uint16_t Ñ::Valor::nat16()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_NATURAL_16)
	{
		return dato.nat16;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::nat16(uint16_t nat16)
{
	tipo = Ñ::CategoríaTipo::TIPO_NATURAL_16;
	dato.nat16 = nat16;
}

bool Ñ::Valor::esNat16()
{
	return tipo == Ñ::CategoríaTipo::TIPO_NATURAL_16;
}



uint32_t Ñ::Valor::nat32()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_NATURAL_32)
	{
		return dato.nat32;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::nat32(uint32_t nat32)
{
	tipo = Ñ::CategoríaTipo::TIPO_NATURAL_32;
	dato.nat32 = nat32;
}

bool Ñ::Valor::esNat32()
{
	return tipo == Ñ::CategoríaTipo::TIPO_NATURAL_32;
}



uint64_t Ñ::Valor::nat64()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_NATURAL_64)
	{
		return dato.nat64;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::nat64(uint64_t nat64)
{
	tipo = Ñ::CategoríaTipo::TIPO_NATURAL_64;
	dato.nat64 = nat64;
}

bool Ñ::Valor::esNat64()
{
	return tipo == Ñ::CategoríaTipo::TIPO_NATURAL_64;
}



int8_t Ñ::Valor::ent8()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_ENTERO_8)
	{
		return dato.ent8;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::ent8(int8_t ent8)
{
	tipo = Ñ::CategoríaTipo::TIPO_ENTERO_8;
	dato.ent8 = ent8;
}

bool Ñ::Valor::esEnt8()
{
	return tipo == Ñ::CategoríaTipo::TIPO_ENTERO_8;
}



int16_t Ñ::Valor::ent16()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_ENTERO_16)
	{
		return dato.ent16;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::ent16(int16_t ent16)
{
	tipo = Ñ::CategoríaTipo::TIPO_ENTERO_16;
	dato.ent16 = ent16;
}

bool Ñ::Valor::esEnt16()
{
	return tipo == Ñ::CategoríaTipo::TIPO_ENTERO_16;
}



int32_t Ñ::Valor::ent32()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_ENTERO_32)
	{
		return dato.ent32;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::ent32(int32_t ent32)
{
	tipo = Ñ::CategoríaTipo::TIPO_ENTERO_32;
	dato.ent32 = ent32;
}

bool Ñ::Valor::esEnt32()
{
	return tipo == Ñ::CategoríaTipo::TIPO_ENTERO_32;
}



int64_t Ñ::Valor::ent64()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_ENTERO_64)
	{
		return dato.ent64;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::ent64(int64_t ent64)
{
	tipo = Ñ::CategoríaTipo::TIPO_ENTERO_64;
	dato.ent64 = ent64;
}

bool Ñ::Valor::esEnt64()
{
	return tipo == Ñ::CategoríaTipo::TIPO_ENTERO_64;
}



float Ñ::Valor::real32()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_REAL_32)
	{
		return dato.real32;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::real32(float real32)
{
	tipo = Ñ::CategoríaTipo::TIPO_REAL_32;
	dato.real32 = real32;
}

bool Ñ::Valor::esReal32()
{
	return tipo == Ñ::CategoríaTipo::TIPO_REAL_32;
}



double Ñ::Valor::real64()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_REAL_64)
	{
		return dato.real64;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::real64(double real64)
{
	tipo = Ñ::CategoríaTipo::TIPO_REAL_64;
	dato.real64 = real64;
}

bool Ñ::Valor::esReal64()
{
	return tipo == Ñ::CategoríaTipo::TIPO_REAL_64;
}



bool Ñ::Valor::booleano()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_BOOLEANO)
	{
		return dato.booleano;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::booleano(bool booleano)
{
	tipo = Ñ::CategoríaTipo::TIPO_BOOLEANO;
	dato.booleano = booleano;
}

bool Ñ::Valor::esBooleano()
{
	return tipo == Ñ::CategoríaTipo::TIPO_BOOLEANO;
}



int64_t Ñ::Valor::puntero()
{
	if(tipo == Ñ::CategoríaTipo::TIPO_PUNTERO)
	{
		return dato.puntero;
	}
	else
	{
		return 0;
	}
}

void Ñ::Valor::puntero(int64_t puntero)
{
	tipo = Ñ::CategoríaTipo::TIPO_PUNTERO;
	dato.puntero = puntero;
}

bool Ñ::Valor::esPuntero()
{
	return tipo == Ñ::CategoríaTipo::TIPO_PUNTERO;
}

void Ñ::Valor::vector(uint64_t tamaño)
{
	tipo = Ñ::CategoríaTipo::TIPO_VECTOR;
	dato.vector = tamaño;
}

bool Ñ::Valor::esVector()
{
	return tipo == Ñ::CategoríaTipo::TIPO_VECTOR;
}



void Ñ::Valor::muestra()
{
	imprimeAjuste();
	std::cout << "(NODO_VALOR) [";
	std::cout << obténNombreDeTipo(obténTipoDeValor(this)) << "] [";
	

	if(esNat8())
	{
		std::cout << std::to_string(nat8());
	}
	else if(esNat16())
	{
		std::cout << std::to_string(nat16());
	}
	else if(esNat32())
	{
		std::cout << std::to_string(nat32());
	}
	else if(esNat64())
	{
		std::cout << std::to_string(nat64());
	}
	else if(esEnt8())
	{
		std::cout << std::to_string(ent8());
	}
	else if(esEnt16())
	{
		std::cout << std::to_string(ent16());
	}
	else if(esEnt32())
	{
		std::cout << std::to_string(ent32());
	}
	else if(esEnt64())
	{
		std::cout << std::to_string(ent64());
	}
	else if(esReal32())
	{
		std::cout << std::to_string(real32());
	}
	else if(esReal64())
	{
		std::cout << std::to_string(real64());
	}
	else if(esBooleano())
	{
		std::cout << std::to_string(booleano());
	}
	else if(esPuntero())
	{
		std::cout << std::to_string(puntero());
	}
	else if(esTexto())
	{
		std::cout << texto();
	}
	else
	{
		std::cout << "nada";
	}

	std::cout << "] - [hijos:" + std::to_string(ramas.size()) + "]" << std::endl;
	
	for(auto rama : ramas)
	{
		muestraNodos(rama);
	}
}


Ñ::Resultado Ñ::aBooleano(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->nat8(1);
		}
		else
		{
			v->nat8(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a bool");
		return resultado;
	}
}


Ñ::Resultado Ñ::aNat8(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->nat8(1);
		}
		else
		{
			v->nat8(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->nat8(valor->nat8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a nat8");
		return resultado;
	}
}

Ñ::Resultado Ñ::aNat16(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->nat16(1);
		}
		else
		{
			v->nat16(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->nat16(valor->nat8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat16())
	{
		v->nat16(valor->nat16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a nat16");
		return resultado;
	}
}

Ñ::Resultado Ñ::aNat32(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->nat32(1);
		}
		else
		{
			v->nat32(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->nat32(valor->nat8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat16())
	{
		v->nat32(valor->nat16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat32())
	{
		v->nat32(valor->nat32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a nat32");
		return resultado;
	}
}

Ñ::Resultado Ñ::aNat64(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->nat64(1);
		}
		else
		{
			v->nat64(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->nat64(valor->nat8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat16())
	{
		v->nat64(valor->nat16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat32())
	{
		v->nat64(valor->nat32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat64())
	{
		v->nat64(valor->nat64());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a nat64");
		return resultado;
	}
}


Ñ::Resultado Ñ::aEnt8(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->ent8(1);
		}
		else
		{
			v->ent8(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt8())
	{
		v->ent8(valor->ent8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a ent8");
		return resultado;
	}
}

Ñ::Resultado Ñ::aEnt16(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->ent16(1);
		}
		else
		{
			v->ent16(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->ent16(valor->nat8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt8())
	{
		v->ent16(valor->ent8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt16())
	{
		v->ent16(valor->ent16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a ent16");
		return resultado;
	}
}

Ñ::Resultado Ñ::aEnt32(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->ent32(1);
		}
		else
		{
			v->ent32(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->ent32(valor->nat8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat16())
	{
		v->ent32(valor->nat16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt8())
	{
		v->ent32(valor->ent8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt16())
	{
		v->ent32(valor->ent16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt32())
	{
		v->ent32(valor->ent32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a ent32");
		return resultado;
	}
}

Ñ::Resultado Ñ::aEnt64(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->ent64(1);
		}
		else
		{
			v->ent64(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->ent64(valor->nat8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat16())
	{
		v->ent64(valor->nat16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat32())
	{
		v->ent64(valor->nat32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt8())
	{
		v->ent64(valor->ent8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt16())
	{
		v->ent64(valor->ent16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt32())
	{
		v->ent64(valor->ent32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt64())
	{
		v->ent64(valor->ent64());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a ent64");
		return resultado;
	}
}

Ñ::Resultado Ñ::aPuntero(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;

	if(valor->esPuntero())
	{
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a puntero");
		return resultado;
	}

	resultado = aEnt64(valor);

	if(resultado.error())
	{
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a puntero");
		return resultado;
	}
	else
	{
		return resultado;
	}
}

Ñ::Resultado Ñ::aReal32(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->real32(1);
		}
		else
		{
			v->real32(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->real32(valor->nat8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat16())
	{
		v->real32(valor->nat16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat32())
	{
		v->real32(valor->nat32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat64())
	{
		v->real32(valor->nat64());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt8())
	{
		v->real32(valor->ent8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt16())
	{
		v->real32(valor->ent16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt32())
	{
		v->real32(valor->ent32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt64())
	{
		v->real32(valor->ent64());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esReal32())
	{
		v->real32(valor->real32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a real32");
		return resultado;
	}
}

Ñ::Resultado Ñ::aReal64(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->real64(1);
		}
		else
		{
			v->real64(0);
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->real64(valor->nat8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat16())
	{
		v->real64(valor->nat16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat32())
	{
		v->real64(valor->nat32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat64())
	{
		v->real64(valor->nat64());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt8())
	{
		v->real64(valor->ent8());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt16())
	{
		v->real64(valor->ent16());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt32())
	{
		v->real64(valor->ent32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt64())
	{
		v->real64(valor->ent64());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esReal32())
	{
		v->real64(valor->real32());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esReal64())
	{
		v->real64(valor->real64());
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a real64");
		return resultado;
	}
}

Ñ::Resultado Ñ::aTexto(Ñ::Valor* valor)
{
	Ñ::Resultado resultado;
	Ñ::Valor* v = new Ñ::Valor;

	if(valor->esBooleano())
	{
		if(valor->booleano())
		{
			v->texto("cierto");
		}
		else
		{
			v->texto("falso");
		}

		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat8())
	{
		v->texto(std::to_string(valor->nat8()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat16())
	{
		v->texto(std::to_string(valor->nat16()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat32())
	{
		v->texto(std::to_string(valor->nat32()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esNat64())
	{
		v->texto(std::to_string(valor->nat64()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt8())
	{
		v->texto(std::to_string(valor->ent8()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt16())
	{
		v->texto(std::to_string(valor->ent16()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt32())
	{
		v->texto(std::to_string(valor->ent32()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esEnt64())
	{
		v->texto(std::to_string(valor->ent64()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esReal32())
	{
		v->texto(std::to_string(valor->real32()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else if(valor->esReal64())
	{
		v->texto(std::to_string(valor->real64()));
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)v);
		return resultado;
	}
	else
	{
		delete v;
		resultado.error("CONVERSIÓN DE TIPOS - No está permitida la conversión de "
						+ Ñ::obténNombreDeTipo(obténTipoDeValor(valor))
						+ " a texto");
		return resultado;
	}
}

Ñ::Resultado Ñ::convierteValor(Ñ::Valor* valor, Ñ::Tipo* tipoDestino)
{
	Ñ::Resultado resultado;

	switch (tipoDestino->tipo)
	{
	case Ñ::CategoríaTipo::TIPO_NADA:
		delete valor;
		resultado.éxito();
		resultado.nodo((Ñ::Nodo*)(new Ñ::Valor));
		return resultado;
		break;
	
	case Ñ::CategoríaTipo::TIPO_BOOLEANO:
		return Ñ::aBooleano(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_NATURAL_8:
		return Ñ::aNat8(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_NATURAL_16:
		return Ñ::aNat16(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_NATURAL_32:
		return Ñ::aNat32(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_NATURAL_64:
		return Ñ::aNat64(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_ENTERO_8:
		return Ñ::aEnt8(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_ENTERO_16:
		return Ñ::aEnt16(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_ENTERO_32:
		return Ñ::aEnt32(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_ENTERO_64:
		return Ñ::aEnt64(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_REAL_32:
		return Ñ::aReal32(valor);
		break;
	
	case Ñ::CategoríaTipo::TIPO_REAL_64:
		return Ñ::aReal64(valor);
		break;
	
	default:
		resultado.error("Tipo inválido: " + Ñ::obténNombreDeTipo(tipoDestino));
		return resultado;
		break;
	}
}

bool Ñ::comparaValores(Ñ::Valor* valor1, Ñ::Valor* valor2)
{
	Ñ::Valor* v1;
	Ñ::Valor* v2;
	Ñ::Resultado r1;
	Ñ::Resultado r2;

	Ñ::Tipo* tmc = obténTipoMínimoComún(obténTipoDeValor(valor1), obténTipoDeValor(valor2));
	
	switch (tmc->tipo)
	{
	case TIPO_NADA:
		return false;
		break;
	
	case TIPO_PUNTERO:
		r1 = Ñ::aPuntero(valor1);
		r2 = Ñ::aPuntero(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->puntero() == v2->puntero());
		break;
	
	case TIPO_TEXTO:
		r1 = Ñ::aTexto(valor1);
		r2 = Ñ::aTexto(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->texto() == v2->texto());
		break;
	
	case TIPO_BOOLEANO:
		r1 = Ñ::aBooleano(valor1);
		r2 = Ñ::aBooleano(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->booleano() == v2->booleano());
		break;
	
	case TIPO_NATURAL_8:
		r1 = Ñ::aNat8(valor1);
		r2 = Ñ::aNat8(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->nat8() == v2->nat8());
		break;
	
	case TIPO_NATURAL_16:
		r1 = Ñ::aNat16(valor1);
		r2 = Ñ::aNat16(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->nat16() == v2->nat16());
		break;
	
	case TIPO_NATURAL_32:
		r1 = Ñ::aNat32(valor1);
		r2 = Ñ::aNat32(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->nat32() == v2->nat32());
		break;
	
	case TIPO_NATURAL_64:
		r1 = Ñ::aNat64(valor1);
		r2 = Ñ::aNat64(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->nat64() == v2->nat64());
		break;
	
	case TIPO_ENTERO_8:
		r1 = Ñ::aEnt8(valor1);
		r2 = Ñ::aEnt8(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->ent8() == v2->ent8());
		break;
	
	case TIPO_ENTERO_16:
		r1 = Ñ::aEnt16(valor1);
		r2 = Ñ::aEnt16(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->ent16() == v2->ent16());
		break;
	
	case TIPO_ENTERO_32:
		r1 = Ñ::aEnt32(valor1);
		r2 = Ñ::aEnt32(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->ent32() == v2->ent32());
		break;
	
	case TIPO_ENTERO_64:
		r1 = Ñ::aEnt64(valor1);
		r2 = Ñ::aEnt64(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->ent64() == v2->ent64());
		break;
	
	case TIPO_REAL_32:
		r1 = Ñ::aReal32(valor1);
		r2 = Ñ::aReal32(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->real32() == v2->real32());
		break;
	
	case TIPO_REAL_64:
		r1 = Ñ::aReal64(valor1);
		r2 = Ñ::aReal64(valor2);
		v1 = (Ñ::Valor*)(r1).nodo();
		v2 = (Ñ::Valor*)(r2).nodo();
		return (v1->real64() == v2->real64());
		break;
	
	default:
		return false;
		break;
	}

	return false;
}


Ñ::Valor* Ñ::duplicaValor(Ñ::Valor* valor)
{
	Ñ::Valor* v;

	if(valor == nullptr)
	{
		return nullptr;
	}
	else if(((Ñ::Nodo*)valor)->categoría != Ñ::CategoríaNodo::NODO_VALOR)
	{
		return nullptr;
	}
	
	switch (valor->obténTipo())
	{
	case TIPO_NADA:
		v = new Ñ::Valor;
		return v;
		break;
	
	case TIPO_PUNTERO:
		v = new Ñ::Valor;
		v->puntero(valor->puntero());
		return v;
		break;
	
	case TIPO_TEXTO:
		v = new Ñ::Valor;
		v->texto(valor->texto());
		return v;
		break;
	
	case TIPO_BOOLEANO:
		v = new Ñ::Valor;
		v->booleano(valor->booleano());
		return v;
		break;
	
	case TIPO_NATURAL_8:
		v = new Ñ::Valor;
		v->nat8(valor->nat8());
		return v;
		break;
	
	case TIPO_NATURAL_16:
		v = new Ñ::Valor;
		v->nat16(valor->nat16());
		return v;
		break;
	
	case TIPO_NATURAL_32:
		v = new Ñ::Valor;
		v->nat32(valor->nat32());
		return v;
		break;
	
	case TIPO_NATURAL_64:
		v = new Ñ::Valor;
		v->nat64(valor->nat64());
		return v;
		break;
	
	case TIPO_ENTERO_8:
		v = new Ñ::Valor;
		v->ent8(valor->ent8());
		return v;
		break;
	
	case TIPO_ENTERO_16:
		v = new Ñ::Valor;
		v->ent16(valor->ent16());
		return v;
		break;
	
	case TIPO_ENTERO_32:
		v = new Ñ::Valor;
		v->ent32(valor->ent32());
		return v;
		break;
	
	case TIPO_ENTERO_64:
		v = new Ñ::Valor;
		v->ent64(valor->ent64());
		return v;
		break;
	
	case TIPO_REAL_32:
		v = new Ñ::Valor;
		v->real32(valor->real32());
		return v;
		break;
	
	case TIPO_REAL_64:
		v = new Ñ::Valor;
		v->real64(valor->real64());
		return v;
		break;
	
	default:
		v = new Ñ::Valor;
		return v;
		break;
	}
}

Ñ::Valor* Ñ::creaValor(Ñ::Literal* literal)
{
	if(literal == nullptr)
	{
		return nullptr;
	}
	else if(((Ñ::Nodo*)literal)->categoría != Ñ::CategoríaNodo::NODO_LITERAL)
	{
		return nullptr;
	}
	else if(literal->dato == "nulo")
	{
		return new Ñ::Valor;
	}
	
	Ñ::Valor* valor = new Ñ::Valor;

	for(auto subliteral : ((Ñ::Nodo*)literal)->ramas)
	{
		Ñ::Valor* subvalor = creaValor((Ñ::Literal*)subliteral);
		((Ñ::Nodo*)valor)->ramas.push_back((Ñ::Nodo*)subvalor);
	}
	
	switch (literal->tipo)
	{
	case Ñ::CategoríaTipo::TIPO_NADA:
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_BOOLEANO:
		if(literal->dato == "cierto")
		{
			valor->booleano(true);
		}
		else if(literal->dato == "falso")
		{
			valor->booleano(false);
		}
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_ENTERO_8:
		valor->ent8(std::stoi(literal->dato));
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_ENTERO_16:
		valor->ent16(std::stoi(literal->dato));
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_ENTERO_32:
		valor->ent32(std::stoi(literal->dato));
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_ENTERO_64:
		valor->ent64(std::stoi(literal->dato));
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_NATURAL_8:
		valor->nat8(std::stoul(literal->dato));
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_NATURAL_16:
		valor->nat16(std::stoul(literal->dato));
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_NATURAL_32:
		valor->nat32(std::stoul(literal->dato));
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_NATURAL_64:
		valor->nat64(std::stoul(literal->dato));
		return valor;
		break;
	
	case Ñ::CategoríaTipo::TIPO_REAL_32:
		valor->real32(std::stof(literal->dato));
		return valor;
		break;

	case Ñ::CategoríaTipo::TIPO_REAL_64:
		valor->real64(std::stod(literal->dato));
		return valor;
		break;

	case Ñ::CategoríaTipo::TIPO_VECTOR:
		valor->vector(((Ñ::Nodo*)valor)->ramas.size());
		return valor;
		break;
	
	default:
		return valor;
		break;
	}
}