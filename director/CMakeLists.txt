﻿# SPDX-License-Identifier: MPL-2.0-no-copyleft-exception
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v.
# 2.0. If a copy of the MPL was not distributed with this file, You can obtain one
# at http://mozilla.org/MPL/2.0/.
#
# This Source Code Form is "Incompatible With Secondary Licenses", as defined by
# the Mozilla Public License, v. 2.0.
#
# Copyright © 2021 Eduardo Garre Muñoz

cmake_minimum_required(VERSION 3.14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# set the project name
project(director VERSION 0.1)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "He encontrado LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Usaré el LLVMConfig.cmake que he encontrado en: ${LLVM_DIR}")

# file(GLOB CODIGO_DIRECTOR CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")
file(GLOB_RECURSE CODIGO_DIRECTOR CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# añade el ejecutable
add_executable(director ${CODIGO_DIRECTOR})

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /utf-8")
  set_target_properties(director PROPERTIES

    # Expande automáticamente los comodines y caracteres especiales de la
    # línea de comandos de Windows
    LINK_FLAGS "setargv.obj"
  )
elseif(CMAKE_COMPILER_IS_GNUC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

set(componentes_llvm aarch64asmparser aarch64codegen aarch64desc aarch64disassembler aarch64info aarch64utils aggressiveinstcombine analysis armasmparser armcodegen armdesc armdisassembler arminfo armutils asmparser asmprinter binaryformat bitreader bitstreamreader bitwriter cfguard codegen core coroutines coverage debuginfocodeview debuginfodwarf debuginfogsym debuginfomsf debuginfopdb demangle dlltooldriver dwarflinker extensions filecheck frontendopenacc frontendopenmp fuzzmutate globalisel instcombine instrumentation interfacestub interpreter ipo irreader libdriver lineeditor linker lto mc mca mcdisassembler mcparser mirparser native nativecodegen objcarcopts object objectyaml option orcjit orcshared orctargetprocess passes profiledata remarks runtimedyld scalaropts selectiondag support symbolize tablegen target textapi transformutils vectorize webassemblyasmparser webassemblycodegen webassemblydesc webassemblydisassembler webassemblyinfo webassemblyutils windowsmanifest x86asmparser x86codegen x86desc x86disassembler x86info xray)
llvm_map_components_to_libnames(bibliotecas_llvm ${componentes_llvm})

# Enlazo el ejecutable "director" con las bibliotecas "lenguaje" y "docopt"
target_link_libraries(director LINK_PUBLIC lenguaje docopt ${bibliotecas_llvm})

set_target_properties(director PROPERTIES
  OUTPUT_NAME "ñ" # Establezco el nombre final del ejecutable
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "../../proyecto/"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "../../proyecto/"
  RUNTIME_OUTPUT_DIRECTORY "../../proyecto/"
)