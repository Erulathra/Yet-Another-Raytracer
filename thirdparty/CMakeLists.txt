# CPM - package manager
include(CPM)

CPMAddPackage("gh:gabime/spdlog@1.13.0")

add_library(STB STB/stb_image.h)
target_include_directories(STB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/STB)
set_target_properties(STB PROPERTIES LINKER_LANGUAGE CXX)
