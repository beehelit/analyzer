#pragma once

#include <window/Window.hpp>

#include "engine/arctic_types.h"
#include "engine/vec2si32.h"

class ElipseSeet {
public:
  ElipseSeet(Window *window) : window_(window), seetCount_(0) {}

  void SeetN( Ui32 count);
   Vec2Si32 GetCoord( Ui32 number);

private:
  double ElipseLen();
   Vec2Si32 PixFromElipseCoord(double eliseCoord);

  Window *window_;
   Ui32 seetCount_;
};
