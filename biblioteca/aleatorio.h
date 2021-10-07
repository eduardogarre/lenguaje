#pragma once

#define ALEATORIO_MAX 0x7fff

// Siembra el generador de números aleatorios con un entero
void saleatorio(unsigned int const semilla);

// Devuelve un natural pseudoaleatorio en el rango [0, 32767].
int aleatorio();
