#pragma once

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/DrawElements/actors/Actor.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"

#include "engine/arctic_types.h"
#include "engine/vec2si32.h"

class TransportLine : public IDrawElement {
public:
    void Draw(Drawer* drawer) const override {
        auto fromActor = drawer->GetActorStorage()[fromTo_.first];
        auto toActor = drawer->GetActorStorage()[fromTo_.second];

        auto fromCoord = fromActor->GetOffset();
        auto toCoord = toActor->GetOffset();

        auto camera = drawer->GetCamera();

        // TODO for any window, now only for Rectangle
        auto* window = dynamic_cast<RectangleWindow*>(drawer->GetWindow());
        auto center = window->GetWindowSize() / 2;

        fromCoord -= camera->GetOffset();
        toCoord -= camera->GetOffset();

        fromCoord.x = center.x - (center.x - fromCoord.x) * camera->GetScaleFactor();
        fromCoord.y = center.y - (center.y - fromCoord.y) * camera->GetScaleFactor();

        toCoord.x = center.x - (center.x - toCoord.x) * camera->GetScaleFactor();
        toCoord.y = center.y - (center.y - toCoord.y) * camera->GetScaleFactor();

        arctic::DrawLine(drawer->GetDrawSprite(), 
                         fromCoord, 
                         toCoord, 
                            arctic::Rgba(255, 255, 255));
    }

    DrawElementType GetDrawElementType() const override {
        return DrawElementType::TRANSPORT_LINE;
    }

    TransportLine(arctic::Si32 from, arctic::Si32 to) :
        fromTo_(from, to) {}

private:
    std::pair<arctic::Si32, arctic::Si32> fromTo_;
};