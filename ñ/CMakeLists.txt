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

llvm_map_components_to_libnames(llvm_libs support core irreader)

# enlaza el ejecutable "prueballvm" con la biblioteca "lenguaje"
target_link_libraries(lenguaje LINK_PUBLIC ${llvm_libs})

# make sure the compiler can find include files for our library
# from other projects who link to us
#target_include_directories(ñ PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(lenguaje PUBLIC "${CMAKE_SOURCE_DIR}")

set_target_properties(lenguaje PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY  "../../proyecto/"
)