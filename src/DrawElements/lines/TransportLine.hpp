#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <DrawElements/actors/Actor.hpp>
#include <window/Drawer/Drawer.hpp>

#include "engine/arctic_types.h"
#include "engine/easy_drawing.h"
#include "engine/vec2f.h"
#include "engine/vec2si32.h"

using namespace arctic;

class TransportLine : public IDrawElement {
public:
  void Draw(const Drawer *drawer) const override {
    Actor* fromActor = drawer->GetActorStorage()[
      drawer->GetActorIdToStorageInd().at(fromTo_.first)
    ];
    Actor* toActor = drawer->GetActorStorage()[
      drawer->GetActorIdToStorageInd().at(fromTo_.second)
    ];

     Vec2Si32 fromCoord = fromActor->GetActorCenter();
     Vec2Si32 toCoord = toActor->GetActorCenter();

    Camera* camera = drawer->GetCamera();
     Vec2Si32 center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

    fromCoord -= camera->GetOffset();
    toCoord -= camera->GetOffset();

    fromCoord.x =
        center.x - (center.x - fromCoord.x) * camera->GetScaleFactor();
    fromCoord.y =
        center.y - (center.y - fromCoord.y) * camera->GetScaleFactor();

    toCoord.x = center.x - (center.x - toCoord.x) * camera->GetScaleFactor();
    toCoord.y = center.y - (center.y - toCoord.y) * camera->GetScaleFactor();

     Sprite sprite = drawer->GetDrawSprite();

     DrawArrow(sprite,  Vec2F(fromCoord),  Vec2F(toCoord),
                     2, 30, 50,
                      Rgba(120, 0, 0));
  }

  DrawElementType GetDrawElementType() const override {
    return DrawElementType::TRANSPORT_LINE;
  }

  TransportLine( Si32 from,  Si32 to) : fromTo_(from, to) {}

  std::pair< Si32,  Si32> GetFromTo() const { return fromTo_; }

private:
  std::pair< Si32,  Si32> fromTo_;
};
