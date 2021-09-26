# Representación de literales en el árbol de sintaxis

- `(Literal) cadena:"DATO" tipo:TIPO_SIMPLE`

- `(Literal) cadena:"" tipo:TIPO_COMPUESTO`
  - `(Literal)0 cadena:"DATO" tipo:TIPO_SIMPLE`
  - `(Literal)1 cadena:"DATO" tipo:TIPO_SIMPLE`
  - `(Literal)2 cadena:"" tipo:TIPO_COMPUESTO`
    - `(Literal)20 cadena:"DATO" tipo:TIPO_SIMPLE`
    - `(Literal)21 cadena:"DATO" tipo:TIPO_SIMPLE`
  - `(Literal)3 cadena:"DATO" tipo:TIPO_SIMPLE`
  - `(Literal)4 cadena:"DATO" tipo:TIPO_SIMPLE`
  - `...`

## Ejemplos

---

Nada

- `(Literal) cadena:"nulo" tipo:TIPO_NADA`

Booleano

- `(Literal) cadena:"cierto|falso" tipo:TIPO_BOOLEANO`

Natural de 8 bits

- `(Literal) cadena:"DATO" tipo:TIPO_NATURAL_8`

Entero de 16 bits

- `(Literal) cadena:"DATO" tipo:TIPO_ENTERO_16`

Real de 32 bits

- `(Literal) cadena:"DATO" tipo:TIPO_REAL_32`

Puntero a Booleano

- `(Literal) cadena:"" tipo=TIPO_PUNTERO`
  - `(Literal)0 cadena:"" tipo=TIPO_BOOLEANO`

Vector de 4 enteros de 32 bits

- `(Literal) cadena:"" tipo=TIPO_VECTOR`
  - `(Literal)0 cadena:"DATO" tipo=TIPO_ENTERO_32`
  - `(Literal)1 cadena:"DATO" tipo=TIPO_ENTERO_32`
  - `(Literal)2 cadena:"DATO" tipo=TIPO_ENTERO_32`
  - `(Literal)3 cadena:"DATO" tipo=TIPO_ENTERO_32`

Estructura de entero de 16, booleano y real de 64

- `(Literal) cadena:"nombre_estructura" tipo=TIPO_ESTRUCTURA`
  - `(Literal)0 cadena:"DATO" tipo=TIPO_ENTERO_16`
  - `(Literal)1 cadena:"DATO" tipo=TIPO_BOOLEANO`
  - `(Literal)2 cadena:"DATO" tipo=TIPO_REAL_64`

Clase de natural de 64 y real de 32

- `(Literal) cadena:"nombre_clase" tipo=TIPO_CLASE`
  - `(Literal)0 cadena:"DATO" tipo=TIPO_NATURAL_64`
  - `(Literal)1 cadena:"DATO" tipo=TIPO_REAL_32`

Unión de booleano, natural de 16 y real de 64

- `(Literal) cadena:"" tipo=TIPO_UNIÓN`
  - `(Literal)0 cadena:"" tipo=TIPO_BOOLEANO`
  - `(Literal)1 cadena:"" tipo=TIPO_NATURAL_16`
  - `(Literal)2 cadena:"" tipo=TIPO_REAL_64`

Puntero a vector de 3 naturales de 16 bits

- `(Literal) cadena:"" tipo=TIPO_PUNTERO`
  - `(Literal)0 cadena:"" tipo=TIPO_VECTOR`
    - `(Literal)00 cadena:"DATO" tipo=TIPO_NATURAL_16`
    - `(Literal)01 cadena:"DATO" tipo=TIPO_NATURAL_16`
    - `(Literal)02 cadena:"DATO" tipo=TIPO_NATURAL_16`

Puntero a estructura de un natural de 16 bits y un real de 64

- `(Literal) cadena:"" tipo=TIPO_PUNTERO`
  - `(Literal)0 cadena:"nombre_estructura" tipo=TIPO_ESTRUCTURA`
    - `(Literal)00 cadena:"DATO" tipo=TIPO_NATURAL_16`
    - `(Literal)01 cadena:"DATO" tipo=TIPO_REAL_64`
