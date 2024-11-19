#include "RectWinDraw.hpp"

#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/mouse/Mouse.hpp"
#include "analizer/src/window/MWindow/MWindow.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"
#include "analizer/src/window/Window.hpp"

#include "engine/vec2d.h"
#include "engine/vec2si32.h"

arctic::Sprite RectWinDraw::GetDrawSprite() const { return GetFrameSprite(); }

const Window *RectWinDraw::GetWindow() const { return this; }

void RectWinDraw::Listen() {
  MWindow::Listen();

  if (GetCamera()) {
    GetCamera()->Listen();

    if (IsMouseIn() && GetMouse()->IsLeftDown()) {
      if (GetMouse()->GetFlag()) {
        GetMouse()->Listen();

        GetCamera()->SetOffset(
            GetCamera()->GetOffset() +
            arctic::Vec2Si32(arctic::Vec2D(GetMouse()->GetOffset() -
                                           GetMouse()->GetSafeOffset()) /
                             GetCamera()->GetScaleFactor()));
      }

      GetMouse()->SetFlag(true);
      GetMouse()->SafeOffset();
    } else {
      GetMouse()->SetFlag(false);
    }

    if (IsMouseIn()) {
      GetCamera()->SetScaleFactor(GetCamera()->GetScaleFactor() -
                                  arctic::MouseWheelDelta() * 0.001);
    }
  }
}
