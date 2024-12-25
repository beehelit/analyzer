#include "TimeLine.hpp"

#include <window/Drawer/Drawer.hpp>

#include "engine/easy_drawing.h"
#include "engine/rgba.h"
#include "engine/vec2si32.h"

#include <iostream>

void TimeLine::Action() {
   Si32 mouseCoordX = GetMouseOffset().x;
   Si32 width = GetFrameSprite().Size().x;

  time_ = (1.0 * mouseCoordX / width) * maxTime_;
}

void TimeLine::Draw(const Drawer *drawer) const {
   Si32 width = drawer->GetDrawSprite().Size().x;
  double curX = (1.0 * time_ / maxTime_) * width;

   DrawRectangle(drawer->GetDrawSprite(),  Vec2Si32(0, 0),
                        drawer->GetDrawSprite().Size(),
                         Rgba(255, 255, 255));


   DrawRectangle(
      drawer->GetDrawSprite(),  Vec2Si32(0, 0),
       Vec2Si32(curX, drawer->GetDrawSprite().Size().y),
       Rgba(13, 131, 13));
}
