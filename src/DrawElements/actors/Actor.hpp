#pragma once

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/camera/Camera.hpp"
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

    void Draw(Drawer* drawer) const override;

    DrawElementType GetDrawElementType() const override {
        return DrawElementType::ACTOR;
    }

    auto GetOffset() const {
        return offset_;
    }
    
private:
    arctic::Si32 radius_;
    arctic::Vec2Si32 offset_;
};