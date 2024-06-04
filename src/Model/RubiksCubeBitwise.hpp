#pragma once
#include "RubiksCube.hpp"
#include <array>
#include <map>
#include <vector>

namespace cube {

class RubiksCubeBitwise : public RubiksCube {
private:
  typedef RubiksCube::MOVE MOVE;
  typedef RubiksCube::FACE FACE;
  typedef RubiksCube::COLOR COLOR;

  enum class ROTATION : uint8_t {
    CLOCKWISE,
    CLOCKWISE2,
    COUNTERCLOCKWISE,
  };

  enum class FACE_EDGE : uint8_t {
    UT, // Up Top
    UR, // Up Right
    UB, // Up Bottom
    UL, // Up Left

    LT, // Left Top
    LR, // Left Right
    LB, // Left Bottom
    LL, // Left Left

    FT, // Front Top
    FR, // Front Right
    FB, // Front Bottom
    FL, // Front Left

    RT, // Right Top
    RR, // Right Right
    RB, // Right Bottom
    RL, // Right Left

    DT, // Down Top
    DR, // Down Right
    DB, // Down Bottom
    DL, // Down Left

    BT, // Back Top
    BR, // Back Right
    BB, // Back Bottom
    BL, // Back Left
  };
  COLOR cube[6][8];
  /**
   * @brief Rotates the face of the cube according to the rotation. Ignores the
   * edges of the face.
   *
   * @param f Face to rotate.
   * @param rotation Rotation to apply.
   */
  void rotateFace(FACE f, ROTATION rotation);

  /**
   * @brief Rotates the edges of the face of the cube according to the rotation.
   * Ignores the face itself.
   *
   * @param f Face to rotate.
   * @param rotation Rotation to apply.
   */
  void rotateEdges(FACE f, ROTATION rotation);

  /**
   * @brief Applies the rotation to the face and edges of the face.
   *
   * @param f Face to rotate.
   * @param rotation Rotation to apply.
   */
  void rotate(FACE f, ROTATION rotation);

  // Edge mapping
  std::map<FACE, std::array<FACE_EDGE, 4>> edgeMap = {
      {FACE::UP, {FACE_EDGE::BB, FACE_EDGE::RT, FACE_EDGE::FT, FACE_EDGE::LT}},
      {FACE::DOWN,
       {FACE_EDGE::LB, FACE_EDGE::FB, FACE_EDGE::RB, FACE_EDGE::BT}},
      {FACE::LEFT,
       {FACE_EDGE::UL, FACE_EDGE::FL, FACE_EDGE::DL, FACE_EDGE::BL}},
      {FACE::RIGHT,
       {FACE_EDGE::UR, FACE_EDGE::BR, FACE_EDGE::DR, FACE_EDGE::FL}},
      {FACE::FRONT,
       {FACE_EDGE::LR, FACE_EDGE::UB, FACE_EDGE::RL, FACE_EDGE::DT}},
      {FACE::BACK,
       {FACE_EDGE::DB, FACE_EDGE::RR, FACE_EDGE::UT, FACE_EDGE::LL}}};

public:
  RubiksCubeBitwise();

  std::vector<std::vector<COLOR>> getMatrix() const;

  RubiksCube &u() override;
  RubiksCube &uPrime() override;
  RubiksCube &u2() override;

  RubiksCube &d() override;
  RubiksCube &dPrime() override;
  RubiksCube &d2() override;

  RubiksCube &l() override;
  RubiksCube &lPrime() override;
  RubiksCube &l2() override;

  RubiksCube &r() override;
  RubiksCube &rPrime() override;
  RubiksCube &r2() override;

  RubiksCube &f() override;
  RubiksCube &fPrime() override;
  RubiksCube &f2() override;

  RubiksCube &b() override;
  RubiksCube &bPrime() override;
  RubiksCube &b2() override;

  RubiksCube &m() override;
  RubiksCube &mPrime() override;
  RubiksCube &m2() override;

  RubiksCube &e() override;
  RubiksCube &ePrime() override;
  RubiksCube &e2() override;

  RubiksCube &s() override;
  RubiksCube &sPrime() override;
  RubiksCube &s2() override;

  RubiksCube::COLOR getColor(FACE face, unsigned row,
                             unsigned col) const override;
  bool isSolved() const override;
};

} // namespace cube