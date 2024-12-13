#include "TimeLine.hpp"

#include <window/Drawer/Drawer.hpp>

#include "engine/easy_drawing.h"
#include "engine/rgba.h"
#include "engine/vec2si32.h"

#include <iostream>

void TimeLine::Action() {
  arctic::Si32 mouseCoordX = GetMouseOffset().x;
  arctic::Si32 width = GetFrameSprite().Size().x;

  time_ = (1.0 * mouseCoordX / width) * maxTime_;
}

void TimeLine::Draw(const Drawer *drawer) const {
  arctic::Si32 width = drawer->GetDrawSprite().Size().x;
  double curX = (1.0 * time_ / maxTime_) * width;

  arctic::DrawRectangle(drawer->GetDrawSprite(), arctic::Vec2Si32(0, 0),
                        drawer->GetDrawSprite().Size(),
                        arctic::Rgba(255, 255, 255));

/*
  std::cout << drawer->GetDrawSprite().Size().x << " "
            << drawer->GetDrawSprite().Size().y << std::endl;
*/

  //std::cout << GetMouseOffset().x << " " << GetMouseOffset().y << std::endl;
  arctic::DrawRectangle(
      drawer->GetDrawSprite(), arctic::Vec2Si32(0, 0),
      arctic::Vec2Si32(curX, drawer->GetDrawSprite().Size().y),
      arctic::Rgba(13, 131, 13));
}
