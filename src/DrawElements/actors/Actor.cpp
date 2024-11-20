#include "Actor.hpp"

#include "analizer/src/window/Drawer/Drawer.hpp"
#include "analizer/src/window/RectWinDraw.hpp"

void Actor::Draw(const Drawer *drawer) const {
  arctic::Vec2Si32 coord = offset_;

  Camera* camera = drawer->GetCamera();
  coord -= camera->GetOffset();

  arctic::Vec2Si32 center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

  coord.x = center.x - (center.x - coord.x) * camera->GetScaleFactor();
  coord.y = center.y - (center.y - coord.y) * camera->GetScaleFactor();

  arctic::DrawCircle(drawer->GetDrawSprite(), coord,
                     radius_ * camera->GetScaleFactor(), arctic::Rgba(0, 0, 0));
}
