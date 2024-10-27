#pragma once

#include "engine/arctic_types.h"
#include "engine/vec2si32.h"
#include <span>
#include <vector>
#include <string>

#include "../Event/Event.hpp"

class LogsReader {
public:
    void ReadFile(std::string fileName, size_t count = std::dynamic_extent);
    std::vector<Event> CreateLogEvents();

    const auto& GetActorsEvents() const { return actorsEvents; }
    const auto& GetEventsTime() const { return eventsTime; }
    const auto& GetEventsId() const { return eventsId; }
    const auto& GetEventsType() const { return eventsType; }

    enum class EventType {
        SEND,
        RECEIVE
    };

private:
    using EventId = arctic::Ui64;

    std::vector<std::pair<ActorId, ActorId>> actorsEvents;
    std::vector<Time> eventsTime;
    std::vector<EventId> eventsId;
    std::vector<EventType> eventsType;
};