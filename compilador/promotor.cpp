#include <iostream>
#include <string>
#include <vector>

#include "llvm/Support/Host.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"

#include "configuracion.hpp"
#include "consola.hpp"
#include "herramientas.hpp"
#include "ñ/ñ.hpp"
#include "promotor.hpp"

std::string creaNombreMódulo(std::string archivo)
{
	std::filesystem::path p = archivo;
	std::string antes = p.string();
	std::string después = p.stem().string();
    //std::cout << "Antes: " << antes << std::endl;
    //std::cout << "Después: " << después << std::endl;

	return después;
}

Ñ::ResultadoLlvm construyeArchivo(std::string archivo, Ñ::EntornoConstrucción *entorno)
{
	Ñ::ResultadoLlvm resultado;

	std::string código = "";

	std::string nombreMódulo = creaNombreMódulo(archivo);

	if(entorno->HABLADOR)
	{
		std::cout << "LEYENDO EL CODIGO DEL ARCHIVO" << std::endl;
	}

	try{
		código = leeArchivo(archivo);
	}
	catch (std::exception& e)
	{
		resultado.error("No puedo leer el archivo " + archivo);
		return resultado;
	}

	std::vector<Ñ::Lexema*> lexemas;
	Ñ::Nodo* nodos;

	Ñ::Léxico léxico;
	Ñ::Sintaxis sintaxis;
	
	
	if(entorno->HABLADOR)
	{
		std::cout << "ANALIZANDO LEXICO" << std::endl;
	}

	lexemas = léxico.analiza(código);

	if(entorno->HABLADOR)
	{
		Ñ::muestraLexemas(lexemas);
	}

	/*
	if(lexemas.size() <= 1)
	{
		Ñ::errorConsola(u8"El análisis léxico no encontró código.");
		
		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();

		resultado.éxito();
		return resultado;
	}
	*/
	
	if(entorno->HABLADOR)
	{
		std::cout << "ANALIZANDO SINTAXIS" << std::endl;
	}

	nodos = sintaxis.analiza(lexemas, nombreMódulo);
	
	if(entorno->HABLADOR)
	{
		muestraNodos(nodos);
	}

	if(nodos == nullptr)
	{
		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();

		resultado.error("Error durante el análisis sintáctico, código incorrecto.");
		return resultado;
	}
	
	if(entorno->HABLADOR)
	{
		std::cout << "ANALIZANDO SEMANTICA" << std::endl;
	}

	Ñ::TablaSímbolos* tablaSímbolos = new Ñ::TablaSímbolos;
	Ñ::Resultado rSemántico = Ñ::analizaSemántica(nodos, tablaSímbolos);
	
	if(entorno->HABLADOR)
	{
		muestraNodos(nodos, tablaSímbolos);
	}

	delete tablaSímbolos;

	if(rSemántico.error())
	{
		for(auto l : lexemas)
		{
			delete l;
		}
		lexemas.clear();
		delete nodos;
		
		resultado.error(rSemántico.mensaje());
		resultado.posición(rSemántico.posición());
		return resultado;
	}
	
	if(entorno->HABLADOR)
	{
		std::cout << "CONSTRUYENDO MODULO" << std::endl;
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
		return resultado;
	}

	resultado.éxito();
	return resultado;
}

int Compilador::compila(Compilador::Configuración cfg)
{
	Ñ::EntornoConstrucción *entorno = new Ñ::EntornoConstrucción;
	entorno->optimización = cfg.optimización;
	
	llvm::InitializeNativeTarget();
	llvm::InitializeNativeTargetAsmParser();
	llvm::InitializeNativeTargetAsmPrinter();

	std::string tripleteDestino = llvm::sys::getDefaultTargetTriple();

	if(cfg.HABLADOR)
	{
		entorno->HABLADOR = true;

		std::cout << "Construiré ";
		std::cout << "'" << cfg.nombreArchivoDestino << cfg.extensión << "'";
		
		std::cout << ", empleando";

		for(std::string archivo : cfg.archivos)
		{
			std::cout << " " << archivo;
		}

		std::cout << std::endl << std::endl;

		std::cout << "Tripleta de Destino: " << tripleteDestino << std::endl << std::endl;
	}

	std::string error;
	auto destino = llvm::TargetRegistry::lookupTarget(tripleteDestino, error);

	if (!destino) {
		return -1;
	}

	std::string procesador = "x86-64";
	std::string características = "";

	llvm::TargetOptions opciones;
	auto modeloReordenamiento = llvm::Optional<llvm::Reloc::Model>();
	auto máquinaDestino = destino->createTargetMachine(tripleteDestino, procesador, características, opciones, modeloReordenamiento);

	//std::cout << "Preparando construcción con LLVM" << std::endl << std::endl;

    for(std::string archivo : cfg.archivos)
    {
		if(cfg.HABLADOR)
		{
			std::cout << "Construyendo '" << archivo << "'" << std::endl;
		}
		
        Ñ::ResultadoLlvm resultado = construyeArchivo(archivo, entorno);
        if(resultado.error())
        {
			Compilador::escribeError(resultado.mensaje(), archivo, resultado.posición());
			
            return -1;
        }

		llvm::Module* móduloLlvm = resultado.módulo();

		móduloLlvm->setDataLayout(máquinaDestino->createDataLayout());
		móduloLlvm->setTargetTriple(tripleteDestino);

		if(cfg.HABLADOR)
		{
			std::cout << std::endl << "Archivo de representación intermedia:" << std::endl << std::endl;
			móduloLlvm->print(llvm::outs(), nullptr);
		}

		std::string nombreMódulo = creaNombreMódulo(archivo);

		std::string nombreArchivoDestino = nombreMódulo + ".o";
		std::error_code códigoError;
		llvm::raw_fd_ostream archivoDestino(nombreArchivoDestino, códigoError, llvm::sys::fs::OF_None);

		if (códigoError) {
			std::cout << ("No he podido abrir el archivo: " + códigoError.message()) << std::endl;
			return -1;
		}

		llvm::legacy::PassManager paseDeCódigoObjeto;
		auto tipoArchivo = llvm::CGFT_ObjectFile;

		if(máquinaDestino->addPassesToEmitFile(paseDeCódigoObjeto, archivoDestino, nullptr, tipoArchivo))
		{
			std::cout << ("No he podido emitir un archivo de este tipo") << std::endl;
			return -1;
		}

		paseDeCódigoObjeto.run(*(móduloLlvm));
		archivoDestino.flush();

		if(cfg.HABLADOR)
		{
			std::cout << "He construido el archivo '" + nombreArchivoDestino + "'." << std::endl;
		}
    }

	std::string archivoDestino = cfg.nombreArchivoDestino + cfg.extensión;
	
	ejecutaPrograma("proyecto/lld-link.exe",
					"lld *.o proyecto/biblioteca.lib proyecto/base.lib /entry:__lugar_de_inicio /subsystem:console /nodefaultlib /out:" + archivoDestino);

    return 0;
}