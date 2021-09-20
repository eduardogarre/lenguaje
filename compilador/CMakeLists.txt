cmake_minimum_required(VERSION 3.14)

set(CMAKE_BUILD_TYPE Release)

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

set(componentes_llvm aggressiveinstcombine analysis asmparser asmprinter binaryformat bitreader bitstreamreader bitwriter cfguard codegen core coroutines coverage debuginfocodeview debuginfodwarf debuginfogsym debuginfomsf debuginfopdb demangle dlltooldriver dwarflinker extensions filecheck frontendopenacc frontendopenmp fuzzmutate globalisel instcombine instrumentation interfacestub interpreter ipo irreader libdriver lineeditor linker lto mc mca mcdisassembler mcparser mirparser native nativecodegen objcarcopts object objectyaml option orcjit orcshared orctargetprocess passes profiledata remarks runtimedyld scalaropts selectiondag support symbolize tablegen target textapi transformutils vectorize windowsmanifest x86asmparser x86codegen x86desc x86disassembler x86info xray)
llvm_map_components_to_libnames(bibliotecas_llvm ${componentes_llvm})

# enlaza el ejecutable "compilador" con las bibliotecas "lenguaje" y "docopt_s"
target_link_libraries(compilador LINK_PUBLIC lenguaje docopt_s ${bibliotecas_llvm})

set_target_properties(compilador PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY  "../../proyecto/"
)