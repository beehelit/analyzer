#pragma once

#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"
#include "RectangleWindow/RectangleWindow.hpp"
#include "engine/vec2si32.h"
#include <memory>

class RectWinDraw : public RectangleWindow, public Drawer {
public:
    RectWinDraw(arctic::Sprite sprite, arctic::Vec2Si32 windowSize, std::shared_ptr<Camera> camera) :
        Drawer(camera),
        RectangleWindow(sprite, windowSize) {}

    RectWinDraw(arctic::Sprite sprite, arctic::Vec2Si32 windowSize) :
        RectWinDraw(sprite, windowSize, std::make_shared<Camera>()) {}

    arctic::Sprite GetDrawSprite() override;
    IWindow* GetWindow() override;
};