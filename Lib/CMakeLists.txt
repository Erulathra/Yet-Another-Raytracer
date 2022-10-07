# Set the project name
project(Lib)

add_library(${PROJECT_NAME} src/Vector3.cpp include/Vector3.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
