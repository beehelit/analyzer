#include "DrawBox.hpp"
#include "DrawElements/IDrawElement.hpp"
#include "arctic/engine/vec2si32.h"
#include "engine/arctic_types.h"
#include "engine/easy_drawing.h"
#include "window/Drawer/DrawBoxOptions.hpp"

#include <utility>

#include <iostream>

void DrawBox::DrawWithOption() const {
    arctic::DrawRectangle(
        space_, 
        arctic::Vec2Si32(0, 0), 
        GetDrawSprite().Size(),
        options_.background_color);

    if (drawElement_) {
        if (IDrawElement::IsWindowed(drawElement_->GetDrawElementType())) {
            Window* window = dynamic_cast<Window*>(drawElement_);
            window->SetSprite(GetDrawSprite());
/*
            std::cout << GetDrawSprite().Size().x << " " << GetDrawSprite().Size().y << std::endl;
            std::cout << GetDrawSprite().RefPos().x << " " << GetDrawSprite().RefPos().y << std::endl;
            std::cout << std::endl;
*/
        }

        drawElement_->Draw(this);
        return;
    }

    if (drawers_.empty()) {
        return;
    }

    DrawBoxOptions curOptions = options_;

    if (curOptions.flex_list.empty()) {
        size_t countDrawers = drawers_.size();
        double samePart = 1.0 / countDrawers;

        for (size_t i = 0; i < countDrawers; ++i) {
            curOptions.flex_list.push_back(samePart);
        }
    }

    arctic::Sprite curSpace = space_;
    arctic::Si32 width = curSpace.Width();
    arctic::Si32 height = curSpace.Height();

    if (curOptions.flex_type == "row") {
        std::vector<std::pair<arctic::Si32, arctic::Si32>> widthBorders;
        widthBorders.reserve(curOptions.flex_list.size());

        std::vector<arctic::Sprite> drawerSprites_;
        drawerSprites_.resize(curOptions.flex_list.size());

        widthBorders.emplace_back(0, (arctic::Si32)(width * curOptions.flex_list[0]));        

        for (size_t curWidthBorderNum = 1; 
             curWidthBorderNum < curOptions.flex_list.size();
             ++curWidthBorderNum) {
            widthBorders.emplace_back(widthBorders.back().second+1,
                widthBorders.back().second + width * curOptions.flex_list[curWidthBorderNum]);

            if (curWidthBorderNum == curOptions.flex_list.size() - 1) {
                widthBorders.back().second = width;
            }
        }

        for (size_t curWidthBorderNum = 0;
             curWidthBorderNum < curOptions.flex_list.size();
             ++curWidthBorderNum) {
            drawerSprites_[curWidthBorderNum].Reference(curSpace,
                arctic::Vec2Si32(widthBorders[curWidthBorderNum].first, 0),
                arctic::Vec2Si32(widthBorders[curWidthBorderNum].second, curSpace.Height())
            );

            drawers_[curWidthBorderNum]->SetDrawSprite(drawerSprites_[curWidthBorderNum]);
        }
    } else if (curOptions.flex_type == "column") {
        std::vector<std::pair<arctic::Si32, arctic::Si32>> heightBorders;
        heightBorders.reserve(curOptions.flex_list.size());

        std::vector<arctic::Sprite> drawerSprites_;
        drawerSprites_.resize(curOptions.flex_list.size());

        heightBorders.emplace_back(0, (arctic::Si32)(height * curOptions.flex_list[0]));        

        for (size_t curHeightBorderNum = 1; 
             curHeightBorderNum < curOptions.flex_list.size();
             ++curHeightBorderNum) {
            heightBorders.emplace_back(heightBorders.back().second+1,
                heightBorders.back().second + height*curOptions.flex_list[curHeightBorderNum]);

            if (curHeightBorderNum == curOptions.flex_list.size() - 1) {
                heightBorders.back().second = height;
            }
        }

        for (size_t curHeightBorderNum = 0;
             curHeightBorderNum < curOptions.flex_list.size();
             ++curHeightBorderNum) {
            drawerSprites_[curHeightBorderNum].Reference(curSpace,
                arctic::Vec2Si32(0, heightBorders[curHeightBorderNum].first),
                arctic::Vec2Si32(curSpace.Width(), heightBorders[curHeightBorderNum].second)
            );

            drawers_[curHeightBorderNum]->SetDrawSprite(drawerSprites_[curHeightBorderNum]);
        }
    }

    for (const Drawer* drawer : drawers_) {
        drawer->Draw();
    }
}
