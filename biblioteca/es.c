#include "txt.h"

#define ASA_COMUN_ENTRADA    ((unsigned long)-10)
#define ASA_COMUN_SALIDA     ((unsigned long)-11)
#define ASA_COMUN_ERROR      ((unsigned long)-12)

extern __declspec(dllimport) int __stdcall WriteConsoleW(
    void* asaDeSalida,
    const void* almacen,
    unsigned long posicionesPorEscribir,
    unsigned long* posicionesEscritas,
    void* reservado
    );

extern __declspec(dllimport) int __stdcall WriteConsoleA(
    void* asaDeSalida,
    const void* almacen,
    unsigned long posicionesPorEscribir,
    unsigned long* posicionesEscritas,
    void* reservado
    );

extern __declspec(dllimport) int __stdcall WriteConsoleA(
    void* asaDeSalida,
    const void* almacen,
    unsigned long posicionesPorEscribir,
    unsigned long* posicionesEscritas,
    void* reservado
    );

extern void* __stdcall GetStdHandle( unsigned long asaComún );

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