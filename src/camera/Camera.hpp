#pragma once

#include <mouse/Mouse.hpp>
#include <window/IListener.hpp>

#include "engine/easy.h"
#include "engine/vec2si32.h"

#include <optional>

using namespace arctic;

class Camera : public IListener {
public:
  Camera( Vec2Si32 cameraOffset, double scaleFactor)
      : offset_(cameraOffset), scaleFactor_(scaleFactor) {}

  Camera() : offset_( Vec2Si32(0, 0)), scaleFactor_(1.0) {}

   Vec2Si32 GetOffset() { return offset_; }
  double GetScaleFactor() { return scaleFactor_; }

  void SetOffset( Vec2Si32 offset) { offset_ = offset; }
  void SetScaleFactor(double scaleFactor) { scaleFactor_ = scaleFactor; }

  void Listen() override;

private:
   Vec2Si32 offset_;
  double scaleFactor_;
};
