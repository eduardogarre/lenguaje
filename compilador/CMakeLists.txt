#This Source Code Form is subject to the terms of the Mozilla Public License, v.
#2.0. If a copy of the MPL was not distributed with this file, You can obtain one
#at http://mozilla.org/MPL/2.0/.
#
#This Source Code Form is "Incompatible With Secondary Licenses", as defined by
#the Mozilla Public License, v. 2.0.

cmake_minimum_required(VERSION 3.14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# set the project name
project(compilador VERSION 0.1)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "He encontrado LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Usaré el LLVMConfig.cmake que he encontrado en: ${LLVM_DIR}")

#file(GLOB CODIGO_COMPILADOR CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")
file(GLOB_RECURSE CODIGO_COMPILADOR CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# añade el ejecutable
add_executable(compilador ${CODIGO_COMPILADOR})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /utf-8")
    set_target_properties(compilador PROPERTIES
    # Expande automáticamente los comodines y caracteres especiales de la
    # línea de comandos de Windows
                                      LINK_FLAGS "/link setargv.obj"
    )
elseif(CMAKE_COMPILER_IS_GNUC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

set(componentes_llvm aarch64asmparser aarch64codegen aarch64desc aarch64disassembler aarch64info aarch64utils aggressiveinstcombine analysis armasmparser armcodegen armdesc armdisassembler arminfo armutils asmparser asmprinter binaryformat bitreader bitstreamreader bitwriter cfguard codegen core coroutines coverage debuginfocodeview debuginfodwarf debuginfogsym debuginfomsf debuginfopdb demangle dlltooldriver dwarflinker extensions filecheck frontendopenacc frontendopenmp fuzzmutate globalisel instcombine instrumentation interfacestub interpreter ipo irreader libdriver lineeditor linker lto mc mca mcdisassembler mcparser mirparser native nativecodegen objcarcopts object objectyaml option orcjit orcshared orctargetprocess passes profiledata remarks runtimedyld scalaropts selectiondag support symbolize tablegen target textapi transformutils vectorize webassemblyasmparser webassemblycodegen webassemblydesc webassemblydisassembler webassemblyinfo webassemblyutils windowsmanifest x86asmparser x86codegen x86desc x86disassembler x86info xray)
llvm_map_components_to_libnames(bibliotecas_llvm ${componentes_llvm})

execute_process(COMMAND llvm-config --prefix OUTPUT_VARIABLE carpeta_llvm OUTPUT_STRIP_TRAILING_WHITESPACE)

set(bibliotecas_lld "")

if(MSVC)
  set(bibliotecas_lld "${carpeta_llvm}/lib/lldCOFF.lib")
elseif(MINGW)
  set(bibliotecas_lld "${carpeta_llvm}/lib/lldMinGW.lib")
elseif(APPLE)
  set(bibliotecas_lld "${carpeta_llvm}/lib/lldMachO.lib" "${carpeta_llvm}/lib/lldMachO.lib")
elseif(UNIX)
  set(bibliotecas_lld "${carpeta_llvm}/lib/lldELF.lib")
endif()

set(bibliotecas_lld ${carpeta_llvm}/lib/lldCommon.lib ${carpeta_llvm}/lib/lldCore.lib ${carpeta_llvm}/lib/lldDriver.lib ${carpeta_llvm}/lib/lldReaderWriter.lib ${carpeta_llvm}/lib/lldWasm.lib ${carpeta_llvm}/lib/lldYAML.lib ${bibliotecas_lld})

  # enlaza el ejecutable "compilador" con las bibliotecas "lenguaje" y "docopt_s"
target_link_libraries(compilador LINK_PUBLIC lenguaje docopt_s ${bibliotecas_llvm} ${bibliotecas_lld})

set_target_properties(compilador PROPERTIES
                      OUTPUT_NAME "ñ"
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY  "../../proyecto/"
)