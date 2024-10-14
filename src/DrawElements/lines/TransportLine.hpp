#pragma once

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/MainFrame/MainFrame.hpp"
#include "engine/arctic_types.h"
#include "engine/vec2si32.h"
#include "../actors/Actor.hpp"

class TransportLine : public IDrawElement {
public:
    void Draw(arctic::Sprite sprite) const override {
        auto from_coord = dynamic_cast<Actor*>(MainFrame::GetDrawElements()[MainFrame::GetActorsList()[fromTo_.first]])->GetCenter();
        auto to_coord = dynamic_cast<Actor*>(MainFrame::GetDrawElements()[MainFrame::GetActorsList()[fromTo_.second]])->GetCenter();

        arctic::DrawLine(sprite, from_coord, to_coord, arctic::Rgba(255, 255, 255));
    }

    TransportLine(arctic::Si32 from, arctic::Si32 to) :
        fromTo_(from, to) {}

private:
    std::pair<arctic::Si32, arctic::Si32> fromTo_;
};