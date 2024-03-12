# Add source files
file(GLOB_RECURSE SOURCE_FILES
	 *.c
	 *.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
	 *.h
	 *.hpp)

# Set the project name
project(Lib)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES}
		src/Camera.cpp
		include/Camera.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
