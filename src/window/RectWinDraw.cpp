#include "RectWinDraw.hpp"
#include "analizer/src/window/IWindow.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"

arctic::Sprite RectWinDraw::GetDrawSprite() {
    return IWindow::GetFrameSprite();
}

IWindow* RectWinDraw::GetWindow() {
    return this;
}