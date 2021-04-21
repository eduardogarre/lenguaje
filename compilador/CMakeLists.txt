cmake_minimum_required(VERSION 3.14)

# set the project name
project(compilador VERSION 0.1)

#file(GLOB CODIGO_COMPILADOR CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")
file(GLOB_RECURSE CODIGO_COMPILADOR CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /utf-8")
elseif(CMAKE_COMPILER_IS_GNUC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

# add the executable
add_executable(compilador ${CODIGO_COMPILADOR})

# enlaza el ejecutable "compilador" con la biblioteca "lenguaje"
target_link_libraries(compilador LINK_PUBLIC lenguaje)

set_target_properties(compilador PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY  "../../proyecto/"
)