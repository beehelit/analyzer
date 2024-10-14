#include "Mouse.hpp"
#include "analizer/src/camera/Camera.hpp"
#include "engine/easy_input.h"
#include "engine/vec2si32.h"
#include <memory>

#include <iostream>

bool Mouse::InWindow() {
    auto spritePos = window_->GetFrameSprite().RefPos();
    auto mousePos = arctic::MousePos();
    auto spriteSize = window_->GetFrameSprite().Size();

    // std::cout << spritePos.x << " ? " << spritePos.y << std::endl;
    // std::cout << mousePos.x << " ! " << mousePos.y << std::endl;
    // std::cout << spriteSize.x << " | " << spriteSize.y << std::endl;

    return mousePos.x > spritePos.x && mousePos.y > spritePos.y &&
           mousePos.x < spritePos.x + spriteSize.x && mousePos.y < spritePos.y + spriteSize.y;
}

void Mouse::Listen(Camera* camera) {
    static bool leftMouse = false;
    static arctic::Vec2Si32 offset = arctic::MousePos();
    if (InWindow() && arctic::IsKeyDown(arctic::KeyCode::kKeyMouseLeft)) {
        if (leftMouse) {
            camera->SetOffset(
                camera->GetOffset() +
                arctic::Vec2Si32(
                    arctic::Vec2D(offset - arctic::MousePos()) / camera->GetScaleFactor()
                )
            );
        } 

        leftMouse = true;
        offset = arctic::MousePos();
    } else {
        leftMouse = false;
    }

    if (InWindow()) {
        camera->SetScaleFactor(camera->GetScaleFactor() - arctic::MouseWheelDelta() * 0.001);
    }
}