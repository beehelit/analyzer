#include "Fps.hpp"
#include "analizer/src/DrawElements/fps/FpsCounter.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"

std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> FpsCounter::time_ = {};

void Fps::Draw(const Drawer* drawer) const {
    auto curFps = FpsCounter::GetFps();
    std::string text = std::to_string(curFps);

    auto windowHeight = drawer->GetWindow()->GetFrameSprite().Size().y;

    gFont_.Draw(drawer->GetDrawSprite(), 
                text.c_str(), 
                0, windowHeight,
                arctic::kTextOriginTop,
                arctic::kTextAlignmentLeft,
                arctic::kDrawBlendingModeColorize,
                arctic::kFilterNearest,
                arctic::Rgba(0, 255, 0));
}