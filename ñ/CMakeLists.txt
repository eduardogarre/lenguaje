cmake_minimum_required(VERSION 3.12)

# set the project name
project(lenguaje VERSION 0.1)

#file(GLOB CODIGO_LENGUAJE CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")
file(GLOB_RECURSE CODIGO_LENGUAJE CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")

# add the executable
add_library(lenguaje ${CODIGO_LENGUAJE})

# make sure the compiler can find include files for our library
# from other projects who link to us
#target_include_directories(lenguaje PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(lenguaje PUBLIC "${CMAKE_SOURCE_DIR}")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /utf-8")
elseif(CMAKE_COMPILER_IS_GNUC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

set_target_properties(lenguaje PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY  "../../proyecto/"
)