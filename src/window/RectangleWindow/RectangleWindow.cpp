#include "RectangleWindow.hpp"

bool RectangleWindow::IsMouseIn() const {
  if (!GetMouse()) {
    return false;
  }

  Mouse* mouse = GetMouse();

  arctic::Vec2Si32 spritePos = GetFrameSprite().RefPos();
  arctic::Vec2Si32 mousePos = mouse->GetOffset();
  arctic::Vec2Si32 spriteSize = GetFrameSprite().Size();

  return mousePos.x > spritePos.x && mousePos.y > spritePos.y &&
         mousePos.x < spritePos.x + spriteSize.x &&
         mousePos.y < spritePos.y + spriteSize.y;
}
