#pragma once

#include "analizer/src/window/Window.hpp"
#include "analizer/src/window/IListener.hpp"
#include "analizer/src/mouse/Mouse.hpp"

#include "engine/vec2si32.h"

#include <optional>

#define UNDEFINED_MOUSE_POSITION arctic::Vec2Si32(-1, -1);

class MWindow : virtual public Window, public IListener {
public:
    void Listen() override {
        if (mouse_) {
            (*mouse_)->Listen();
        }
    }

    virtual bool IsMouseIn() const;
    
    arctic::Vec2Si32 GetMouseOffset() const;

    void SetMouse(Mouse* mouse) {
        mouse_ = mouse;
    }

    Mouse* GetMouse() const {
        if (!mouse_) {
            return nullptr;
        }

        return *mouse_;
    }

    MWindow(arctic::Sprite sprite) :
        Window(sprite) {}

    ~MWindow() = default;

private:
    MWindow() = delete;
    MWindow(const MWindow&) = delete;
    MWindow& operator=(const MWindow&) = delete;

    std::optional<Mouse*> mouse_;
};