cmake_minimum_required(VERSION 3.14)

# set the project name
project(pruebas VERSION 0.1)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/23ef29555ef4789f555f1ba8c51b4c52975f0907.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
file(GLOB_RECURSE CODIGO_PRUEBAS CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")
set(CABECERAS_GTEST "../obra/_deps/googletest-src/googletest/include/")

add_executable(pruebas ${CODIGO_PRUEBAS})

target_include_directories(pruebas PRIVATE ${CABECERAS_GTEST})
target_link_libraries(pruebas gtest_main lenguaje)

add_test(NAME pruebas COMMAND pruebas)

set(DIRECTIVA_PRUEBAS EVALUANDO_PRUEBAS)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /utf-8 /D${DIRECTIVA_PRUEBAS}=1")
elseif(CMAKE_COMPILER_IS_GNUC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -D${DIRECTIVA_PRUEBAS}=1")
endif()

set_target_properties(pruebas PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "../../proyecto/"
                      RUNTIME_OUTPUT_DIRECTORY  "../../proyecto/"
)