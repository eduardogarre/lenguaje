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
    class ConfiguraciónEnlazador
    {
    private:
        std::string nombreEnlazador = "enlazador";
        std::string nombreBibliotecaEstándar = "bibñ.lib";
        std::string carpetaBibliotecaEstándar = "";
        std::string lugarInicio = "__lugar_de_inicio";
        std::vector<std::string> archivosObjeto;
        std::string archivoDestino = "programa";
        std::string subsistema = "console";

    public:
        ConfiguraciónEnlazador();

        ~ConfiguraciónEnlazador();

        std::string leeNombreEnlazador();

        void ponNombreEnlazador(std::string _nombreEnlazador);

        std::string leeNombreBibliotecaEstándar();

        void ponNombreBibliotecaEstándar(std::string _nombreBibliotecaEstándar);

        std::string leeCarpetaBibliotecaEstándar();

        void ponCarpetaBibliotecaEstándar(std::string _carpetaBibliotecaEstándar);

        std::string leeLugarInicio();

        void ponLugarInicio(std::string _lugarInicio);

        std::vector<std::string> leeArchivosObjeto();

        void borraArchivosObjeto();

        void ponArchivoObjeto(std::string archivoObjeto);

        std::string leeArchivoDestino();

        void ponArchivoDestino(std::string _archivoDestino);

        std::string leeSubsistema();

        void ponSubsistema(std::string _subsistema);

        std::vector<const char *> generaArgumentos();
    };

    int enlaza(std::vector<const char *> argumentos);
}