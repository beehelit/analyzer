#include "RectWinDraw.hpp"

#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/mouse/Mouse.hpp"
#include "analizer/src/window/MWindow/MWindow.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"
#include "analizer/src/window/Window.hpp"

#include "engine/easy_drawing.h"
#include "engine/rgba.h"
#include "engine/vec2d.h"
#include "engine/vec2f.h"
#include "engine/vec2si32.h"
#include "seet/GreedSeet.hpp"

#include <iostream>

 Sprite RectWinDraw::GetDrawSprite() const { return GetFrameSprite(); }
void RectWinDraw::SetDrawSprite( Sprite sprite) { SetSprite(sprite); }

const Window *RectWinDraw::GetWindow() const { return this; }

const std::vector< Rgba> layersColors_ = {
   Rgba(245, 120, 145, 40),
   Rgba(0, 0, 253, 30),
   Rgba(0, 130, 50, 10),
   Rgba(230, 7, 7, 82)
};

const std::vector<std::string> layersNames_ = {
  "PDisk",
  "VDisk",
  "BSQueue",
  "DSProxy"
};

void RectWinDraw::Draw() const {
   DrawRectangle(GetDrawSprite(),  Vec2Si32(0, 0),
                        GetDrawSprite().Size(), backgroundColor_);

  if (gs_) {
    const GreedSeet* gs = *gs_;

    const std::vector<ActorTable>& actorTables = gs->GetActorTables();
    for (size_t actorTableNum = 1; actorTableNum < actorTables.size(); ++actorTableNum) {
       Vec2Si32 leftDownCorner(
        actorTables[actorTableNum].GetXAdd() - 50, 
        actorTables[actorTableNum].GetYAdd() - 150);
      
       Vec2Si32 rightUpCorner = 
        leftDownCorner +  Vec2Si32(actorTables[actorTableNum].GetLineLength(),
        -leftDownCorner.y + actorTables[actorTableNum].GetY());

      Camera* camera = GetCamera();
       Vec2Si32 center = GetWindow()->GetFrameSprite().Size() / 2;

      leftDownCorner -= camera->GetOffset();
      rightUpCorner -= camera->GetOffset();

      leftDownCorner.x = center.x - (center.x - leftDownCorner.x) * camera->GetScaleFactor();
      leftDownCorner.y = center.y - (center.y - leftDownCorner.y) * camera->GetScaleFactor();
      
      rightUpCorner.x = center.x - (center.x - rightUpCorner.x) * camera->GetScaleFactor();
      rightUpCorner.y = center.y - (center.y - rightUpCorner.y) * camera->GetScaleFactor();

       DrawRectangle(GetDrawSprite(), leftDownCorner, rightUpCorner, layersColors_[actorTableNum-1]);

      gFont_.Draw(GetDrawSprite(), layersNames_[actorTableNum-1].c_str(), 
      leftDownCorner.x, leftDownCorner.y + 30,
                    kTextOriginTop,  kTextAlignmentLeft,
                    kDrawBlendingModeColorize,  kFilterNearest,
                    Rgba(160, 0, 0));
    }
  }

  Drawer::Draw();
}

void RectWinDraw::Listen() {
  MWindow::Listen();

  if (GetCamera()) {
    GetCamera()->Listen();

    if (IsMouseIn() && GetMouse()->IsLeftDown()) {
      if (GetMouse()->GetFlag()) {
        GetMouse()->Listen();

        GetCamera()->SetOffset(
            GetCamera()->GetOffset() +
             Vec2Si32( Vec2D(GetMouse()->GetOffset() -
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
                                   MouseWheelDelta() * 0.001);
    }
  }
}

void RectWinDraw::SetBackgroundColor( Rgba color) {
  backgroundColor_ = color;
}