# **Lenguaje Ñ**

Éste es el repositorio del **Lenguaje Ñ**. Contiene el compilador, la biblioteca estándar y documentación.

Puedes encontrar más información en la página del proyecto: http://lenguajeñ.com.

&nbsp;

# Construye el Lenguaje Ñ

El **Lenguaje Ñ** está escrito en `C++` usando el sistema de construcción [`CMake`](https://cmake.org/). Debes instalar `CMake` y un compilador de `C++` moderno para poder construir tanto las diferentes partes de **Ñ** como sus dependencias. Además, para obtener el código de los repositorios debes instalar [`git`](https://git-scm.com/).

&nbsp;

## **Construyendo en Windows**

### **Instala las dependencias**

Para construir el **Lenguaje Ñ** necesitarás las bibliotecas [`LLVM`](https://llvm.org/) y [`docopt.cpp`](https://github.com/docopt/docopt.cpp):

- **LLVM**

    En el momento actual, los binarios disponibles de **LLVM** para Windows no incluyen algunos módulos y subproyectos necesarios en **Ñ**, como por ejemplo `lld`. Por tanto, para construir el proyecto necesitarás construir tú mismo **LLVM** a partir de su código fuente. En la página oficial de **LLVM** puedes encontrar las instrucciones necesarias, pero un ejemplo rápido de cómo construir esta biblioteca sería:

    ```powerhell
    git clone --depth 1 --config core.autocrlf=false https://github.com/llvm/llvm-project.git llvm

    mkdir c:\llvm
    mkdir obra
    cd obra

    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=c:/llvm -DLLVM_TARGETS_TO_BUILD="all" -DLLVM_TARGET_ARCH="host" -DLLVM_BUILD_EXAMPLES=ON -DLLVM_BUILD_TOOLS=ON -DLLVM_ENABLE_THREADS=ON -DLLVM_INCLUDE_EXAMPLES=ON -DLLVM_INCLUDE_TOOLS=ON -DLLVM_OPTIMIZED_TABLEGEN=ON -DLLVM_PARALLEL_COMPILE_JOBS="16" -DLLVM_PARALLEL_LINK_JOBS="16" ..\llvm\llvm
    cmake --build . --parallel
    cmake --build . --target install
    ```

- **docopt.cpp**

    La biblioteca **docopt.cpp** está enteramente en inglés. Para disfrutar de una versión traducida al español empleo la bifurcación en [este repositorio](https://github.com/eduardogarre/docopt.cpp), que incluyo como un submódulo para facilitar su inclusión en el **Lenguaje Ñ**.

&nbsp;

### **Consigue el código de Ñ**

Una vez tengas preparadas todas las dependiencias, clona este repositorio para obtener el código de **Ñ**, en este caso dentro de una nueva carpeta llamada `./ñ`.

```powerhell
mkdir ñ
cd ñ
git clone --recurse-submodules https://github.com/eduardogarre/lenguaje .
```

&nbsp;

### **Estructura del repositorio**

El repositorio contiene **3 subproyectos**:
1) `director`, en la carpeta `director/`
1) `ñ`, en la carpeta `ñ/`
1) `biblioteca`, en la carpeta `biblioteca/`

El proyecto `ñ` es una biblioteca que contiene el código que analiza y compila o interpreta el lenguaje Ñ. Esta biblioteca puede ser incluida por otros proyectos para añadir soporte del lenguaje Ñ en ellos.

El proyecto `director` es un ejecutable que incluye la biblioteca `ñ` para, juntos, construir el compilador. Este proyecto es un ejemplo de cómo emplear la biblioteca `ñ` para incorporar soporte del lenguaje `ñ` en un proyecto.

El proyecto `biblioteca` contiene el código de la biblioteca estándar del lenguaje Ñ.

### **Construye el Lenguaje Ñ**
   
Componiendo los subproyectos descritos arriba, el repositorio construye **2 objetivos**
1) El `compilador de Ñ`, el ejecutable construido a partir de los proyectos `director` y `ñ`
1) La `biblioteca estándar de Ñ`, la biblioteca construida a partir del proyecto `biblioteca`

- **Compilador**

    Sus archivos principañes se encuentran en las carpetas `./director` y `./ñ`. Para construirlo da las siguientes órdenes:

    ```powershell
    mkdir obra
    mkdir proyecto
    cd obra
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build . --parallel 4
    cd ..
    ```

    Estas órdenes generarán un ejecutable `ñ.exe` dentro de la carpeta `./proyecto`.

- **Biblioteca estándar**

    Sus archivos principales se encuentran en la carpeta `./biblioteca`. Para construirlo da las siguientes órdenes:

    ```powershell
    mkdir obra
    cd obra
    cmake -DCMAKE_BUILD_TYPE=Release ../biblioteca
    cmake --build . --parallel 4
    cd ..
    ```

    Estas órdenes generarán una biblioteca `bibñ.lib` dentro de la carpeta `./proyecto`.

&nbsp;

### **Añade el Lenguaje Ñ a la ruta de archivos ejecutables**

#### &nbsp;&nbsp;PENDIENTE

&nbsp;

### **Pasa las pruebas**

Para comprobar que el proyecto se ha construido correctamente, usa el compilador en `./proyecto/ñ.exe` para construir el proyecto de prueba que se encuentra en la carpeta `./pruebas/`. Para ello, construye el proyecto de pruebas con la siguiente orden:

```powershell
.\proyecto\ñ.exe .\pruebas\*.ñ -s prueba
```

Esta orden compila todos los archivos `.ñ` presentes en la carpeta `pruebas/`, y como salida crea un archivo ejecutable llamado `prueba.exe`.

Tras ejecutar esa orden correctamente, el compilador `ñ.exe` debería crear un nuevo ejecutable `prueba.exe` en la carpeta actual. Para terminar, ejecuta `prueba.exe` y comprueba su salida. Cada prueba que se ejecute satisfactoriamente debería imprimir un punto y seguido en la consola. Algo parecido a esto:

```powershell
PS> .\prueba.exe
.............................................................................................
.............................................................................................
.........
PS> 
```

Si observas un resultado similar a éste, enhorabuena, has construido **Ñ** con éxito y funciona correctamente.

&nbsp;

## **Construyendo en Linux**

### &nbsp;&nbsp;PENDIENTE

&nbsp;

# Integración con VS Code

Estamos desarrollando una extensión para VS Code que integra el **Lenguaje Ñ** en **VS Code**. Puedes descargar la extensión en [este repositorio](https://github.com/eduardogarre/lenguaje_sintaxis_vscode).

&nbsp;

# Licencia

El **Lenguaje Ñ** se distribuye bajo la licencia [Mozilla Public License 2.0 (no copyleft exception)](https://www.mozilla.org/en-US/MPL/2.0/), con el siguiente código SPDX: [MPL-2.0-no-copyleft-exception](https://spdx.org/licenses/MPL-2.0-no-copyleft-exception.html).
