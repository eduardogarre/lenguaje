# Representación de valores en el árbol de sintaxis

- `(Valor) unión:DATO tipo:TIPO_SIMPLE`

- `(Valor) unión:0 tipo:TIPO_COMPUESTO`
  - `(Valor)0 unión:DATO tipo:TIPO_SIMPLE`
  - `(Valor)1 unión:DATO tipo:TIPO_SIMPLE`
  - `(Valor)2 unión:0 tipo:TIPO_COMPUESTO`
    - `(Valor)20 unión:DATO tipo:TIPO_SIMPLE`
    - `(Valor)21 unión:DATO tipo:TIPO_SIMPLE`
  - `(Valor)3 unión:DATO tipo:TIPO_SIMPLE`
  - `(Valor)4 unión:DATO tipo:TIPO_SIMPLE`
  - `...`

## Ejemplos

---

Nada

- `(Valor) unión:0 tipo:TIPO_NADA`

Booleano

- `(Valor) unión:DATO tipo:TIPO_BOOLEANO`

Natural de 8 bits

- `(Valor) unión:DATO tipo:TIPO_NATURAL_8`

Entero de 16 bits

- `(Valor) unión:DATO tipo:TIPO_ENTERO_16`

Real de 32 bits

- `(Valor) unión:DATO tipo:TIPO_REAL_32`

Puntero a Booleano

- `(Valor) unión:DATO tipo=TIPO_PUNTERO`
  - `(Valor)0 unión:0 tipo=TIPO_BOOLEANO`

Vector de 4 enteros de 32 bits

- `(Valor) unión:0 tipo=TIPO_VECTOR`
  - `(Valor)0 unión:DATO tipo=TIPO_ENTERO_32`
  - `(Valor)1 unión:DATO tipo=TIPO_ENTERO_32`
  - `(Valor)2 unión:DATO tipo=TIPO_ENTERO_32`
  - `(Valor)3 unión:DATO tipo=TIPO_ENTERO_32`

Estructura de entero de 16, booleano y real de 64

- `(Valor) unión:0 tipo=TIPO_ESTRUCTURA`
  - `(Valor)0 unión:DATO tipo=TIPO_ENTERO_16`
  - `(Valor)1 unión:DATO tipo=TIPO_BOOLEANO`
  - `(Valor)2 unión:DATO tipo=TIPO_REAL_64`

Clase de natural de 64 y real de 32

- `(Valor) unión:0 tipo=TIPO_CLASE`
  - `(Valor)0 unión:DATO tipo=TIPO_NATURAL_64`
  - `(Valor)1 unión:DATO tipo=TIPO_REAL_32`

Unión de booleano, natural de 16 y real de 64

- `(Valor) unión:DATO tipo=TIPO_UNIÓN`
  - `(Valor)0 unión:0 tipo=TIPO_BOOLEANO`
  - `(Valor)1 unión:0 tipo=TIPO_NATURAL_16`
  - `(Valor)2 unión:0 tipo=TIPO_REAL_64`

Puntero a vector de 3 naturales de 16 bits

- `(Valor) unión:DATO tipo=TIPO_PUNTERO`
  - `(Valor)0 unión:0 tipo=TIPO_VECTOR`
    - `(Valor)00 unión:DATO tipo=TIPO_NATURAL_16`
    - `(Valor)01 unión:DATO tipo=TIPO_NATURAL_16`
    - `(Valor)02 unión:DATO tipo=TIPO_NATURAL_16`

Puntero a estructura de un natural de 16 bits y un real de 64

- `(Valor) unión:DATO tipo=TIPO_PUNTERO`
  - `(Valor)0 unión:0 tipo=TIPO_ESTRUCTURA`
    - `(Valor)00 unión:DATO tipo=TIPO_NATURAL_16`
    - `(Valor)01 unión:DATO tipo=TIPO_REAL_64`
