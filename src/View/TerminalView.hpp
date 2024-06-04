#pragma once
#include <vector>

namespace cube {
class CubeViewer {
public:
  CubeViewer(const std::vector<std::vector<int>> &matrix);
  void display() const;

private:
  std::vector<std::vector<int>> matrix;
};

} // namespace cube
