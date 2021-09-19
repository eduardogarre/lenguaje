#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "llvm/Support/TargetSelect.h"

#include "promotor.hpp"
#include "ñ/ñ.hpp"

std::string leeArchivo(std::filesystem::path archivo)
{
    // Open the stream to 'lock' the file.
    std::ifstream arc(archivo, std::ios::in | std::ios::binary);

    // Obtain the size of the file.
    const auto tamaño = std::filesystem::file_size(archivo);

    // Create a buffer.
    std::string resultado(tamaño, '\0');

    // Read the whole file into the buffer.
    arc.read(resultado.data(), tamaño);

    return resultado;
}

int construyeArchivo(std::string archivo, Ñ::EntornoConstrucción *entorno)
{
	std::string código = "";

	try{
		código = leeArchivo(archivo);
	}
	catch (std::exception& e)
	{
		std::cout << "Error al leer el archivo" << '\n';
	}

	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;

	Ñ::Léxico léxico;
	Ñ::Sintaxis sintaxis;
	
	lexemas = léxico.analiza(código);

	if(lexemas.empty())
	{
		Ñ::errorConsola(u8"Error durante el análisis léxico, código incorrecto.");
		
		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();

		return -1;
	}

	nodos = sintaxis.analiza(lexemas, archivo);

	if(nodos == nullptr)
	{
		Ñ::errorConsola(u8"Error durante el análisis sintáctico, código incorrecto.");
		muestraLexemas(lexemas);

		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();

		return -1;
	}

	Ñ::TablaSímbolos* tablaSímbolos = new Ñ::TablaSímbolos;
	Ñ::Resultado resultado = Ñ::analizaSemántica(nodos, tablaSímbolos);
	delete tablaSímbolos;

	if(resultado.error())
	{
		std::cout << resultado.mensaje() << std::endl;
		muestraNodos(nodos);
	
		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();
		delete nodos;
		return -1;
	}
	else
	{
		//auto resultado = Ñ::interpretaNodos(nodos, tablaSímbolos);
		//if(resultado.error())
		//{
		//	std::cout << resultado.mensaje() << std::endl;
		//	muestraNodos(nodos);
		//}
	}

	resultado = Ñ::construye(nodos, entorno);

	for(auto l : lexemas)
	{
		delete l;
	}
	lexemas.clear();
	delete nodos;

	if(resultado.error())
	{
		std::cout << resultado.mensaje() << std::endl;
		return -1;
	}

	return 0;
}

int Compilador::construyeArchivos(std::vector<std::string> archivos)
{
	Ñ::EntornoConstrucción *entorno = new Ñ::EntornoConstrucción;
	
	llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmParser();
	llvm::InitializeNativeTargetAsmPrinter();

    for(std::string archivo : archivos)
    {
        int resultado = construyeArchivo(archivo, entorno);
        if(resultado != 0)
        {
            return resultado;
        }
    }
    return 0;
}