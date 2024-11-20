#pragma once

#include "engine/easy_drawing.h"
#include "engine/easy_sprite.h"
#include "engine/rgba.h"
#include "engine/vec2si32.h"

const arctic::Sprite kNoneSprite = arctic::Sprite();

class Window {
public:
  virtual void Fill(arctic::Rgba color) const {
    arctic::DrawRectangle(frameSprite_, arctic::Vec2Si32(0, 0),
                          frameSprite_.Size(), color);
  }

  arctic::Sprite GetFrameSprite() const { return frameSprite_; }

  Window(arctic::Sprite frameSprite) : frameSprite_(frameSprite) {}

  void AddSubWindow(Window *window) { subWindows_.push_back(window); }

  const std::vector<Window*>& GetSubWindows() const { return subWindows_; }

  virtual ~Window() {
    for (Window* window : subWindows_) {
      delete window;
    }
  }

  Window() { frameSprite_ = kNoneSprite; }

  virtual void SetSprite(arctic::Sprite sprite) { frameSprite_ = sprite; }

  void ClearSprite() { frameSprite_ = kNoneSprite; }

private:
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  arctic::Sprite frameSprite_;
  std::vector<Window *> subWindows_;
};
