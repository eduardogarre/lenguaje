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

int longTxt(txt texto)
{
    return 15 - texto.posición[15];
}

const char* cadenaCdeTxt(txt texto)
{
    return texto.posición;
}