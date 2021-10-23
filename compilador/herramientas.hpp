#pragma once

#include <filesystem>
#include <string>

int         ejecutaPrograma(std::string ruta, std::string argumentos);
std::string leeArchivo(std::filesystem::path archivo);
std::string obténCarpetaInstalación();