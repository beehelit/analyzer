#include "message.hpp"
#include "analizer/src/window/Drawer/Drawer.hpp"
#include "engine/vec2d.h"
#include "engine/vec2si32.h"

void Message::Draw(const Drawer *drawer) const {
  Actor *from = drawer->GetActorStorage()[
    drawer->GetActorIdToStorageInd().at(line_->GetFromTo().first)
  ];
  Camera* camera = drawer->GetCamera();

  Vec2Si32 coord = line_->GetTransportLinePoint(drawer, progress_);

   DrawCircle(drawer->GetDrawSprite(), coord,
                     from->GetRadius() * camera->GetScaleFactor(),
                      Rgba(255, 255, 0));
}
