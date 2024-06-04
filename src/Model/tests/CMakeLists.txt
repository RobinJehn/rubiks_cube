cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
project(move_tests)

# Download and unpack googletest at configure time
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} unittest_move_generator.cpp ../../View/utils.cpp ../../View/TerminalView.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/)
target_link_libraries(${PROJECT_NAME} gtest_main rubiks_cube_model)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})