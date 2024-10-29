#pragma once

#include "ActionHandler.hpp"
#include "analizer/src/window/MWindow/MWindow.hpp"
#include <functional>

class Button : public MWindow, public ActionHandler {
public:
    Button(arctic::Sprite sprite, std::function<void()> action) :
        Window(sprite),
        MWindow(sprite),
        ActionHandler(action) {}

    Button(arctic::Sprite sprite, Mouse* mouse, std::function<void()> action) :
        Button(sprite, action) {
        SetMouse(mouse);
    }

    Button() = default;
};