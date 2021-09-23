#pragma once

typedef struct _txt
{
    // Texto acabado en nulo.
    // El último byte representa el número de caracteres todavía disponibles
    // Cuando la cadena está vacía
    //      posición[0] a posición[14] = 0
    //      posición[15] = 15
    // Cuando la cadena tiene 14 caracteres
    //      posición[13] es el último carácter
    //      posición[14] vale 0 (nulo)
    //      posición[15] vale 1
    // Cuando la cadena tiene los 15 caracteres (está llena)
    //      posición[14] es el último carácter
    //      posición[15] vale 0 (nulo)
    char posición[16];
} txt;

txt creaTxt (const char* caracteres);

txt borraTxt(txt texto);

txt sumaTxt(txt texto1, txt texto2);

int longTxt(txt texto);

const char* cadenaCdeTxt(txt texto);