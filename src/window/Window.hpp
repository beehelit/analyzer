#pragma once

#include "engine/easy_sprite.h"
#include "engine/rgba.h"

class Window {
public:
    virtual void Fill(arctic::Rgba color) = 0;
    
    auto GetFrameSprite() const {
        return frameSprite_;
    }

    Window(arctic::Sprite frameSprite) :
        frameSprite_(frameSprite) {}

    void AddSubWindow(Window* window) {
        subWindows_.push_back(window);
    }

    const auto& GetSubWindows() {
        return subWindows_;
    }

    virtual ~Window() {
        for (auto window : subWindows_) {
            delete window;
        }
    }

private:
    Window() = delete;
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    arctic::Sprite frameSprite_;
    std::vector<Window*> subWindows_;
};