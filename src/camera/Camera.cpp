#include "Camera.hpp"

#include "engine/easy.h"

using namespace arctic;

void Camera::Listen() {
  if ( IsKeyDown( KeyCode::kKeyLeft)) {
    offset_.x -= 2;
  }

  if ( IsKeyDown( KeyCode::kKeyDown)) {
    offset_.y -= 2;
  }

  if ( IsKeyDown( KeyCode::kKeyRight)) {
    offset_.x += 2;
  }

  if ( IsKeyDown( KeyCode::kKeyUp)) {
    offset_.y += 2;
  }

  if ( IsKeyDown( KeyCode::kKeyEquals)) {
    scaleFactor_ += 0.01;
  }

  if ( IsKeyDown( KeyCode::kKeyMinus)) {
    scaleFactor_ -= 0.01;
  }
}
