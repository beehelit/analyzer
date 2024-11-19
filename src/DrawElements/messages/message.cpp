#include "message.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"
#include "engine/vec2d.h"
#include "engine/vec2si32.h"

void Message::Draw(const Drawer *drawer) const {
  Actor *from = drawer->GetActorStorage()[line_->GetFromTo().first];
  Actor *to = drawer->GetActorStorage()[line_->GetFromTo().second];

  double len = std::sqrt((1.0 * from->GetOffset().x - to->GetOffset().x) *
                             (1.0 * from->GetOffset().x - to->GetOffset().x) +

                         (1.0 * from->GetOffset().y - to->GetOffset().y) *
                             (1.0 * from->GetOffset().y - to->GetOffset().y));

  double cur = len * progress_;

  arctic::Vec2Si32 curOffset =
      from->GetOffset() +
      arctic::Vec2Si32((arctic::Vec2D(to->GetOffset() - from->GetOffset())) /
                       len * cur);

  auto coord = curOffset;

  auto camera = drawer->GetCamera();
  coord -= camera->GetOffset();

  auto center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

  coord.x = center.x - (center.x - coord.x) * camera->GetScaleFactor();
  coord.y = center.y - (center.y - coord.y) * camera->GetScaleFactor();

  arctic::DrawCircle(drawer->GetDrawSprite(), coord,
                     from->GetRadius() * 2.0 * camera->GetScaleFactor(),
                     arctic::Rgba(255, 255, 0));
}