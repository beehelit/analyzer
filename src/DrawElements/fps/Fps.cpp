#include "Fps.hpp"
#include "analizer/src/DrawElements/fps/FpsCounter.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"

std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> FpsCounter::time_ = {};

void Fps::Draw(Drawer* drawer) const {
    auto curFps = FpsCounter::GetFps();
    std::string text = std::to_string(curFps);

    // TODO for any window, now only for Rectangle
    auto* window = dynamic_cast<RectangleWindow*>(drawer->GetWindow());
    auto windowHeight = window->GetWindowSize().y;

    gFont_.Draw(drawer->GetDrawSprite(), 
                text.c_str(), 
                0, windowHeight,
                arctic::kTextOriginTop,
                arctic::kTextAlignmentLeft,
                arctic::kDrawBlendingModeAlphaBlend,
                arctic::kFilterNearest,
                arctic::Rgba(0, 0, 0));
}