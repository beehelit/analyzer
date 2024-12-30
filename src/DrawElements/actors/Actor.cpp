#include "Actor.hpp"

#include "analizer/src/window/Drawer/Drawer.hpp"
#include "analizer/src/window/RectWinDraw.hpp"
#include "engine/arctic_types.h"
#include "engine/vec2f.h"
#include "engine/vec2si32.h"

#include <log/Logs.hpp>

using ActorId = uint64_t;

void Actor::Draw(const Drawer *drawer) const {

/*  
  if (!IsVisible()) {
    return;
  }
*/
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

  
  Ui8 alpha = 255;
  if (!IsVisible()) {
    alpha = 50;
  }

  Rgba blockColor = Rgba(128, 160, 190, alpha);
  if (active_) {
    blockColor = Rgba(255, 160, 190, alpha);
  }

    DrawBlock(
    sprite, 
    leftDownBlockCorner, 
      rightUpCorner - leftDownBlockCorner, 
    5.0,
      blockColor,
    2.0,
      Rgba(0, 0, 0));

    gFont_.Draw(drawer->GetDrawSprite(), text.c_str(), coord.x, coord.y,
                  kTextOriginTop,  kTextAlignmentLeft,
                  kDrawBlendingModeColorize,  kFilterNearest,
                  Rgba(0, 0, 0));
}
