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
#include "externowindows.h"
#include "conv.h"
#include "txt.h"

extern int escribetxt(txt texto)
{
    int escrito;
    WriteConsoleA(GetStdHandle(ASA_COMUN_SALIDA), (const void*) cadenaCdeTxt(texto), longTxt(texto), &escrito, 0);

    return escrito;
}

extern int escribe(char* texto)
{
    int escritotxt = 0;

    if(texto > 0)
    {
        int longitudtxt;
        for(longitudtxt = 0; texto[longitudtxt] != 0; longitudtxt++)
        {

        }
        int escritotxt;
        WriteConsoleA(GetStdHandle(ASA_COMUN_SALIDA), (const void*) texto, longitudtxt, &escritotxt, 0);
    }

    return escritotxt;
}

extern int escribeln(char* texto)
{
    int escritotxt = escribe(texto);
    int escritoln = 0;

    char* nuevalinea = "\n";
    int longitudln;
    for(longitudln = 0; nuevalinea[longitudln] != 0; longitudln++)
    {

    }

    WriteConsoleA(GetStdHandle(ASA_COMUN_SALIDA), (const void*) nuevalinea, longitudln, &escritoln, 0);

    return escritotxt + escritoln;
}

extern int escribeletra(char _letra)
{
    char texto[2];
    texto[0] = _letra;
    texto[1] = '\0';
    return escribe(texto);
}

extern int escribeletraln(char _letra)
{
    char texto[2];
    texto[0] = _letra;
    texto[1] = '\0';
    return escribeln(texto);
}

extern int escribenat(unsigned int _num)
{
    char* texto = entatxt(_num);
    return escribe(texto);
}

extern int escribenatln(unsigned int _num)
{
    char* texto = entatxt(_num);
    return escribeln(texto);
}

extern int escribeent(int _num)
{
    char* texto = entatxt(_num);
    return escribe(texto);
}

extern int escribeentln(int _num)
{
    char* texto = entatxt(_num);
    return escribeln(texto);
}