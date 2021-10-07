#define ALEATORIO_MAX 0x7fff

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
