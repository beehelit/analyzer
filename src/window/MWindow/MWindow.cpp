#include "MWindow.hpp"
#include "engine/vec2si32.h"

arctic::Vec2Si32 MWindow::GetMouseOffset() const {
  Mouse* mouse = *mouse_;

  arctic::Vec2Si32 spritePos = GetFrameSprite().RefPos();
  arctic::Vec2Si32 mousePos = mouse->GetOffset();

  return mousePos - spritePos;
}
