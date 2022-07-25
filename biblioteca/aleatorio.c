/*
SPDX-License-Identifier: MPL-2.0-no-copyleft-exception

This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include "definiciones.h"
#include "aleatorio.h"

int estado_pseudoaleatorio = 0;

// Siembra el generador de números aleatorios con un entero
void saleatorio(unsigned int const semilla)
{
    estado_pseudoaleatorio = semilla;
}

// Devuelve un natural pseudoaleatorio en el rango [0, 32767].
int aleatorio()
{
    estado_pseudoaleatorio = estado_pseudoaleatorio * 214013 + 2531011;
    return (estado_pseudoaleatorio >> 16) & ALEATORIO_MAX;
}
