# Representación de tipos en el árbol de sintaxis

- `(Tipo) tipo:TIPO_SIMPLE`

- `(Tipo) tipo:TIPO_COMPUESTO`
  - `(Tipo)0 tipo:TIPO_SIMPLE`
  - `(Tipo)1 tipo:TIPO_SIMPLE`
  - `(Tipo)2 tipo:TIPO_COMPUESTO`
    - `(Tipo)20 tipo:TIPO_SIMPLE`
    - `(Tipo)21 tipo:TIPO_SIMPLE`
  - `(Tipo)3 tipo:TIPO_SIMPLE`
  - `(Tipo)4 tipo:TIPO_SIMPLE`
  - `...`

## Referencias

---

`TIPO_SIMPLE`

- Nada
- Booleano
- Natural ( 8 | 16 | 32 | 64 )
- Entero ( 8 | 16 | 32 | 64 )
- Real ( 32 | 64 )

`TIPO_COMPUESTO`

- Puntero
- Serie
- Estructura
- Clase
- Unión

## Ejemplos

---

Nada

- `(Tipo) tipo:TIPO_NADA`

Booleano

- `(Tipo) tipo:TIPO_BOOLEANO`

Natural de 8 bits

- `(Tipo) tipo:TIPO_NATURAL_8`

Entero de 16 bits

- `(Tipo) tipo:TIPO_ENTERO_16`

Real de 32 bits

- `(Tipo) tipo:TIPO_REAL_32`

Puntero a Booleano

- `(Tipo) tipo=TIPO_PUNTERO`
  - `(Tipo)0 tipo=TIPO_BOOLEANO`

Serie de 4 enteros de 32 bits

- `(Tipo) tipo=TIPO_SERIE`
  - `(Tipo)0 tipo=TIPO_ENTERO_32`
  - `(Tipo)1 tipo=TIPO_ENTERO_32`
  - `(Tipo)2 tipo=TIPO_ENTERO_32`
  - `(Tipo)3 tipo=TIPO_ENTERO_32`

Estructura de entero de 16, booleano y real de 64

- `(Tipo) tipo=TIPO_ESTRUCTURA`
  - `(Tipo)0 tipo=TIPO_ENTERO_16`
  - `(Tipo)1 tipo=TIPO_BOOLEANO`
  - `(Tipo)2 tipo=TIPO_REAL_64`

Clase de natural de 64 y real de 32

- `(Tipo) tipo=TIPO_CLASE`
  - `(Tipo)0 tipo=TIPO_NATURAL_64`
  - `(Tipo)1 tipo=TIPO_REAL_32`

Unión de booleano, natural de 16 y real de 64

- `(Tipo) tipo=TIPO_UNIÓN`
  - `(Tipo)0 tipo=TIPO_BOOLEANO`
  - `(Tipo)1 tipo=TIPO_NATURAL_16`
  - `(Tipo)2 tipo=TIPO_REAL_64`

Puntero a serie de 3 naturales de 16 bits

- `(Tipo) tipo=TIPO_PUNTERO`
  - `(Tipo)0 tipo=TIPO_SERIE`
    - `(Tipo)00 tipo=TIPO_NATURAL_16`
    - `(Tipo)01 tipo=TIPO_NATURAL_16`
    - `(Tipo)02 tipo=TIPO_NATURAL_16`

Puntero a estructura de un natural de 16 bits y un real de 64

- `(Tipo) tipo=TIPO_PUNTERO`
  - `(Tipo)0 tipo=TIPO_ESTRUCTURA`
    - `(Tipo)00 tipo=TIPO_NATURAL_16`
    - `(Tipo)01 tipo=TIPO_REAL_64`
