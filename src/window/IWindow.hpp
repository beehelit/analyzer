#pragma once

#include "engine/easy_sprite.h"
#include "engine/rgba.h"

class IWindow {
public:
    virtual void Fill(arctic::Rgba color) = 0;
    
    auto GetFrameSprite() {
        return frameSprite_;
    }

    IWindow(arctic::Sprite frameSprite) :
        frameSprite_(frameSprite) {}
private:
    arctic::Sprite frameSprite_;
};