#pragma once

#include "ActionHandler.hpp"
#include <functional>
#include <window/MWindow/MWindow.hpp>

class Button : virtual public MWindow, public ActionHandler {
public:
  Button(arctic::Sprite sprite, std::function<void()> action)
      : Window(sprite), MWindow(sprite), ActionHandler(action) {}

  Button(arctic::Sprite sprite, Mouse *mouse, std::function<void()> action)
      : Button(sprite, action) {
    SetMouse(mouse);
  }

  Button() = default;
};