#include "Model/RubiksCubeBitwise.hpp"
#include <vector>

namespace cube {

std::vector<std::vector<int>> colorToIntMatrix(
    const std::vector<std::vector<RubiksCube::COLOR>> &color_matrix) {
  std::vector<std::vector<int>> matrix;
  // Convert the matrix to a vector of vectors of integers.
  for (auto &row : color_matrix) {
    std::vector<int> int_row;
    for (auto &color : row) {
      int_row.push_back(static_cast<int>(color));
    }
    matrix.push_back(int_row);
  }
  return matrix;
};

std::vector<std::vector<int>> getIntMatrix(const RubiksCubeBitwise &cube) {
  std::vector<std::vector<RubiksCube::COLOR>> color_matrix = cube.getMatrix();
  return colorToIntMatrix(color_matrix);
}

} // namespace cube