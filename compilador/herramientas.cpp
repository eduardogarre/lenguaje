#include "herramientas.hpp"

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