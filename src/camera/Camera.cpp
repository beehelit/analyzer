#include "Camera.hpp"

#include "engine/easy.h"

void Camera::Listen() {
  if (arctic::IsKeyDown(arctic::KeyCode::kKeyLeft)) {
    offset_.x -= 2;
  }

  if (arctic::IsKeyDown(arctic::KeyCode::kKeyDown)) {
    offset_.y -= 2;
  }

  if (arctic::IsKeyDown(arctic::KeyCode::kKeyRight)) {
    offset_.x += 2;
  }

  if (arctic::IsKeyDown(arctic::KeyCode::kKeyUp)) {
    offset_.y += 2;
  }

  if (arctic::IsKeyDown(arctic::KeyCode::kKeyEquals)) {
    scaleFactor_ += 0.01;
  }

  if (arctic::IsKeyDown(arctic::KeyCode::kKeyMinus)) {
    scaleFactor_ -= 0.01;
  }
}
