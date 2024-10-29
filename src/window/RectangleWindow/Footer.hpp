#pragma once

#include "analizer/src/window/IListener.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"
#include "analizer/src/window/Drawer/DrawBox.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"
#include "engine/easy_sprite.h"

class Footer : 
    public Drawer,
    public RectangleWindow {
public:
    Footer(arctic::Sprite sprite) :
        Window(sprite),
        RectangleWindow(sprite) {}

    Footer() = default;

    void Listen() override {
        RectangleWindow::Listen();

        for (auto window : GetSubWindows()) {
            auto elem = dynamic_cast<Drawer*>(window)->GetWindow();
            auto nonConst = const_cast<Window*>(elem);
            dynamic_cast<IListener*>(nonConst)->Listen();
        }
    }

    const Window* GetWindow() const override {
        return this;
    }

    arctic::Sprite GetDrawSprite() const override {
        return GetFrameSprite();
    }
};