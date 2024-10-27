#pragma once

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/window/Window.hpp"
#include "analizer/src/DrawElements/actors/Actor.hpp"

#include "engine/easy_sprite.h"

#include <memory>

class Drawer {
public:
    void Draw();
    void AddDrawElement(IDrawElement* drawElement);
     
    virtual arctic::Sprite GetDrawSprite() = 0;
    virtual Window* GetWindow() = 0;

    void SetCamera(Camera* camera) {
        camera_ = camera;
    }

    Camera* GetCamera() { 
        if (camera_ == std::nullopt) {
            return nullptr;
        }

        return *camera_;
    }

    const auto& GetActorStorage() { return actorStorage_; }

    ~Drawer();
    Drawer() = default;

private:
    Drawer(const Drawer&) = delete;

    std::vector<IDrawElement*> drawStorage_;
    std::optional<Camera*> camera_;

    std::vector<Actor*> actorStorage_;
};