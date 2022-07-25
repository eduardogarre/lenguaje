/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#pragma once

#include <string>
#include <vector>

namespace Ñ
{
    extern class EntornoConstrucción;

    namespace Entorno {
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

        Ñ::EntornoConstrucción *preparaEntornoConstrucción(Entorno::Configuración cfg);
        void        ponArchivoActual(Ñ::EntornoConstrucción* entorno, std::string archivo);
        std::string leeArchivoActual(Ñ::EntornoConstrucción* entorno, std::string archivo);
    }
}