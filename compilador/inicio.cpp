#include <cctype>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "ñ/ñ.hpp"

// Extiendo nodos para pasar argumentos
#include "nodos.hpp"

bool EJECUTA_INTÉRPRETE = true;

void _muestraTexto(std::string txt)
{
	std::cout << txt << std::endl;
}

std::string _esperaComando()
{
	std::string comando;
	std::cout << "> ";
	std::getline(std::cin, comando);

	return comando;
}

void apaga(Ñ::Argumentos* args)
{
	EJECUTA_INTÉRPRETE = false;
}

void escribe(Ñ::Argumentos* args)
{
	if(args == nullptr)
	{
		return;
	}
	else if(((Ñ::Nodo*)args)->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
	{
		if(((Ñ::Nodo*)args)->ramas.size() == 0)
		{
			return;
		}
		else if(((Ñ::Nodo*)args)->ramas.size() == 1)
		{
			Ñ::Nodo* arg = ((Ñ::Nodo*)args)->ramas[0];
			if(arg == nullptr)
			{
				return;
			}
			else if(arg->categoría == Ñ::CategoríaNodo::NODO_LITERAL)
			{
				std::string dato = ((Ñ::Literal*)arg)->dato;
				std::cout << dato;
			}
		}
	}
}

void tabla(Ñ::Argumentos* args)
{
	if(args == nullptr)
	{
		return;
	}
	else if(((Ñ::Nodo*)args)->categoría == Ñ::CategoríaNodo::NODO_ARGUMENTOS)
	{
		if(((Ñ::Nodo*)args)->ramas.size() == 0)
		{
			return;
		}
		else if(((Ñ::Nodo*)args)->ramas.size() == 1)
		{
			Ñ::Nodo* arg = ((Ñ::Nodo*)args)->ramas[0];
			if(arg == nullptr)
			{
				return;
			}
			else if(arg->categoría == Ñ::CategoríaNodo::NODO_EXPANDIDO)
			{
				auto tablaSímbolos = ((NTablaSímbolos*)arg)->tablaSímbolos;
				Ñ::muestraTablaSímbolos(*tablaSímbolos);
			}
		}
	}
}

std::map<std::string, Ñ::Símbolo>* creaTablaSímbolos()
{
	return new std::map<std::string, Ñ::Símbolo>();
}

void llenaTablaSímbolos(std::map<std::string, Ñ::Símbolo>* tablaSímbolos)
{
	// Añado una función sin argumentos
    Ñ::Símbolo s1;
    s1.añadeEjecución(escribe);
    (*tablaSímbolos)["escribe"] = s1;

	// Añado una función sin argumentos
	Ñ::Símbolo s2;
	s2.añadeEjecución(apaga);
	(*tablaSímbolos)["apaga"] = s2;

	// Añado una función con un único argumento, ntabla
	Ñ::Símbolo s3;
	Ñ::Argumentos* args = new Ñ::Argumentos();
	NTablaSímbolos* ntabla = new NTablaSímbolos(tablaSímbolos);
	((Ñ::Nodo*)args)->ramas.push_back((Ñ::Nodo*)ntabla);
	s3.añadeEjecución(tabla, (Ñ::Nodo*)args);
	(*tablaSímbolos)["tabla"] = s3;
}

void _interpretaComando(std::string comando, std::map<std::string, Ñ::Símbolo>* tablaSímbolos)
{
	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;
	
	lexemas = Ñ::analizaLéxico(comando);

	if(lexemas.empty())
	{
		Ñ::errorConsola(u8"Error durante el análisis léxico, comando incorrecto.");
		return;
	}

	nodos = Ñ::analizaSintaxis(lexemas);

	if(nodos == nullptr)
	{
		Ñ::errorConsola(u8"Error durante el análisis sintáctico, comando incorrecto.");
		muestraLexemas(lexemas);
		return;
	}

	Ñ::Resultado resultado = Ñ::analizaSemántica(nodos, tablaSímbolos);

	if(resultado.error())
	{
		std::cout << resultado.mensaje() << std::endl;
		
		muestraNodos(nodos);
	}
	else
	{
		//std::cout << "Ejecuto nodos2" << std::endl;

		auto resultado = Ñ::interpretaNodos(nodos, tablaSímbolos);
		if(resultado.error())
		{
			std::cout << resultado.mensaje() << std::endl;
		}
	}

	delete nodos;
}

int main()
{
	std::map<std::string, Ñ::Símbolo>* tablaSímbolos = creaTablaSímbolos();
	llenaTablaSímbolos(tablaSímbolos);

	while (EJECUTA_INTÉRPRETE)
	{
		std::string comando = _esperaComando();
		if(comando.size() == 0)
		{
			continue;
		}
		_interpretaComando(comando, tablaSímbolos);

		std::this_thread::yield();
	}

	return 0;
}