#include "SpeedUpButton.hpp"

bool SpeedUpButton::IsMouseIn() const {
  arctic::Vec2Si32 curMouseCoord = GetMouseOffset();
  if (curMouseCoord.x > usePix_.front().size() || curMouseCoord.x < 0 ||
      curMouseCoord.y > usePix_.size() || curMouseCoord.y < 0) {
    return false;
  }

  if (curMouseCoord == kUndefinedMousePosition) {
    return false;
  }

  return usePix_[curMouseCoord.y][curMouseCoord.x];
}

void SpeedUpButton::Draw(const Drawer *drawer) const {
  arctic::Rgba color = arctic::Rgba(255, 0, 0);

  for (size_t i = 0; i < usePix_.size(); ++i) {
    for (size_t j = 0; j < usePix_[i].size(); ++j) {
      if (usePix_[i][j]) {
        arctic::SetPixel(drawer->GetDrawSprite(), j, i, color);
      }
    }
  }
}

void SpeedUpButton::Action() {
  CButton::Action();

  DrawPicture();
}

void SpeedUpButton::SetSprite(arctic::Sprite sprite) {
  Window::SetSprite(sprite);

  usePix_.clear();
  usePix_.resize(GetFrameSprite().Size().y);
  for (std::vector<bool>& line : usePix_) {
    line.resize(GetFrameSprite().Size().x);
  }

  DrawPicture();
}

void SpeedUpButton::DrawPicture() {
  size_t height = usePix_.size();
  size_t width = usePix_.front().size();

  size_t plusWidth = width / 10;
  size_t plusHeight = height / 10;

  size_t centerX = width / 2;
  size_t centerY = width / 2;

  for (int x = centerX - plusWidth; x < centerX + plusWidth; ++x) {
    for (int y = 0; y < height; ++y) {
      usePix_[y][x] = true;
    }
  }

  for (int y = centerY - plusHeight; y < centerY + plusHeight; ++y) {
    for (int x = 0; x < width; ++x) {
      usePix_[y][x] = true;
    }
  }
}

void SpeedUpButton::Listen() {
  GetMouse()->Listen();

  if (GetMouse()->IsLeftDownward() && IsMouseIn()) {
    Action();
  }
}
