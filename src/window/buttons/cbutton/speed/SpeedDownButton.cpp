#include "SpeedDownButton.hpp"

bool SpeedDownButton::IsMouseIn() const {
   Vec2Si32 curMouseCoord = GetMouseOffset();
  if (curMouseCoord.x > usePix_.front().size() || curMouseCoord.x < 0 ||
      curMouseCoord.y > usePix_.size() || curMouseCoord.y < 0) {
    return false;
  }

  if (curMouseCoord == kUndefinedMousePosition) {
    return false;
  }

  return usePix_[curMouseCoord.y][curMouseCoord.x];
}

void SpeedDownButton::Draw(const Drawer *drawer) const {
   Rgba color =  Rgba(0, 0, 255);

  for (size_t i = 0; i < usePix_.size(); ++i) {
    for (size_t j = 0; j < usePix_[i].size(); ++j) {
      if (usePix_[i][j]) {
         SetPixel(GetFrameSprite(), j, i, color);
      }
    }
  }
}

void SpeedDownButton::Action() {
  CButton::Action();

  DrawPicture();
}

void SpeedDownButton::SetSprite( Sprite sprite) {
  Window::SetSprite(sprite);

  usePix_.clear();
  usePix_.resize(GetFrameSprite().Size().y);
  for (std::vector<bool>& line : usePix_) {
    line.resize(GetFrameSprite().Size().x);
  }

  DrawPicture();
}

void SpeedDownButton::DrawPicture() {
  size_t height = usePix_.size();
  size_t width = usePix_.front().size();

  size_t minusHeight = height / 5;

  size_t centerX = width / 2;
  size_t centerY = height / 2;

  for (int y = centerY - minusHeight; y < centerY + minusHeight; ++y) {
    for (int x = 0; x < width; ++x) {
      usePix_[y][x] = true;
    }
  }
}

void SpeedDownButton::Listen() {
  GetMouse()->Listen();

  if (GetMouse()->IsLeftDownward() && IsMouseIn()) {
    Action();
  }
}
