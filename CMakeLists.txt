# SPDX-License-Identifier: MPL-2.0-no-copyleft-exception
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
project(lenguaje VERSION 0.1)

add_subdirectory(ñ)
add_subdirectory(director)

message("MENSAJE :: Configuro algunas flags del compilador")
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /utf-8")
elseif(CMAKE_COMPILER_IS_GNUC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
endif()

message("MENSAJE :: Configurando submódulos")
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Comprueba los submódulos durante la construcción" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Actualizando submódulo")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init falló con el siguiente resultado ${GIT_SUBMOD_RESULT}. Restaura los submódulos haciendo un checkout.")
        endif()
    endif()
endif()

message("MENSAJE :: Comprobando existencia de docopt.cpp")
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/docopt.cpp/CMakeLists.txt")
    message(FATAL_ERROR "¡No se han descargado los submódulos! GIT_SUBMODULE estaba desactivado o falló. Por favor, actualiza los submódulos y prueba otra vez.")
else()
    message("MENSAJE :: Añado docopt.cpp")
    set(WITH_TESTS "Build tests." OFF)
    set(WITH_EXAMPLE "Build example." OFF)
    set(USE_BOOST_REGEX "Replace std::regex with Boost.Regex" OFF)
    add_subdirectory(docopt.cpp)
endif()