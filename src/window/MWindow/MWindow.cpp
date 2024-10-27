#include "MWindow.hpp"
#include "engine/vec2si32.h"

bool MWindow::IsMouseIn() const {
    if (!mouse_) {
        return false;
    }

    auto mouse = *mouse_;

    auto spritePos = GetFrameSprite().RefPos();
    auto mousePos = mouse->GetOffset();
    auto spriteSize = GetFrameSprite().Size();

    return mousePos.x > spritePos.x && mousePos.y > spritePos.y &&
           mousePos.x < spritePos.x + spriteSize.x && mousePos.y < spritePos.y + spriteSize.y;
}

arctic::Vec2Si32 MWindow::GetMouseOffset() const {
    if (!IsMouseIn()) {
        return UNDEFINED_MOUSE_POSITION;
    }

    auto mouse = *mouse_;

    auto spritePos = GetFrameSprite().RefPos();
    auto mousePos = mouse->GetOffset();

    return mousePos - spritePos;
}