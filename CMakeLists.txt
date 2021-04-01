cmake_minimum_required(VERSION 3.12)

# set the project name
project(compilador VERSION 0.1)

#file(GLOB CODIGO_COMPILADOR CONFIGURE_DEPENDS "compilador/*.hpp" "compilador/*.cpp")
file(GLOB_RECURSE CODIGO_COMPILADOR CONFIGURE_DEPENDS "compilador/*.hpp" "compilador/*.cpp")

# add the executable
add_executable(compilador ${CODIGO_COMPILADOR})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /utf-8")
elseif(CMAKE_COMPILER_IS_GNUC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
endif()

set_target_properties(compilador PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG  "../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY  "../proyecto/"
)