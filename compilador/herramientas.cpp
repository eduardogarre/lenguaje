/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "herramientas.hpp"

#if defined(WIN32) || defined(WIN64)
#include <Windows.h>
std::string obténCarpetaInstalación()
{
	char espacio[MAX_PATH];
	GetModuleFileNameA(NULL, espacio, MAX_PATH);
	std::string::size_type posición = std::string(espacio).find_last_of("\\/");
	
	return std::string(espacio).substr(0, posición);
}
#elif defined(UNIX)
#include <unistd.h> 
std::string obténCarpetaInstalación()
{
	char espacio[MAX_PATH];
    readlink("/proc/self/exe", espacio, MAX_PATH);
	std::string::size_type posición = std::string(espacio).find_last_of("\\/");
	
	return std::string(espacio).substr(0, posición);
}
#endif

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

#ifdef __linux__  //// LINUX ////
#include <iostream>
int ejecutaPrograma(std::string ruta, std::string argumentos)
{
    std::string comando = ruta + " " + argumento;
    
    return system(comando);
}

#elif _WIN32 //// WINDOWS ////
#include <locale>
#include <codecvt>
#include "Windows.h"
int ejecutaPrograma(std::string ruta, std::string argumentos)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conversor;
    std::wstring rutaAncha = conversor.from_bytes(ruta);;
    LPCTSTR lpNombreAplicación = rutaAncha.c_str();
    
    std::wstring argumentosAnchos = conversor.from_bytes(argumentos);
    LPWSTR lpLíneaArgumentos = &argumentosAnchos[0];

    // additional information
    STARTUPINFO si;     
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // start the program up
    CreateProcess( lpNombreAplicación,   // the path
            lpLíneaArgumentos,  // Command line
            NULL,               // Process handle not inheritable
            NULL,               // Thread handle not inheritable
            FALSE,              // Set handle inheritance to FALSE
            0,                  // No creation flags
            NULL,               // Use parent's environment block
            NULL,               // Use parent's starting directory 
            &si,                // Pointer to STARTUPINFO structure
            &pi                 // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
        );

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );
    
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

    return 0;
}

#else
#include <iostream>
int ejecutaPrograma(std::string ruta, std::string argumentos)
{
    std::string comando = ruta + " " + argumento;
    
    return system(comando);
}

#endif