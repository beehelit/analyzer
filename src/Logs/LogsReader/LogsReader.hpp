#pragma once

#include "engine/arctic_types.h"
#include "engine/vec2si32.h"
#include <span>
#include <vector>
#include <string>
#include <map>

#include "../Event/Event.hpp"

class LogsReader {
public:
    void ReadFile(std::string fileName, size_t count = std::dynamic_extent);
    std::vector<Event>&& MoveEvents() {
        return std::move(events_);
    }

private:
    using EventId = arctic::Ui64;

    std::vector<Event> events_;
};