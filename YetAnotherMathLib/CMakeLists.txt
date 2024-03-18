# Add source files
file(GLOB_RECURSE SOURCE_FILES
	 *.c
	 *.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
	 *.h
	 *.hpp)

# Set the project name
project(YetAnotherMathLib)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} -static-libstdc++)
else()
	target_link_libraries(${PROJECT_NAME} stdc++)
	target_link_libraries(${PROJECT_NAME} -lm)
endif()
