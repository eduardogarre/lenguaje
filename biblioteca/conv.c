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

#include "conv.h"
#include "es.h"
#include "mem.h"

long long int longitud(char* _texto)
{
    long long int largo = 0;

    while(_texto[largo] != '\0')
    {
        largo++;
    }

    return largo;
}

extern void copia(char* origen, char* destino)
{
    int i = 0;
    while(origen[i] != '\0')
    {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

extern char* duplicatxt(char* _texto)
{
    long long int largo = longitud(_texto);
    char* texto = reserva(largo);
    copia(_texto, texto);
    return texto;
}

char* invierte(char* _texto)
{
    int inicio = 0;
    char* texto = duplicatxt(_texto);
    int fin = longitud(texto) - 1;

    while(inicio < fin)
    {
        // PENDIENTE
        char tmp = texto[inicio];
        texto[inicio] = texto[fin];
        texto[fin] = tmp;
        inicio++;
        fin--;
    }

    return texto;
}

extern char* entatxt(long long int _num)
{
    int base = 10;
    long long int contador = 0;
    long long int largo = 0;
    int esNegativo = 0;

    char* texto;

    // Compruebo si 0
    if(_num == 0)
    {
        texto = reserva(2);
        if(texto == NULO)
        {
            return NULO;
        }
        texto[0] = '0';
        texto[1] = '\0';
        return texto;
    }

    // Quiero operar siempre con números positivos
    if(_num < 0)
    {
        esNegativo = 1;
        _num = -_num;
    }

    long long int temporal = _num;
    // Calculo cuánto espacio necesito;
    while(temporal != 0)
    {
        largo++;
        temporal = temporal/base;
    }

    // Reservo espacio para la cadena
    // Sumo 1 por el '\0' final, y otro 1 por si es negativo, por el '-'
    texto = reserva(largo + 1 + esNegativo);

    // Voy añadiendo números a la cadena de texto, de forma inversa
    while(_num != 0)
    {
        long long int resto = _num % base;
        texto[contador++] = resto + '0';
        _num = _num/base;
    }

    if(esNegativo)
    {
        texto[contador++] = '-';
    }

    // Termino la cadena con el caracter nulo
    texto[contador] = '\0';

    char* inverso = invierte(texto);
    suelta(texto);

    return inverso;
}