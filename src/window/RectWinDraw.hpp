#pragma once

#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"
#include "RectangleWindow/RectangleWindow.hpp"
#include "analizer/src/window/MWindow/MWindow.hpp"
#include "engine/vec2si32.h"
#include <memory>

class RectWinDraw : 
    public RectangleWindow, 
    public Drawer {
public:
    RectWinDraw(arctic::Sprite sprite, 
                Camera* camera,
                Mouse* mouse) :
    RectWinDraw(sprite, camera) {
        SetMouse(mouse);
    }

    RectWinDraw(arctic::Sprite sprite, Camera* camera) :
        RectWinDraw(sprite) {
        SetCamera(camera);
    }

    RectWinDraw(arctic::Sprite sprite) :
        Window(sprite),
        Drawer(),
        RectangleWindow(sprite) {}

    RectWinDraw() = default;

    arctic::Sprite GetDrawSprite() const override;

    void Listen() override;

    const Window* GetWindow() const override;
};