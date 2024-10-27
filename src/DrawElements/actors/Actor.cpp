#include "Actor.hpp"

#include "analizer/src/window/Drawer/Drawer.hpp"
#include "analizer/src/window/RectWinDraw.hpp"

void Actor::Draw(Drawer* drawer) const {
    auto coord = offset_;

    auto camera = drawer->GetCamera();
    coord -= camera->GetOffset();

    // TODO - mouse offset

    // TODO for any window, now only for Rectangle
    auto* window = dynamic_cast<RectWinDraw*>(drawer->GetWindow());
    auto center = window->GetWindowSize() / 2;

    coord.x = center.x - (center.x - coord.x) * camera->GetScaleFactor();
    coord.y = center.y - (center.y - coord.y) * camera->GetScaleFactor();

    arctic::DrawCircle(drawer->GetDrawSprite(), 
                        coord, 
                        radius_ * camera->GetScaleFactor(), 
                        arctic::Rgba(0, 0, 0));
}