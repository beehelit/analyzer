#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <_types/_uint64_t.h>
#include <camera/Camera.hpp>
#include <window/RectangleWindow/RectangleWindow.hpp>

#include "engine/arctic_types.h"
#include "engine/easy_drawing.h"
#include "engine/rgba.h"
#include "engine/vec2si32.h"
#include "log/Logs.hpp"
#include <memory>

#include <map>
using ActorId = uint64_t;

class Actor : public IDrawElement {
public:
  Actor( Vec2Si32 offset,  Si32 radius, uint64_t id, bool visible, Font font)
      : radius_(radius), offset_(offset), id_(id), visible_(visible), gFont_(font) {

    const std::map<ActorId, std::string_view>& idToType = Logs::GetActorIdToActorType();
    std::string text = static_cast<std::string>(idToType.at(GetId()));

    Vec2Si32 typeBlockSize = gFont_.EvaluateSize(text.c_str(), false);
    Vec2F leftDownBlockCorner = Vec2F(offset_) -  Vec2F(8, 40);
    Vec2F rightUpCorner = Vec2F(offset_ + typeBlockSize) -  Vec2F(-5, 20);

    actorCenter_ = Vec2Si32(leftDownBlockCorner + (rightUpCorner - leftDownBlockCorner) / 2);
  }

  void Draw(const Drawer *drawer) const override;

  DrawElementType GetDrawElementType() const override {
    return DrawElementType::ACTOR;
  }

   Vec2Si32 GetOffset() const { return offset_; }

   Vec2Si32 GetActorCenter() const { return actorCenter_; }

   Si32 GetRadius() const { return radius_; }

  uint64_t GetId() const { return id_; }

  void SetVisible(bool visible) { visible_ = visible; }
  bool IsVisible() const { return visible_; } 

private:
   Si32 radius_;
  Vec2Si32 offset_;
  Vec2Si32 actorCenter_;

  uint64_t id_;

  bool visible_ = true;

  mutable Font gFont_;
};
