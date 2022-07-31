/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include <memory>

#include "ejecutorjat.hpp"
#include "entorno_int.hpp"

Ñ::Resultado Ñ::ejecutaMóduloJAT(llvm::Module *móduloJAT, Ñ::EntornoConstrucción *entorno)
{
    Ñ::Resultado resultado;

    std::unique_ptr<llvm::Module> módulo(móduloJAT);
    entorno->jat->añadeMódulo(std::move(módulo));

    llvm::Expected<llvm::JITEvaluatedSymbol> funciónEvaluadaJAT = entorno->jat->busca("__función_anónima__");

    if (auto error = funciónEvaluadaJAT.takeError())
    {
        resultado.error("El constructor JAT no encuentra el símbolo '__función_anónima__()'.");
        return resultado;
    }

    void (*funciónJAT)() = (void (*)())(*funciónEvaluadaJAT).getAddress();

    if (entorno->HABLADOR)
    {
        std::cout << "ejecutando '__función_anónima__()' ..." << std::endl;
    }

    funciónJAT();

    if (entorno->HABLADOR)
    {
        std::cout << "Elimino '__función_anónima__()' ..." << std::endl;
    }
    
    entorno->jat->eliminaSímbolo("__función_anónima__");

    resultado.éxito();
    return resultado;
}