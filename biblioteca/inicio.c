/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.
*/

extern int inicia();

#include "es.h"

extern int holamundo()
{
    txt texto = sumaTxt(creaTxt("¡hola, "), creaTxt("mundo!\n"));
    return escribetxt(texto);
}

int __stdcall __lugar_de_inicio()
{
    int devuelto = inicia();
    return devuelto;
}
