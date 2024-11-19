#pragma once

#include "engine/easy_sprite.h"
#include "engine/vec2si32.h"

enum class DrawElementType {
  ACTOR,
  TRANSPORT_LINE,
  FPS,
  PLAYER_PAUSE_PLAY_BUTTON,
  SPEED_UP_BUTTON,
  TIME_LINE,
  MESSAGE
};

class Drawer;

class IDrawElement {
public:
  virtual DrawElementType GetDrawElementType() const = 0;
  virtual void Draw(const Drawer *) const = 0;
  virtual ~IDrawElement() {}
};
