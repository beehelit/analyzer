#include "MWindow.hpp"
#include "engine/vec2si32.h"

arctic::Vec2Si32 MWindow::GetMouseOffset() const {
    auto mouse = *mouse_;

    auto spritePos = GetFrameSprite().RefPos();
    auto mousePos = mouse->GetOffset();

    return mousePos - spritePos;
}
