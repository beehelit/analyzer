#pragma once

#include <DrawElements/IDrawElement.hpp>

#include "engine/font.h"

using namespace arctic;

class Fps : public IDrawElement {
public:
  Fps() { gFont_.Load("data/arctic_one_bmf.fnt"); }

  void Draw(const Drawer *drawer) const override;

  DrawElementType GetDrawElementType() const override {
    return DrawElementType::FPS;
  }

private:
  mutable  Font gFont_;
};
