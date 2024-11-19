#pragma once

#include <window/Window.hpp>

#include "engine/arctic_types.h"
#include "engine/vec2si32.h"

class ElipseSeet {
public:
  ElipseSeet(Window *window) : window_(window), seetCount_(0) {}

  void SeetN(arctic::Ui32 count);
  arctic::Vec2Si32 GetCoord(arctic::Ui32 number);

private:
  double ElipseLen();
  arctic::Vec2Si32 PixFromElipseCoord(double eliseCoord);

  Window *window_;
  arctic::Ui32 seetCount_;
};