# This Source Code Form is subject to the terms of the Mozilla Public License, v.
# 2.0. If a copy of the MPL was not distributed with this file, You can obtain one
# at http://mozilla.org/MPL/2.0/.
# 
# This Source Code Form is "Incompatible With Secondary Licenses", as defined by
# the Mozilla Public License, v. 2.0.

cmake_minimum_required(VERSION 3.14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(BUILD_SHARED_LIBS OFF)

# set the project name
project(biblioteca VERSION 0.1)

#file(GLOB CODIGO_BIBLIOTECA CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")
file(GLOB_RECURSE CODIGO_BIBLIOTECA CONFIGURE_DEPENDS "./*.h" "./*.c")

# añade la biblioteca
add_library(biblioteca STATIC ${CODIGO_BIBLIOTECA})
#add_executable(biblioteca ${CODIGO_BIBLIOTECA})

#target_link_libraries(biblioteca PUBLIC "-static")

if(MSVC)
    foreach(flag_var
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/RTC")
            string(REGEX REPLACE "[/|-]RTC(su|[1su])" "" ${flag_var} "${${flag_var}}")
        endif()
    endforeach(flag_var)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /GS- /X /std:c17 /utf-8 /validate-charset")
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /GS- /std:c17 /utf-8 /validate-charset")
    set_target_properties(biblioteca PROPERTIES
        LINK_FLAGS "/entry:__lugar_de_inicio /subsystem:console /nodefaultlib"
        #LINK_FLAGS "/entry:__lugar_de_inicio /subsystem:console"
    )
    #target_link_libraries(biblioteca kernel32 libcmt ntdll)
elseif(CMAKE_COMPILER_IS_GNUC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdinc -nostdinc++ -std=c17")
endif()

if(WIN32)
    get_filename_component(ruta_enlazador "${CMAKE_LINKER}" DIRECTORY)
    find_program(LIB_EXE NAMES lib.exe HINTS ${ruta_enlazador})
    add_custom_target(biblioteca_estatica ALL COMMAND ${LIB_EXE} /out:bibñ.lib $<TARGET_FILE:biblioteca> kernel32.lib libcmt.lib ntdll.lib)
elseif(APPLE)
    add_custom_target(biblioteca_estatica ALL COMMAND ${CMAKE_AR} rc bibñ.a $<TARGET_FILE:biblioteca>)
elseif(UNIX)
    add_custom_target(biblioteca_estatica ALL COMMAND ${CMAKE_AR} rc bibñ.a $<TARGET_FILE:biblioteca>)
endif()

set_target_properties(biblioteca_estatica PROPERTIES
                        ARCHIVE_OUTPUT_DIRECTORY  "../proyecto/"
                        LIBRARY_OUTPUT_DIRECTORY  "../proyecto/"
                        RUNTIME_OUTPUT_DIRECTORY  "../proyecto/"
)