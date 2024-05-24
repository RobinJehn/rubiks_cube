#include "RubiksCubeBitwise.hpp"
#include <algorithm>

namespace cube {

RubiksCubeBitwise::RubiksCubeBitwise() {
  // Initialize the cube to the solved state.
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      cube[i][j] = static_cast<COLOR>(i);
    }
  }
}

void RubiksCubeBitwise::rotateEdges(FACE f, ROTATION rotation) {
  std::array<FACE_EDGE, 4> edges = edgeMap[f];

  switch (rotation) {
  case ROTATION::CLOCKWISE: {
    uint16_t edge3 =
        *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[3] / 4)]
                                [(unsigned)edges[3] % 4 * 2];
    COLOR corner3 = this->cube[(unsigned)((unsigned)edges[3] / 4)]
                              [((unsigned)edges[3] % 4 * 2 + 2) % 8];

    for (int i = 3; i > 0; i--) {
      *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[i] / 4)]
                              [(unsigned)edges[i] % 4 * 2] =
          *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[i - 1] / 4)]
                                  [(unsigned)edges[i - 1] % 4 * 2];

      this->cube[(unsigned)((unsigned)edges[i] / 4)]
                [((unsigned)edges[i] % 4 * 2 + 2) % 8] =
          this->cube[(unsigned)((unsigned)edges[i - 1] / 4)]
                    [((unsigned)edges[i - 1] % 4 * 2 + 2) % 8];
    }

    *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[0] / 4)]
                            [(unsigned)edges[0] % 4 * 2] = edge3;
    this->cube[(unsigned)((unsigned)edges[0] / 4)]
              [((unsigned)edges[0] % 4 * 2 + 2) % 8] = corner3;
    break;
    // We would like to move 3 bytes at a time, but the x86-64 architecture only
    // allows powers of 2.  So we move 2 bytes at a time, and then move the last
    // one seperately.

    // There is 24 different edge sides

    // FACE_EDGE::LR, FACE_EDGE::UB, FACE_EDGE::RL, FACE_EDGE::DT
  }
  case ROTATION::COUNTERCLOCKWISE: {
    uint16_t edge0 =
        *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[0] / 4)]
                                [(unsigned)edges[0] % 4 * 2];
    COLOR corner0 = this->cube[(unsigned)((unsigned)edges[0] / 4)]
                              [((unsigned)edges[0] % 4 * 2 + 2) % 8];

    for (int i = 0; i < 3; i++) {
      *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[i] / 4)]
                              [(unsigned)edges[i] % 4 * 2] =
          *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[i + 1] / 4)]
                                  [(unsigned)edges[i + 1] % 4 * 2];

      this->cube[(unsigned)((unsigned)edges[i] / 4)]
                [((unsigned)edges[i] % 4 * 2 + 2) % 8] =
          this->cube[(unsigned)((unsigned)edges[i + 1] / 4)]
                    [((unsigned)edges[i + 1] % 4 * 2 + 2) % 8];
    }

    *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[3] / 4)]
                            [(unsigned)edges[3] % 4 * 2] = edge0;
    this->cube[(unsigned)((unsigned)edges[3] / 4)]
              [((unsigned)edges[3] % 4 * 2 + 2) % 8] = corner0;

    break;
  }
  case ROTATION::CLOCKWISE2: {
    std::swap(*(uint16_t *)&this->cube[(unsigned)((unsigned)edges[0] / 4)]
                                      [(unsigned)edges[0] % 4 * 2],
              *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[2] / 4)]
                                      [(unsigned)edges[2] % 4 * 2]);
    std::swap(*(uint16_t *)&this->cube[(unsigned)((unsigned)edges[1] / 4)]
                                      [(unsigned)edges[1] % 4 * 2],
              *(uint16_t *)&this->cube[(unsigned)((unsigned)edges[3] / 4)]
                                      [(unsigned)edges[3] % 4 * 2]);

    std::swap(this->cube[(unsigned)((unsigned)edges[0] / 4)]
                        [((unsigned)edges[0] % 4 * 2 + 2) % 8],
              this->cube[(unsigned)((unsigned)edges[2] / 4)]
                        [((unsigned)edges[2] % 4 * 2 + 2) % 8]);
    std::swap(this->cube[(unsigned)((unsigned)edges[1] / 4)]
                        [((unsigned)edges[1] % 4 * 2 + 2) % 8],
              this->cube[(unsigned)((unsigned)edges[3] / 4)]
                        [((unsigned)edges[3] % 4 * 2 + 2) % 8]);
    break;
  }
  }
}

void RubiksCubeBitwise::rotateFace(FACE f, ROTATION rotation) {
  uint64_t face = *(uint64_t *)&this->cube[(unsigned)f * 8];

  switch (rotation) {
  case ROTATION::CLOCKWISE:
    asm volatile("rorq $16, %[face]" : [face] "+r"(face) :);
    break;
  case ROTATION::CLOCKWISE2:
    asm volatile("rorq $32, %[face]" : [face] "+r"(face) :);
    break;
  case ROTATION::COUNTERCLOCKWISE:
    asm volatile("rolq $16, %[face]" : [face] "+r"(face) :);
    break;
  }

  *(uint64_t *)&this->cube[(unsigned)f * 8] = face;
}

void RubiksCubeBitwise::rotate(FACE f, ROTATION rotation) {
  rotateFace(f, rotation);
  rotateEdges(f, rotation);
}

RubiksCube &RubiksCubeBitwise::u() {
  rotate(FACE::UP, ROTATION::CLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::uPrime() {
  rotate(FACE::UP, ROTATION::COUNTERCLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::u2() {
  rotate(FACE::UP, ROTATION::CLOCKWISE2);
  return *this;
}

RubiksCube &RubiksCubeBitwise::d() {
  rotate(FACE::DOWN, ROTATION::CLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::dPrime() {
  rotate(FACE::DOWN, ROTATION::COUNTERCLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::d2() {
  rotate(FACE::DOWN, ROTATION::CLOCKWISE2);
  return *this;
}

RubiksCube &RubiksCubeBitwise::l() {
  rotate(FACE::LEFT, ROTATION::CLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::lPrime() {
  rotate(FACE::LEFT, ROTATION::COUNTERCLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::l2() {
  rotate(FACE::LEFT, ROTATION::CLOCKWISE2);
  return *this;
}

RubiksCube &RubiksCubeBitwise::r() {
  rotate(FACE::RIGHT, ROTATION::CLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::rPrime() {
  rotate(FACE::RIGHT, ROTATION::COUNTERCLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::r2() {
  rotate(FACE::RIGHT, ROTATION::CLOCKWISE2);
  return *this;
}

RubiksCube &RubiksCubeBitwise::f() {
  rotate(FACE::FRONT, ROTATION::CLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::fPrime() {
  rotate(FACE::FRONT, ROTATION::COUNTERCLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::f2() {
  rotate(FACE::FRONT, ROTATION::CLOCKWISE2);
  return *this;
}

RubiksCube &RubiksCubeBitwise::b() {
  rotate(FACE::BACK, ROTATION::CLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::bPrime() {
  rotate(FACE::BACK, ROTATION::COUNTERCLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::b2() {
  rotate(FACE::BACK, ROTATION::CLOCKWISE2);
  return *this;
}

RubiksCube &RubiksCubeBitwise::m() {
  rotate(FACE::LEFT, ROTATION::CLOCKWISE);
  rotate(FACE::RIGHT, ROTATION::COUNTERCLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::mPrime() {
  rotate(FACE::LEFT, ROTATION::COUNTERCLOCKWISE);
  rotate(FACE::RIGHT, ROTATION::CLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::m2() {
  rotate(FACE::LEFT, ROTATION::CLOCKWISE2);
  rotate(FACE::RIGHT, ROTATION::CLOCKWISE2);
  return *this;
}

RubiksCube &RubiksCubeBitwise::e() {
  rotate(FACE::UP, ROTATION::COUNTERCLOCKWISE);
  rotate(FACE::DOWN, ROTATION::CLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::ePrime() {
  rotate(FACE::UP, ROTATION::CLOCKWISE);
  rotate(FACE::DOWN, ROTATION::COUNTERCLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::e2() {
  rotate(FACE::UP, ROTATION::CLOCKWISE2);
  rotate(FACE::DOWN, ROTATION::CLOCKWISE2);
  return *this;
}

RubiksCube &RubiksCubeBitwise::s() {
  rotate(FACE::FRONT, ROTATION::CLOCKWISE);
  rotate(FACE::BACK, ROTATION::COUNTERCLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::sPrime() {
  rotate(FACE::FRONT, ROTATION::COUNTERCLOCKWISE);
  rotate(FACE::BACK, ROTATION::CLOCKWISE);
  return *this;
}

RubiksCube &RubiksCubeBitwise::s2() {
  rotate(FACE::FRONT, ROTATION::CLOCKWISE2);
  rotate(FACE::BACK, ROTATION::CLOCKWISE2);
  return *this;
}

RubiksCube::COLOR RubiksCubeBitwise::getColor(FACE face, unsigned row,
                                              unsigned col) const {
  return cube[(unsigned)face][(row << 1) + col];
}

bool RubiksCubeBitwise::isSolved() const {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      if (cube[i][j] != static_cast<COLOR>(i)) {
        return false;
      }
    }
  }

  return true;
}

} // namespace cube