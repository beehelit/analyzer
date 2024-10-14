#pragma once

#include "engine/easy_sprite.h"
#include "engine/vec2si32.h"
class IDrawElement {
public:
    virtual void Draw(arctic::Sprite) const = 0;
    virtual ~IDrawElement() {}
};