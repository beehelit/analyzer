#pragma once

#include <mouse/Mouse.hpp>
#include <window/IListener.hpp>

#include "engine/easy.h"
#include "engine/vec2si32.h"

#include <optional>

class Camera : public IListener {
public:
    Camera(arctic::Vec2Si32 cameraOffset, double scaleFactor) :
        offset_(cameraOffset),
        scaleFactor_(scaleFactor) {}

    Camera() :
        offset_(arctic::Vec2Si32(0, 0)),
        scaleFactor_(1.0){}

    auto GetOffset() { return offset_; }
    auto GetScaleFactor() { return scaleFactor_; }

    void SetOffset(arctic::Vec2Si32 offset) { offset_ = offset; }
    void SetScaleFactor(double scaleFactor) { scaleFactor_ = scaleFactor; }

    void Listen() override;
private:
    arctic::Vec2Si32 offset_;
    double scaleFactor_;
};