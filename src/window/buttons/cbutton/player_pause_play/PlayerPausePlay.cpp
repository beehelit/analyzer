#include "PlayerPausePlay.hpp"
#include "analizer/src/window/MWindow/MWindow.hpp"
#include "engine/easy_drawing.h"
#include "engine/rgba.h"
#include "engine/vec2si32.h"

bool PlayerPausePlay::IsMouseIn() const {
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

void PlayerPausePlay::Draw(const Drawer* drawer) const {
    auto color = (!isActive_) ? arctic::Rgba(0, 255, 0) :
                                      arctic::Rgba(255, 0, 0);

    for (size_t i = 0; i < usePix_.size(); ++i) {
        for (size_t j = 0; j < usePix_[i].size(); ++j) {
            if (usePix_[i][j]) {
                arctic::SetPixel(drawer->GetDrawSprite(), j, i, color);
            }
        }
    }
}

void PlayerPausePlay::Action() {
    CButton::Action();
    isActive_ = !isActive_;

    DrawPicture();
}

void PlayerPausePlay::SetSprite(arctic::Sprite sprite) {
    Window::SetSprite(sprite);

    usePix_.clear();
    usePix_.resize(GetFrameSprite().Size().y);
    for (auto& line : usePix_) {
        line.resize(GetFrameSprite().Size().x);
    }

    DrawPicture();
}

void PlayerPausePlay::DrawPicture() {
    auto height = usePix_.size();
    auto width = usePix_.front().size();

    auto paddingWidth = usePix_.front().size() / 10;
    auto paddingHeight = usePix_.size() / 10;

    int del = 0;
    int x = paddingWidth;

    int pauseBarWidth = paddingWidth * 2;
    if (!isActive_) { // play Icon
        while (height > 2 * del) {
            for (int y = paddingHeight + del; y < height - del - paddingHeight; ++y) {
                usePix_[y][x] = true;
            }
            x++;
            del++;
        }
    } else { // pause Icon
    
        for (int x = paddingWidth; x < paddingWidth + pauseBarWidth; ++x) {
            for (int y = paddingHeight; y < height - paddingHeight; ++y) {
                usePix_[y][x] = true;
            }
        }
    
        for (int x = width - paddingWidth; x > width - paddingWidth - pauseBarWidth; --x) {
            for (int y = paddingHeight; y < height - paddingHeight; ++y) {
                usePix_[y][x] = true;
            }
        }
    }
}

void PlayerPausePlay::Listen() {
    GetMouse()->Listen();

    if (GetMouse()->IsLeftDownward() && IsMouseIn()) {
        Action();
    }
}