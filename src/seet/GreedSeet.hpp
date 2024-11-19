#pragma once

#include <Logs/Event/Event.hpp>
#include <window/Window.hpp>
#include <Logs/LogsReader/LogsReader.hpp>
#include "arctic/engine/vec2si32.h"

class GreedSeet {
public:
    GreedSeet(Window* window, const LogsReader& logsReader);
    arctic::Vec2Si32 GetCoord(arctic::Ui32 number);

private:
    std::vector<std::vector<ActorId>> tables_;
    std::vector<arctic::Vec2Si32> coords_;

    Window* window_;
};