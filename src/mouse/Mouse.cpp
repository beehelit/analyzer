#include "Mouse.hpp"
#include "analizer/src/camera/Camera.hpp"
#include "engine/easy_input.h"
#include "engine/vec2si32.h"
#include <memory>

#include <iostream>
#include <optional>

void Mouse::Listen() {
  leftMouse_ = arctic::IsKeyDown(arctic::KeyCode::kKeyMouseLeft);
  leftMouseDownward_ = arctic::IsKeyDownward(arctic::KeyCode::kKeyMouseLeft);

  offset_ = arctic::MousePos();
}
