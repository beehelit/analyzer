#pragma once

#include "analizer/src/window/IWindow.hpp"
#include "engine/easy_input.h"
#include "engine/vec2si32.h"

class Camera;

class Mouse {
public:
    Mouse(IWindow* window) :
        window_(window) {}

    bool InWindow();

    void Listen(Camera* camera);

private:
    IWindow* window_;
};