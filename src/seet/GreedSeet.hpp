#pragma once

#include "arctic/engine/vec2si32.h"
#include <Logs/Event/Event.hpp>
#include <Logs/log_reader/LogReader.hpp>
#include <window/Window.hpp>

class GreedSeet {
public:
  GreedSeet(Window *window, const LogReader &logsReader);
  arctic::Vec2Si32 GetCoord(arctic::Ui32 number);

private:
  std::vector<std::vector<ActorId>> tables_;
  std::vector<arctic::Vec2Si32> coords_;

  Window *window_;
};
