#include "Model/RubiksCubeBitwise.hpp"
#include <vector>

namespace cube {
class RubiksCubeBitwise;
std::vector<std::vector<int>> colorToIntMatrix(
    const std::vector<std::vector<RubiksCube::COLOR>> &color_matrix);

std::vector<std::vector<int>> getIntMatrix(const cube::RubiksCubeBitwise &cube);
} // namespace cube