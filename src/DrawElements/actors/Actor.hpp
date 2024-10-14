#pragma once

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/MainFrame/MainFrame.hpp"
#include "engine/arctic_types.h"
#include "engine/easy_drawing.h"
#include "engine/rgba.h"
#include "engine/vec2si32.h"

class Actor : public IDrawElement {
public:

    Actor(arctic::Vec2Si32 offset, arctic::Si32 radius) :
        radius_(radius),
        offset_(offset) {}

    void Draw() const override {
        auto coord = GetCenter();

        arctic::DrawCircle(MainFrame::GetSprite(), coord, radius_ * MainFrame::GetScaleFactor(), arctic::Rgba(0, 255, 0));
    }

    arctic::Vec2Si32 GetCenter() const {
        auto coord = offset_;

        coord -= MainFrame::GetCameraOffset();
        coord -= MainFrame::GetMouseOffset();
    

        coord.x = MainFrame::GetCenter().x - (MainFrame::GetCenter().x - coord.x) * MainFrame::GetScaleFactor();
        coord.y = MainFrame::GetCenter().y - (MainFrame::GetCenter().y - coord.y) * MainFrame::GetScaleFactor();

        return coord;
    }

private:
    arctic::Si32 radius_;
    arctic::Vec2Si32 offset_;
};