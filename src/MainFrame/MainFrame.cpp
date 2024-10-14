#include "MainFrame.hpp"

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "engine/arctic_types.h"
#include "engine/easy.h"
#include "engine/easy_advanced.h"
#include "engine/easy_drawing.h"
#include "engine/easy_input.h"
#include "engine/easy_sprite.h"
#include "engine/easy_util.h"
#include "engine/rgb.h"
#include "engine/vec2si32.h"
#include <cmath>
#include <memory>
#include <iostream>
#include <set>

#include "../DrawElements/actors/Actor.hpp"

arctic::Sprite MainFrame::mainFrameSprite_ = arctic::Sprite();
std::vector<IDrawElement*> MainFrame::drawElements_ = std::vector<IDrawElement*>();
arctic::Vec2Si32 MainFrame::cameraOffset_ = arctic::Vec2Si32(0, 0);
double MainFrame::scaleFactor_ = 1.0;
arctic::Vec2Si32 MainFrame::mouseOffset_ = arctic::Vec2Si32(0, 0);
std::vector<arctic::Si32> MainFrame::actorNumbers_ = std::vector<arctic::Si32>();

void MainFrame::DrawFrame() {
    auto white = arctic::Rgba(255, 255, 255);

    arctic::DrawLine(mainFrameSprite_, 
                    arctic::Vec2Si32(0, 0), 
                    arctic::Vec2Si32(FrameSize().x - 1, 0), 
                    white);

    arctic::DrawLine(mainFrameSprite_,
                     arctic::Vec2Si32(0, 0),
                     arctic::Vec2Si32(0, FrameSize().y - 1),
                     white);

    arctic::DrawLine(mainFrameSprite_,
                     arctic::Vec2Si32(0, FrameSize().y - 1),
                     arctic::Vec2Si32(FrameSize().x - 1, FrameSize().y - 1),
                     white);

    arctic::DrawLine(mainFrameSprite_,
                     arctic::Vec2Si32(FrameSize().x - 1, FrameSize().y - 1),
                     arctic::Vec2Si32(FrameSize().x - 1, 0),
                     white);
}

arctic::Vec2Si32 MainFrame::FrameSize() {
    return arctic::Vec2Si32{arctic::ScreenSize().x - 2 * (arctic::ScreenSize().x / kSides_div),
                            arctic::ScreenSize().y - 
                                ((arctic::ScreenSize().y / kBottom_div)
                                 + (arctic::ScreenSize().y / kTop_div))};
}

double MainFrame::ElipseLen() {
    auto frame_size = FrameSize();

    auto width_half = frame_size.x / 2;
    auto height_half = frame_size.y / 2;
    const auto& a = width_half;
    const auto& b = height_half;

    // ramanudjana formula
    double elipse_len = std::acos(-1) * (3*(a+b) - std::sqrt((3*a + b) * (a + 3*b)));

    return elipse_len;
}

arctic::Vec2Si32 MainFrame::PixFromElipseCoord(double elipse_coord) {
    double rad_coord = (elipse_coord / ElipseLen()) * 2 * std::acos(-1);    

    double x = (FrameSize().x / 2.0) * std::cos(rad_coord);
    double y = (FrameSize().y / 2.0) * std::sin(rad_coord);

    return arctic::Vec2Si32(x + FrameSize().x / 2.0, y + FrameSize().y / 2.0);
}

void MainFrame::DrawElipse() {
    double elipse_len = ElipseLen();
    for (int cur = 0; cur < elipse_len; cur += 1) {
        auto coord = PixFromElipseCoord(cur);
        arctic::SetPixel(mainFrameSprite_, coord.x, coord.y, arctic::Rgba(255, 255, 0));
    }
}

void MainFrame::CreateMainFrame() {
    auto screen_size = arctic::ScreenSize();

    auto margin_sides = screen_size.x / kSides_div;
    auto margin_top = screen_size.y / kTop_div;
    auto margin_bottom = screen_size.y / kBottom_div;

    auto left_top_ang = arctic::Vec2Si32(margin_sides, screen_size.y - margin_top);
    auto left_bottom_ang = arctic::Vec2Si32(margin_sides, margin_bottom);

    mainFrameSprite_.Reference(arctic::GetEngine()->GetBackbuffer(), 
                               left_bottom_ang,
                               FrameSize());
}

bool MainFrame::CheckMouseIn() {
    auto left_bottom_ang = arctic::Vec2Si32(arctic::ScreenSize().x / kSides_div,
                                                            arctic::ScreenSize().y / kBottom_div);
    
    auto pos = arctic::MousePos();

    return (pos.x > left_bottom_ang.x && pos.y > left_bottom_ang.y) &&
           (pos.x < left_bottom_ang.x + FrameSize().x && pos.y < left_bottom_ang.y + FrameSize().y);
}

void MainFrame::DrawNCircles(arctic::Ui32 count) {
    auto elipse_len = ElipseLen();
    auto width = elipse_len / count;
    arctic::Si32 rad = width / 4;

    for (arctic::Ui32 i = 0; i < count; ++i) {
        auto coord = PixFromElipseCoord(width * i);

        AddDrawElement(new Actor(coord, rad));
        ActorAdded();
    }
}

void MainFrame::DrawElements() {
    for (auto element : drawElements_) {
        element->Draw();
    }
}

void MainFrame::AddDrawElement(IDrawElement* drawElement) {
    drawElements_.push_back(drawElement);
}

void MainFrame::EraseElements() {
    for (auto element : drawElements_) {
        delete element;
    }

    drawElements_.clear();
    actorNumbers_.clear();
}