#pragma once

#include <mouse/Mouse.hpp>
#include <window/IListener.hpp>
#include <window/Window.hpp>

#include "engine/vec2si32.h"

#include <optional>

const arctic::Vec2Si32 kUndefinedMousePosition = arctic::Vec2Si32(-1, -1);

class MWindow : virtual public Window, public IListener {
public:
  void Listen() override {
    if (mouse_) {
      (*mouse_)->Listen();
    }
  }

  virtual bool IsMouseIn() const = 0;

  arctic::Vec2Si32 GetMouseOffset() const;

  void SetMouse(Mouse *mouse) { mouse_ = mouse; }

  Mouse *GetMouse() const {
    if (!mouse_) {
      return nullptr;
    }

    return *mouse_;
  }

  MWindow(arctic::Sprite sprite, Mouse *mouse) : MWindow(sprite) {
    mouse_ = mouse;
  }

  MWindow(arctic::Sprite sprite) : Window(sprite) {}

  ~MWindow() = default;

  MWindow() = default;

private:
  MWindow(const MWindow &) = delete;
  MWindow &operator=(const MWindow &) = delete;

  std::optional<Mouse *> mouse_;
};