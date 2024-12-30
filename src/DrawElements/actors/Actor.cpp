#include "Actor.hpp"

#include "analizer/src/window/Drawer/Drawer.hpp"
#include "analizer/src/window/RectWinDraw.hpp"
#include "engine/vec2f.h"
#include "engine/vec2si32.h"

#include <log/Logs.hpp>

using ActorId = uint64_t;

void Actor::Draw(const Drawer *drawer) const {
  if (!IsVisible()) {
    return;
  }

  const std::map<ActorId, std::string_view>& idToType = Logs::GetActorIdToActorType();
  std::string text = static_cast<std::string>(idToType.at(GetId()));  

  Vec2Si32 coord = offset_;

  Camera* camera = drawer->GetCamera();
  coord -= camera->GetOffset();

  Vec2Si32 center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

  coord.x = center.x - (center.x - coord.x) * camera->GetScaleFactor();
  coord.y = center.y - (center.y - coord.y) * camera->GetScaleFactor();

  Sprite sprite = drawer->GetDrawSprite();

    Vec2Si32 typeBlockSize = gFont_.EvaluateSize(text.c_str(), false);
    Vec2F leftDownBlockCorner = Vec2F(coord) -  Vec2F(8, 40);
    Vec2F rightUpCorner = Vec2F(coord + typeBlockSize) -  Vec2F(-5, 20);
/*
  leftDownBlockCorner -= Vec2F(camera->GetOffset());
  rightUpCorner -= Vec2F(camera->GetOffset());

  leftDownBlockCorner.x = center.x - (center.x - leftDownBlockCorner.x) * camera->GetScaleFactor();
  leftDownBlockCorner.y = center.y - (center.y - leftDownBlockCorner.y) * camera->GetScaleFactor();

  rightUpCorner.x = center.x - (center.x - rightUpCorner.x) * camera->GetScaleFactor();
  rightUpCorner.y = center.y - (center.y - rightUpCorner.y) * camera->GetScaleFactor();
*/

/*
  coord -= camera->GetOffset();
  coord.x = center.x - (center.x - coord.x) * camera->GetScaleFactor();
  coord.y = center.y - (center.y - coord.y) * camera->GetScaleFactor();
*/

    DrawBlock(
    sprite, 
    leftDownBlockCorner, 
      rightUpCorner - leftDownBlockCorner, 
    5.0,
      Rgba(128, 160, 190),
    2.0,
      Rgba(0, 0, 0));

    gFont_.Draw(drawer->GetDrawSprite(), text.c_str(), coord.x, coord.y,
                  kTextOriginTop,  kTextAlignmentLeft,
                  kDrawBlendingModeColorize,  kFilterNearest,
                  Rgba(0, 0, 0));
}
