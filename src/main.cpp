#include "Model/RubiksCubeBitwise.hpp"
#include "View/TerminalView.cpp"
#include <iostream>
#include <vector>

int main() {
  cube::RubiksCubeBitwise cube;

  cube.move(cube::RubiksCube::MOVE::F);
  cube.move(cube::RubiksCube::MOVE::U);
  cube.move(cube::RubiksCube::MOVE::D);
  cube.move(cube::RubiksCube::MOVE::L);
  cube.move(cube::RubiksCube::MOVE::R);
  cube.move(cube::RubiksCube::MOVE::B);
  cube.move(cube::RubiksCube::MOVE::BPRIME);
  cube.move(cube::RubiksCube::MOVE::RPRIME);
  cube.move(cube::RubiksCube::MOVE::LPRIME);
  cube.move(cube::RubiksCube::MOVE::DPRIME);
  cube.move(cube::RubiksCube::MOVE::UPRIME);
  cube.move(cube::RubiksCube::MOVE::FPRIME);

  std::vector<std::vector<int>> matrix;

  for (int i = 0; i < 6; i++) {
    std::vector<int> face;
    for (int j = 0; j < 8; j++) {
      face.push_back((int)cube.cube[i][j]);
    }
    matrix.push_back(face);
  }

  try {
    CubeViewer viewer(matrix);
    viewer.display();
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}