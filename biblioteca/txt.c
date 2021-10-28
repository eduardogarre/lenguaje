/*
This Source Code Form is subject to the terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not distributed with this file, You can obtain one
at http://mozilla.org/MPL/2.0/.

This Source Code Form is "Incompatible With Secondary Licenses", as defined by
the Mozilla Public License, v. 2.0.

Copyright © 2021 Eduardo Garre Muñoz
*/

#include "txt.h"

txt creaTxt (const char* caracteres) {
    txt texto;
    texto = borraTxt(texto);
    int i;
    for(i = 0; i < 15 && caracteres[i] != 0; i++)
    {
        texto.posición[i] = caracteres[i];
    }

    texto.posición[i] = 0;
    texto.posición[15] = 15 - i;

    return texto;
}

txt borraTxt(txt texto)
{
    for(int i = 0; i < 15; i++)
    {
        texto.posición[i] = 0;
    }

    texto.posición[15] = 15;

    return texto;
}

txt sumaTxt(txt texto1, txt texto2)
{
    int i;
    int espacio1 = texto1.posición[15];
    for(i = 0; i < espacio1 && texto2.posición[i] != 0; i++)
    {
        texto1.posición[15 - espacio1 + i] = texto2.posición[i];
    }

    texto1.posición[15 - espacio1 + i] = 0;
    texto1.posición[15] = espacio1 - i;

    return texto1;
}

int longTxt(txt texto)
{
    return 15 - texto.posición[15];
}

const char* cadenaCdeTxt(txt texto)
{
    return texto.posición;
}