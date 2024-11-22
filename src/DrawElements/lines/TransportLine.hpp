#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <DrawElements/actors/Actor.hpp>
#include <window/Drawer/Drawer.hpp>

#include "engine/arctic_types.h"
#include "engine/vec2si32.h"

class TransportLine : public IDrawElement {
public:
  void Draw(const Drawer *drawer) const override {
    Actor* fromActor = drawer->GetActorStorage()[fromTo_.first];
    Actor* toActor = drawer->GetActorStorage()[fromTo_.second];

    arctic::Vec2Si32 fromCoord = fromActor->GetOffset();
    arctic::Vec2Si32 toCoord = toActor->GetOffset();

    Camera* camera = drawer->GetCamera();
    arctic::Vec2Si32 center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

    fromCoord -= camera->GetOffset();
    toCoord -= camera->GetOffset();

    fromCoord.x =
        center.x - (center.x - fromCoord.x) * camera->GetScaleFactor();
    fromCoord.y =
        center.y - (center.y - fromCoord.y) * camera->GetScaleFactor();

    toCoord.x = center.x - (center.x - toCoord.x) * camera->GetScaleFactor();
    toCoord.y = center.y - (center.y - toCoord.y) * camera->GetScaleFactor();

    arctic::DrawLine(drawer->GetDrawSprite(), fromCoord, toCoord,
                     arctic::Rgba(255, 0, 0));
  }

  DrawElementType GetDrawElementType() const override {
    return DrawElementType::TRANSPORT_LINE;
  }

  TransportLine(arctic::Si32 from, arctic::Si32 to) : fromTo_(from, to) {}

  std::pair<arctic::Si32, arctic::Si32> GetFromTo() const { return fromTo_; }

private:
  std::pair<arctic::Si32, arctic::Si32> fromTo_;
};
