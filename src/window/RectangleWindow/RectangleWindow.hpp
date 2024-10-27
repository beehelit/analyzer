#pragma once 

#include <vector>

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/window/Window.hpp"
#include "engine/vec2si32.h"

class RectangleWindow : virtual public Window {
public:
    RectangleWindow(arctic::Sprite sprite, arctic::Vec2Si32 windowSize) :
        Window(sprite),
        windowSize_(windowSize) {}

    void Fill(arctic::Rgba color) override;

    auto GetWindowSize() {
        return windowSize_;
    }
private:
    arctic::Vec2Si32 windowSize_;
};