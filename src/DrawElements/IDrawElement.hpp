#pragma once

#include "engine/easy_sprite.h"
#include "engine/vec2si32.h"

enum class DrawElementType {
    ACTOR,
    TRANSPORT_LINE,
    FPS
};

class Drawer;

class IDrawElement {
public:
    virtual DrawElementType GetDrawElementType() const = 0;
    virtual void Draw(Drawer*) const = 0;
    virtual ~IDrawElement() {}
};