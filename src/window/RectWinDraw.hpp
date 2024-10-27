#pragma once

#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"
#include "RectangleWindow/RectangleWindow.hpp"
#include "analizer/src/window/MWindow/MWindow.hpp"
#include "engine/vec2si32.h"
#include <memory>

class RectWinDraw : 
    public RectangleWindow, 
    public Drawer, 
    public MWindow {
public:
    RectWinDraw(arctic::Sprite sprite, arctic::Vec2Si32 windowSize, 
                Camera* camera,
                Mouse* mouse) :
    RectWinDraw(sprite, windowSize, camera) {
        SetMouse(mouse);
    }

    RectWinDraw(arctic::Sprite sprite, arctic::Vec2Si32 windowSize, Camera* camera) :
        RectWinDraw(sprite, windowSize) {
        SetCamera(camera);
    }

    RectWinDraw(arctic::Sprite sprite, arctic::Vec2Si32 windowSize) :
        Window(sprite),
        MWindow(sprite),
        Drawer(),
        RectangleWindow(sprite, windowSize) {}

    arctic::Sprite GetDrawSprite() override;

    void Listen() override;

    Window* GetWindow() override;
};