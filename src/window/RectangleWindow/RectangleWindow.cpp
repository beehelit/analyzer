#include "RectangleWindow.hpp"
#include "engine/easy_drawing.h"
#include "engine/vec2si32.h"
#include <stdexcept>

void RectangleWindow::Fill(arctic::Rgba color) {
    auto rightCorner = GetWindowSize();
    rightCorner.x--;
    rightCorner.y--;

    auto leftCorner = arctic::Vec2Si32(0, 0);

    arctic::DrawRectangle(GetFrameSprite(), leftCorner, rightCorner, color);
}