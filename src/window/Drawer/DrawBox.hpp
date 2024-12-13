#pragma once

#include <window/Window.hpp>
#include "DrawBoxOptions.hpp"

#include "DrawElements/IDrawElement.hpp"
#include "Drawer.hpp"
#include "engine/arctic_types.h"
#include "engine/easy_sprite.h"

#include <vector>

class DrawBox : public Drawer {
public:
  void SetDrawOptions(DrawBoxOptions options) {
    options_ = options;
  }

  void Draw() const override {
    DrawWithOption();
  }

  void DrawWithOption() const;
  
  arctic::Sprite GetDrawSprite() const override {
    return space_;
  }

  void SetDrawSprite(arctic::Sprite sprite) override {
    space_ = sprite;
  }

  const Window *GetWindow() const override { return nullptr; }

  void AddDrawer(Drawer* drawer) {
    drawers_.push_back(drawer);
  }

  void SetDrawElement(IDrawElement* drawElement) {
    drawElement_ = drawElement;
  }

private:

  arctic::Sprite space_;

  std::vector<Drawer*> drawers_;

  IDrawElement* drawElement_ = nullptr;

  DrawBoxOptions options_;
};
