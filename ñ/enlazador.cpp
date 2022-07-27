/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include "lld/Common/Driver.h"

#include "apoyo.hpp"
#include "enlazador.hpp"

namespace Ñ
{
    ConfiguraciónEnlazador::ConfiguraciónEnlazador()
    {
    }

    ConfiguraciónEnlazador::~ConfiguraciónEnlazador()
    {
    }

    std::string ConfiguraciónEnlazador::leeNombreEnlazador()
    {
        return nombreEnlazador;
    }

    void ConfiguraciónEnlazador::ponNombreEnlazador(std::string _nombreEnlazador)
    {
        nombreEnlazador = _nombreEnlazador;
    }

    std::string ConfiguraciónEnlazador::leeNombreBibliotecaEstándar()
    {
        return nombreBibliotecaEstándar;
    }

    void ConfiguraciónEnlazador::ponNombreBibliotecaEstándar(std::string _nombreBibliotecaEstándar)
    {
        nombreBibliotecaEstándar = _nombreBibliotecaEstándar;
    }

    std::string ConfiguraciónEnlazador::leeCarpetaBibliotecaEstándar()
    {
        return carpetaBibliotecaEstándar;
    }

    void ConfiguraciónEnlazador::ponCarpetaBibliotecaEstándar(std::string _carpetaBibliotecaEstándar)
    {
        carpetaBibliotecaEstándar = _carpetaBibliotecaEstándar;
    }

    std::string ConfiguraciónEnlazador::leeLugarInicio()
    {
        return lugarInicio;
    }

    void ConfiguraciónEnlazador::ponLugarInicio(std::string _lugarInicio)
    {
        lugarInicio = _lugarInicio;
    }

    std::vector<std::string> ConfiguraciónEnlazador::leeArchivosObjeto()
    {
        return archivosObjeto;
    }

    void ConfiguraciónEnlazador::borraArchivosObjeto()
    {
        archivosObjeto.clear();
    }

    void ConfiguraciónEnlazador::ponArchivoObjeto(std::string archivoObjeto)
    {
        archivosObjeto.push_back(archivoObjeto);
    }

    std::string ConfiguraciónEnlazador::leeArchivoDestino()
    {
        return archivoDestino;
    }

    void ConfiguraciónEnlazador::ponArchivoDestino(std::string _archivoDestino)
    {
        archivoDestino = _archivoDestino;
    }

    std::string ConfiguraciónEnlazador::leeSubsistema()
    {
        return subsistema;
    }

    void ConfiguraciónEnlazador::ponSubsistema(std::string _subsistema)
    {
        subsistema = _subsistema;
    }

    std::vector<const char *> ConfiguraciónEnlazador::generaArgumentos()
    {
        std::vector<const char *> argumentos;
        char *arg;

        // El nombre asignado al enlazador debe ser el 1º argumento
        arg = deStrAPtrChars(nombreEnlazador);
        argumentos.push_back(arg);

        arg = deStrAPtrChars(carpetaBibliotecaEstándar + nombreBibliotecaEstándar);
        argumentos.push_back(arg);

        for (auto archivo : archivosObjeto)
        {
            arg = deStrAPtrChars(archivo);
            argumentos.push_back(arg);
        }

        arg = deStrAPtrChars(std::string("/entry:") + lugarInicio);
        argumentos.push_back(arg);

        arg = deStrAPtrChars(std::string("/nodefaultlib"));
        argumentos.push_back(arg);

        arg = deStrAPtrChars((std::string("/subsystem:") + subsistema));
        argumentos.push_back(arg);

        arg = deStrAPtrChars((std::string("/out:") + archivoDestino));
        argumentos.push_back(arg);

        return argumentos;
    }

    int enlaza(std::vector<const char *> argumentos)
    {
        return lld::coff::link(argumentos, true, llvm::outs(), llvm::errs());
    }

} // namespace Ñ
