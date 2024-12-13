#include "RectangleWindow.hpp"

#include <iostream>

bool RectangleWindow::IsMouseIn() const {
  if (!GetMouse()) {
    return false;
  }

  Mouse* mouse = GetMouse();

  arctic::Vec2Si32 spritePos = GetFrameSprite().RefPos();
  arctic::Vec2Si32 mousePos = mouse->GetOffset();
  arctic::Vec2Si32 spriteSize = GetFrameSprite().Size();

//  std::cout << spritePos.x <<  " " << spritePos.y << std::endl;
    // std::cout << mousePos.x << " " << mousePos.y << std::endl;
//  std::cout << spriteSize.x << " " << spriteSize.y << std::endl;
//  std::cout << std::endl;

  return mousePos.x > spritePos.x && 
         mousePos.y > spritePos.y &&
         mousePos.x < spriteSize.x && // ?
         mousePos.y < spriteSize.y; // ? 
}
