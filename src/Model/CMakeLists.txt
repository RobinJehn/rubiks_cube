cmake_minimum_required(VERSION 3.15)
project(rubiks_cube_model)
set(CMAKE_CXX_STANDARD 20)

set(MODEL_SRCS RubiksCube.cpp RubiksCubeBitwise.cpp)
add_library(${PROJECT_NAME} STATIC ${MODEL_SRCS})

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
