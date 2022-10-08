cmake_minimum_required(VERSION 3.13)
project(Viewer
        VERSION 0.1.0
        LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(WARNING_COMPILER_OPTIONS /W3 /WX)
else()
    set(WARNING_COMPILER_OPTIONS -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers)
endif()

set(DEPENDS_DIR ${CMAKE_SOURCE_DIR}/depends)

find_package(Threads)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
    add_compile_options(-Wno-missing-field-initializers)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options ($<$<COMPILE_LANGUAGE:C>:-fcolor-diagnostics>)
    add_compile_options(-Wno-gnu-zero-variadic-macro-arguments)
    add_compile_options(-gdwarf-4)
    add_compile_options(-O1)
endif()

add_executable(viewer ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_compile_options(viewer PRIVATE ${WARNING_COMPILER_OPTIONS})
