#pragma once 

#include <vector>

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/window/MWindow/MWindow.hpp"
#include "engine/vec2si32.h"

class RectangleWindow : public MWindow {
public:
    RectangleWindow(arctic::Sprite sprite) :
        Window(sprite) {}

    RectangleWindow() = default;

    // void Fill(arctic::Rgba color) override;

    auto GetWindowSize() const {
        return GetFrameSprite().Size();
    }

    bool IsMouseIn() const override;
};