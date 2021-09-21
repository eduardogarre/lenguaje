cmake_minimum_required(VERSION 3.14)

set(CMAKE_BUILD_TYPE "Release")
set(BUILD_SHARED_LIBS OFF)

# set the project name
project(biblioteca VERSION 0.1)

#file(GLOB CODIGO_BIBLIOTECA CONFIGURE_DEPENDS "./*.hpp" "./*.cpp")
file(GLOB_RECURSE CODIGO_BIBLIOTECA CONFIGURE_DEPENDS "./*.h" "./*.c")

# añade la biblioteca
add_library(biblioteca STATIC ${CODIGO_BIBLIOTECA})

#target_link_libraries(biblioteca PUBLIC "-static")

if(MSVC)
    foreach(flag_var
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
        if(${flag_var} MATCHES "/RTC")
            string(REGEX REPLACE "[/|-]RTC(su|[1su])" "" ${flag_var} "${${flag_var}}")
        endif()
    endforeach(flag_var)
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} /X /std:c17 /utf-8")
elseif(CMAKE_COMPILER_IS_GNUC)
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -nostdinc -nostdinc++ -std=c17")
endif()

set_target_properties(biblioteca PROPERTIES
                        ARCHIVE_OUTPUT_DIRECTORY  "../proyecto/"
                        LIBRARY_OUTPUT_DIRECTORY  "../proyecto/"
                        RUNTIME_OUTPUT_DIRECTORY  "../proyecto/"
)