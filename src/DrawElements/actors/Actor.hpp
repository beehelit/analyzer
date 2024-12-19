#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <_types/_uint64_t.h>
#include <camera/Camera.hpp>
#include <window/RectangleWindow/RectangleWindow.hpp>

#include "engine/arctic_types.h"
#include "engine/easy_drawing.h"
#include "engine/rgba.h"
#include "engine/vec2si32.h"
#include <memory>

class Actor : public IDrawElement {
public:
  Actor(arctic::Vec2Si32 offset, arctic::Si32 radius, uint64_t id, bool visible)
      : radius_(radius), offset_(offset), id_(id), visible_(visible) {}

  void Draw(const Drawer *drawer) const override;

  DrawElementType GetDrawElementType() const override {
    return DrawElementType::ACTOR;
  }

  arctic::Vec2Si32 GetOffset() const { return offset_; }

  arctic::Si32 GetRadius() const { return radius_; }

  uint64_t GetId() const { return id_; }

  void SetVisible(bool visible) { visible_ = visible; }
  bool IsVisible() const { return visible_; } 

private:
  arctic::Si32 radius_;
  arctic::Vec2Si32 offset_;

  uint64_t id_;

  bool visible_ = true;
};
