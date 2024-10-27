#pragma once

#include "engine/easy_sprite.h"
#include "engine/vec2si32.h"
#include "../camera/Camera.hpp"

enum class DrawElementType {
    ACTOR,
    TRANSPORT_LINE
};

class Drawer;

class IDrawElement {
public:
    virtual DrawElementType GetDrawElementType() const = 0;
    virtual void Draw(Drawer*) const = 0;
    virtual ~IDrawElement() {}
};