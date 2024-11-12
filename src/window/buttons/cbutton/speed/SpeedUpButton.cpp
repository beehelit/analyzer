#include "SpeedUpButton.hpp"

bool SpeedUpButton::IsMouseIn() const {
    auto curMouseCoord = GetMouseOffset();
    if (curMouseCoord.x > usePix_.front().size() || curMouseCoord.x < 0 ||
        curMouseCoord.y > usePix_.size() || curMouseCoord.y < 0) {
        return false;
    }

    if (curMouseCoord == kUndefinedMousePosition) {
        return false;
    }

    return usePix_[curMouseCoord.y][curMouseCoord.x];    
}

void SpeedUpButton::Draw(const Drawer* drawer) const {
    auto color = arctic::Rgba(255, 0, 0);

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
    for (auto& line : usePix_) {
        line.resize(GetFrameSprite().Size().x);
    }

    DrawPicture();
}

void SpeedUpButton::DrawPicture() {
    auto height = usePix_.size();
    auto width = usePix_.front().size();

    auto plusWidth = width / 10;
    auto plusHeight = height / 10;

    auto centerX = width / 2;
    auto centerY = width / 2;


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