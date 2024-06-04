#include "Model/RubiksCubeBitwise.hpp"
#include "View/TerminalView.hpp"
#include "View/utils.hpp"
#include <gtest/gtest.h>

typedef cube::RubiksCube::COLOR COLOR;

TEST(RubiksCube, LMove) {
  cube::RubiksCubeBitwise cube;
  cube.move(cube::RubiksCube::MOVE::L);

  std::vector<std::vector<COLOR>> color_matrix = cube.getMatrix();

  std::vector<std::vector<COLOR>> expected_matrix = {
      {COLOR::GREEN, COLOR::WHITE, COLOR::WHITE, COLOR::WHITE, COLOR::WHITE,
       COLOR::WHITE, COLOR::GREEN, COLOR::GREEN},
      {COLOR::RED, COLOR::RED, COLOR::RED, COLOR::RED, COLOR::RED, COLOR::RED,
       COLOR::RED, COLOR::RED},
      {COLOR::WHITE, COLOR::BLUE, COLOR::BLUE, COLOR::BLUE, COLOR::BLUE,
       COLOR::BLUE, COLOR::WHITE, COLOR::WHITE},
      {COLOR::ORANGE, COLOR::ORANGE, COLOR::ORANGE, COLOR::ORANGE,
       COLOR::ORANGE, COLOR::ORANGE, COLOR::ORANGE, COLOR::ORANGE},
      {COLOR::BLUE, COLOR::YELLOW, COLOR::YELLOW, COLOR::YELLOW, COLOR::YELLOW,
       COLOR::YELLOW, COLOR::BLUE, COLOR::BLUE},
      {COLOR::YELLOW, COLOR::GREEN, COLOR::GREEN, COLOR::GREEN, COLOR::GREEN,
       COLOR::GREEN, COLOR::YELLOW, COLOR::YELLOW}};

  EXPECT_EQ(color_matrix, expected_matrix);
}
