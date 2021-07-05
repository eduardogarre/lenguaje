cmake_minimum_required(VERSION 3.14)

# set the project name
project(lenguaje VERSION 0.1)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "He encontrado LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Usaré el LLVMConfig.cmake que he encontrado en: ${LLVM_DIR}")

#file(GLOB CODIGO_LENGUAJE CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")
file(GLOB_RECURSE CODIGO_LENGUAJE CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /utf-8")
elseif(CMAKE_COMPILER_IS_GNUC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# add the executable
add_library(lenguaje ${CODIGO_LENGUAJE})

#set(componentes_llvm aggressiveinstcombine analysis asmparser asmprinter binaryformat bitreader bitstreamreader bitwriter cfguard codegen core coroutines coverage debuginfocodeview debuginfodwarf debuginfogsym debuginfomsf debuginfopdb demangle dlltooldriver dwarflinker engine executionengine extensions filecheck frontendopenacc frontendopenmp fuzzmutate globalisel instcombine instrumentation interfacestub interpreter ipo irreader libdriver lineeditor linker lto mc mca mcdisassembler mcparser mirparser native nativecodegen objcarcopts object objectyaml option orcshared orctargetprocess passes profiledata remarks runtimedyld scalaropts selectiondag support symbolize tablegen target textapi transformutils vectorize windowsmanifest x86asmparser x86codegen x86desc x86disassembler x86info xray)
#message(STATUS "${componentes_llvm}")
#string(REPLACE " " ";" lista_componentes_llvm ${componentes_llvm})
#message(STATUS "${lista_componentes_llvm}")
#llvm_map_components_to_libnames(bibliotecas_llvm ${componentes_llvm})
#message(STATUS "${bibliotecas_llvm}")
#message(STATUS "")
execute_process(COMMAND llvm-config --libdir OUTPUT_VARIABLE ruta_bibliotecas_llvm OUTPUT_STRIP_TRAILING_WHITESPACE)
file(GLOB bibliotecas_llvm CONFIGURE_DEPENDS "${ruta_bibliotecas_llvm}/*.lib")
#message(STATUS "${bibliotecas_llvm}")

# enlaza el ejecutable "prueballvm" con la biblioteca "lenguaje"
target_link_libraries(lenguaje LINK_PUBLIC ${bibliotecas_llvm})

# make sure the compiler can find include files for our library
# from other projects who link to us
#target_include_directories(ñ PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(lenguaje PUBLIC "${CMAKE_SOURCE_DIR}")

set_target_properties(lenguaje PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY  "../../proyecto/"
)