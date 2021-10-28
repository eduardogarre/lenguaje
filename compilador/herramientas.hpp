/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.
*/

#pragma once

#include <filesystem>
#include <string>

int         ejecutaPrograma(std::string ruta, std::string argumentos);
std::string leeArchivo(std::filesystem::path archivo);
std::string obténCarpetaInstalación();