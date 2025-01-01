#include "Fps.hpp"
#include "analizer/src/DrawElements/fps/FpsCounter.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"

std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>
    FpsCounter::time_ = {};

void Fps::Draw(const Drawer *drawer) const {
  long long curFps = FpsCounter::GetFps();
  std::string text = std::to_string(curFps);

   Si32 windowHeight = drawer->GetWindow()->GetFrameSprite().Size().y;

  gFont_.Draw(drawer->GetDrawSprite(), text.c_str(), 0, windowHeight,
               kTextOriginTop,  kTextAlignmentLeft,
               kDrawBlendingModeColorize,  kFilterNearest,
               Rgba(0, 255, 0));
}
