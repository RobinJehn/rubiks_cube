#include "TerminalView.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

namespace cube {
CubeViewer::CubeViewer(const std::vector<std::vector<int>> &matrix) {
  if (matrix.size() != 6 || !std::all_of(matrix.begin(), matrix.end(),
                                         [](const std::vector<int> &row) {
                                           return row.size() == 8;
                                         })) {
    throw std::invalid_argument("Matrix must be 6x8.");
  }
  this->matrix = matrix;
}

void CubeViewer::display() const {
  const std::vector<int> &top = matrix[0];

  std::cout << "      " << top[0] << ' ' << top[1] << ' ' << top[2] << '\n';
  std::cout << "      " << top[7] << "   " << top[3] << '\n';
  std::cout << "      " << top[6] << ' ' << top[5] << ' ' << top[4] << '\n';

  for (int j = 0; j < 9; ++j) {
    int face = (int)j / 3 + 1;
    int idx = j % 3;
    std::cout << matrix[face][idx] << ' ';
  }

  std::cout << "\n"
            << matrix[1][7] << "   " << matrix[1][3] << " " << matrix[2][7]
            << "   " << matrix[2][3] << " " << matrix[3][7] << "   "
            << matrix[3][3] << '\n';

  for (int j = 0; j < 9; ++j) {
    int face = (int)j / 3 + 1;
    int idx = 6 - j % 3;
    std::cout << matrix[face][idx] << ' ';
  }

  const std::vector<int> &b_bottom = matrix[4];
  std::cout << "\n      " << b_bottom[0] << ' ' << b_bottom[1] << ' '
            << b_bottom[2] << '\n';
  std::cout << "      " << b_bottom[7] << "   " << b_bottom[3] << '\n';
  std::cout << "      " << b_bottom[6] << ' ' << b_bottom[5] << ' '
            << b_bottom[4] << '\n';

  const std::vector<int> &bottom = matrix[5];
  std::cout << "      " << bottom[0] << ' ' << bottom[1] << ' ' << bottom[2]
            << '\n';
  std::cout << "      " << bottom[7] << "   " << bottom[3] << '\n';
  std::cout << "      " << bottom[6] << ' ' << bottom[5] << ' ' << bottom[4]
            << '\n';
}
} // namespace cube