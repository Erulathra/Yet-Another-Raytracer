# Set the project name
project(Lib)

add_library(${PROJECT_NAME} src/TVector3.cpp include/TVector3.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
