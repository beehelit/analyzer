#include "TimeLine.hpp"

#include <window/Drawer/Drawer.hpp>

#include "engine/easy_drawing.h"
#include "engine/rgba.h"
#include "engine/vec2si32.h"

void TimeLine::Action() {
  auto mouseCoordX = GetMouseOffset().x;
  auto width = GetFrameSprite().Size().x;

  time_ = (1.0 * mouseCoordX / width) * maxTime_;
}

void TimeLine::Draw(const Drawer *drawer) const {
  auto width = drawer->GetDrawSprite().Size().x;
  auto curX = (1.0 * time_ / maxTime_) * width;

  arctic::DrawRectangle(drawer->GetDrawSprite(), arctic::Vec2Si32(0, 0),
                        drawer->GetDrawSprite().Size(),
                        arctic::Rgba(255, 255, 255));

  arctic::DrawRectangle(
      drawer->GetDrawSprite(), arctic::Vec2Si32(0, 0),
      arctic::Vec2Si32(curX, drawer->GetDrawSprite().Size().y),
      arctic::Rgba(13, 131, 13));
}