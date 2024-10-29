#pragma once

#include "engine/easy_sprite.h"
#include "engine/vec2si32.h"

enum class DrawElementType {
    ACTOR,
    TRANSPORT_LINE,
    FPS,
    PLAYER_PAUSE_PLAY_BUTTON,
    TIME_LINE
};

class Drawer;

class IDrawElement {
public:
    virtual DrawElementType GetDrawElementType() const = 0;
    virtual void Draw(const Drawer*) const = 0;
    virtual ~IDrawElement() {}
};