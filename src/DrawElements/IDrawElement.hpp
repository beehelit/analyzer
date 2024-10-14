#pragma once



#include "engine/easy_sprite.h"
#include "engine/vec2si32.h"
#include "../camera/Camera.hpp"

class Drawer;

class IDrawElement {
public:
    virtual void Draw(Drawer*) const = 0;
    virtual ~IDrawElement() {}
};