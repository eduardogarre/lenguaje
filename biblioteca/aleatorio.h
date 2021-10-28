/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.
*/

#pragma once

#define ALEATORIO_MAX 0x7fff

// Siembra el generador de números aleatorios con un entero
void saleatorio(unsigned int const semilla);

// Devuelve un natural pseudoaleatorio en el rango [0, 32767].
int aleatorio();
