#include "RectWinDraw.hpp"

#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/mouse/Mouse.hpp"
#include "analizer/src/window/MWindow/MWindow.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"
#include "analizer/src/window/Window.hpp"

#include "engine/rgba.h"
#include "engine/vec2d.h"
#include "engine/vec2si32.h"
#include "seet/GreedSeet.hpp"

#include <iostream>

arctic::Sprite RectWinDraw::GetDrawSprite() const { return GetFrameSprite(); }
void RectWinDraw::SetDrawSprite(arctic::Sprite sprite) { SetSprite(sprite); }

const Window *RectWinDraw::GetWindow() const { return this; }

void RectWinDraw::Draw() const {
  arctic::DrawRectangle(GetDrawSprite(), arctic::Vec2Si32(0, 0),
                        GetDrawSprite().Size(), backgroundColor_);

  Drawer::Draw();

  for (const Actor* actor : GetActorStorage()) {
    const std::map<ActorId, std::string_view>& idToType = Logs::GetActorIdToActorType();
    std::string text = static_cast<std::string>(idToType.at(actor->GetId()));

    arctic::Vec2Si32 coord = actor->GetOffset();
    Camera* camera = GetCamera();
    coord -= camera->GetOffset();

    arctic::Vec2Si32 center = GetWindow()->GetFrameSprite().Size() / 2;

    coord.x = center.x - (center.x - coord.x) * camera->GetScaleFactor();
    coord.y = center.y - (center.y - coord.y) * camera->GetScaleFactor();

    gFont_.Draw(GetDrawSprite(), text.c_str(), coord.x, coord.y,
                arctic::kTextOriginTop, arctic::kTextAlignmentLeft,
                arctic::kDrawBlendingModeColorize, arctic::kFilterNearest,
                arctic::Rgba(0, 255, 0));
  }
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
/*
      const std::vector<Actor*>& actorStorage = GetActorStorage();
      for (const Actor* actor : actorStorage) {
        arctic::Vec2Si32 coord = actor->GetOffset();
        Camera* camera = GetCamera();
        coord -= camera->GetOffset();

        arctic::Vec2Si32 center = GetWindow()->GetFrameSprite().Size() / 2;

        coord.x = center.x - (center.x - coord.x) * camera->GetScaleFactor();
        coord.y = center.y - (center.y - coord.y) * camera->GetScaleFactor();

        arctic::Si32 radius = actor->GetRadius();

        arctic::Vec2Si32 mouseOffset = GetMouseOffset();
        if (std::sqrt((1.0 * coord.x - mouseOffset.x) * (1.0 * coord.x - mouseOffset.x) +
            (1.0 * coord.y - mouseOffset.y) * (1.0 * coord.y - mouseOffset.y)) <= radius) {
          
          // LogReader* lr = GetLogReader();
          GreedSeet* gs = GetGreedSeet();

          ActorId id = gs->GetId(coord);

          std::string_view text = Logs::GetActorIdToActorType().at(id);
          arctic::Si32 windowHeight = GetWindow()->GetFrameSprite().Size().y;
          arctic::Font gFont_;
          gFont_.Load("data/arctic_one_bmf.fnt");

          gFont_.Draw(GetDrawSprite(), std::string(text).c_str(), GetMouseOffset().x, GetMouseOffset().y,
                      arctic::kTextOriginTop, arctic::kTextAlignmentLeft,
                      arctic::kDrawBlendingModeColorize, arctic::kFilterNearest,
                      arctic::Rgba(0, 255, 0));
        }
      }
*/
    }
  }
}

void RectWinDraw::SetBackgroundColor(arctic::Rgba color) {
  backgroundColor_ = color;
}