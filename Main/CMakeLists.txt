project(Yet-Another-Raytracer)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
        *.c
        *.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
        *.h
        *.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC YetAnotherMathLib)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res)