cmake_minimum_required(VERSION 3.15)
project(RubiksCube LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(
    -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wno-unused-function
)

set(RUBIKS_CUBE_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

set(MODEL_DIR ${RUBIKS_CUBE_SRC_DIR}/Model)
set(MODEL_SRCS ${MODEL_DIR}/RubiksCube.cpp ${MODEL_DIR}/RubiksCubeBitwise.cpp)

set(VIEW_DIR ${RUBIKS_CUBE_SRC_DIR}/View)
set(VIEW_SRCS ${VIEW_DIR}/TerminalView.cpp)

add_executable(${PROJECT_NAME} src/main.cpp ${MODEL_SRCS})
