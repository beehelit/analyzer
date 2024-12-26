#include "message.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"
#include "engine/vec2d.h"
#include "engine/vec2si32.h"

void Message::Draw(const Drawer *drawer) const {
  Actor *from = drawer->GetActorStorage()[
    drawer->GetActorIdToStorageInd().at(line_->GetFromTo().first)
  ];
  Actor *to = drawer->GetActorStorage()[
    drawer->GetActorIdToStorageInd().at(line_->GetFromTo().second)
  ];

  double len = std::sqrt((1.0 * from->GetActorCenter().x - to->GetActorCenter().x) *
                             (1.0 * from->GetActorCenter().x - to->GetActorCenter().x) +

                         (1.0 * from->GetActorCenter().y - to->GetActorCenter().y) *
                             (1.0 * from->GetActorCenter().y - to->GetActorCenter().y));

  double cur = len * progress_;

   Vec2Si32 curOffset =
      from->GetActorCenter() +
       Vec2Si32(( Vec2D(to->GetActorCenter() - from->GetActorCenter())) /
                       len * cur);

   Vec2Si32 coord = curOffset;

  Camera* camera = drawer->GetCamera();
  coord -= camera->GetOffset();

   Vec2Si32 center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

  coord.x = center.x - (center.x - coord.x) * camera->GetScaleFactor();
  coord.y = center.y - (center.y - coord.y) * camera->GetScaleFactor();

   DrawCircle(drawer->GetDrawSprite(), coord,
                     from->GetRadius() * camera->GetScaleFactor(),
                      Rgba(255, 255, 0));
}
