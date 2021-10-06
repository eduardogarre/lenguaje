#pragma once

#include <string>
#include <vector>

namespace Compilador
{
    struct Configuración
    {
        bool HABLADOR = false;
        uint8_t optimización = 1;
        
        std::vector<std::string> archivos;
        
        std::string nombreArchivoDestino = "programa";

        #ifdef _WIN32 //// WINDOWS ////
        std::string extensión = ".exe";
        #else
        std::string extensión = "";
        #endif
    };
}