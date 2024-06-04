cmake_minimum_required(VERSION 3.15)
project(RubiksCube LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(
    -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wno-unused-function
)

set(BUILD_TESTING ON "Enable tests")

if(BUILD_TESTING)
    enable_testing()
endif()

set(RUBIKS_CUBE_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

set(VIEW_DIR ${RUBIKS_CUBE_SRC_DIR}/View)
set(VIEW_SRCS ${VIEW_DIR}/TerminalView.cpp
    ${VIEW_DIR}/utils.cpp)

add_executable(${PROJECT_NAME} src/main.cpp ${MODEL_SRCS} ${VIEW_SRCS})

add_subdirectory(${RUBIKS_CUBE_SRC_DIR}/Model)

target_include_directories(${PROJECT_NAME} PRIVATE ${RUBIKS_CUBE_SRC_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE rubiks_cube_model)
