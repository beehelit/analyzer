#include "ElipseSeet.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"
#include "engine/vec2si32.h"

double ElipseSeet::ElipseLen() {
  // TODO for all window
  RectangleWindow* window = dynamic_cast<RectangleWindow *>(window_);
   Vec2Si32 frameSize = window->GetWindowSize();

  int widthHalf = frameSize.x / 2;
  int heightHalf = frameSize.y / 2;
  const int& a = widthHalf;
  const int& b = heightHalf;

  // ramanudjana formula
  double elipseLen =
      std::acos(-1) * (3 * (a + b) - std::sqrt((3 * a + b) * (a + 3 * b)));

  return elipseLen;
}

void ElipseSeet::SeetN( Ui32 count) { seetCount_ = count; }

 Vec2Si32 ElipseSeet::PixFromElipseCoord(double elipseCoord) {
  double radCoord = (elipseCoord / ElipseLen()) * 2 * std::acos(-1);

  // TODO for all window
  RectangleWindow* window = dynamic_cast<RectangleWindow *>(window_);
   Vec2Si32 frameSize = window->GetWindowSize();

  double x = (frameSize.x / 2.0) * std::cos(radCoord);
  double y = (frameSize.y / 2.0) * std::sin(radCoord);

  return  Vec2Si32(x + frameSize.x / 2.0, y + frameSize.y / 2.0);
}

 Vec2Si32 ElipseSeet::GetCoord( Ui32 number) {
  double elipseLen = ElipseLen();
  double delta = elipseLen / seetCount_;

  return PixFromElipseCoord(delta * number);
}
