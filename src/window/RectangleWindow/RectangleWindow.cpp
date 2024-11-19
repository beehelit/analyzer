#include "RectangleWindow.hpp"

bool RectangleWindow::IsMouseIn() const {
  if (!GetMouse()) {
    return false;
  }

  auto mouse = GetMouse();

  auto spritePos = GetFrameSprite().RefPos();
  auto mousePos = mouse->GetOffset();
  auto spriteSize = GetFrameSprite().Size();

  return mousePos.x > spritePos.x && mousePos.y > spritePos.y &&
         mousePos.x < spritePos.x + spriteSize.x &&
         mousePos.y < spritePos.y + spriteSize.y;
}
