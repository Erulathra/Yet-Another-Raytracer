cmake_minimum_required (VERSION 3.5)

set(CXX_STANDARD 23)

project(S1NU5_Graphics)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(Lib)
add_subdirectory(Main)

# ---- Dependencies ----
add_subdirectory(thirdparty)
