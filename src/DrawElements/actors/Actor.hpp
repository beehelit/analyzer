#pragma once

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/MainFrame/MainFrame.hpp"
#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"

#include "engine/arctic_types.h"
#include "engine/easy_drawing.h"
#include "engine/rgba.h"
#include "engine/vec2si32.h"
#include <memory>

class Actor : public IDrawElement {
public:

    Actor(arctic::Vec2Si32 offset, arctic::Si32 radius) :
        radius_(radius),
        offset_(offset) {}

    void Draw(Drawer* drawer) const override {
        auto coord = offset_;

        auto camera = drawer->GetCamera();
        coord -= camera->GetOffset();

        // TODO - mouse offset

        // TODO for any window, now only for Rectangle
        auto* window = dynamic_cast<RectangleWindow*>(drawer->GetWindow());
        auto center = window->GetWindowSize() / 2;

        coord.x = center.x - (center.x - coord.x) * camera->GetScaleFactor();
        coord.y = center.y - (center.y - coord.y) * camera->GetScaleFactor();

        arctic::DrawCircle(drawer->GetDrawSprite(), 
                            coord, 
                            radius_ * camera->GetScaleFactor(), 
                            arctic::Rgba(0, 255, 0));
    }

private:
    arctic::Si32 radius_;
    arctic::Vec2Si32 offset_;
};