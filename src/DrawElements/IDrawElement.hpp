#pragma once

#include "engine/easy_sprite.h"
#include "engine/vec2si32.h"

enum class DrawElementType {
  ACTOR,
  TRANSPORT_LINE,
  FPS,
  PLAYER_PAUSE_PLAY_BUTTON,
  SPEED_UP_BUTTON,
  SPEED_DOWN_BUTTON,
  TIME_LINE,
  MESSAGE
};

class Drawer;

class IDrawElement {
public:
  virtual DrawElementType GetDrawElementType() const = 0;
  virtual void Draw(const Drawer *) const = 0;
  virtual ~IDrawElement() {}

  static bool IsWindowed(DrawElementType type) {
    switch (type) {
      case DrawElementType::PLAYER_PAUSE_PLAY_BUTTON:
        return true;

      case DrawElementType::TIME_LINE:
        return true;

      case DrawElementType::SPEED_UP_BUTTON:
        return true;

      case DrawElementType::SPEED_DOWN_BUTTON:
        return true;
        
      default:
        return false;
    }
  }
};
