#pragma once

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/window/IWindow.hpp"
#include "engine/easy_sprite.h"
#include <memory>

class Drawer {
public:
    void Draw();
    void AddDrawElement(IDrawElement* drawElement);

    Drawer(std::shared_ptr<Camera> camera) :
        camera_(camera) {}
        
    virtual arctic::Sprite GetDrawSprite() = 0;
    virtual IWindow* GetWindow() = 0;

    auto GetCamera() { return camera_; }

    ~Drawer();

private:
    Drawer(const Drawer&) = delete;
    Drawer() = delete;

    std::vector<IDrawElement*> drawStorage_;
    std::shared_ptr<Camera> camera_;
};