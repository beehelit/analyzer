#pragma once

#include <vector>

#include <DrawElements/IDrawElement.hpp>
#include <window/MWindow/MWindow.hpp>

#include "engine/vec2si32.h"

class RectangleWindow : virtual public MWindow {
public:
  RectangleWindow(arctic::Sprite sprite) : Window(sprite) {}

  RectangleWindow() = default;

  arctic::Vec2Si32 GetWindowSize() const { return GetFrameSprite().Size(); }

  bool IsMouseIn() const override;
};
