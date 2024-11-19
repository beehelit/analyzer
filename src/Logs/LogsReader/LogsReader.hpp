#pragma once

#include "engine/arctic_types.h"
#include "engine/vec2si32.h"
#include <span>
#include <vector>
#include <string>
#include <map>

#include <Logs/Event/Event.hpp>

enum class Config {
    SEET
};

class LogsReader {
public:
    void ReadFile(std::string fileName, size_t count = std::dynamic_extent);
    std::vector<Event>&& MoveEvents() {
        return std::move(events_);
    }

    void ReadConfig(std::string fileName, Config cfg);

    auto GetSeetInfo() const {
        return actorNameSeet_;
    }

    auto GetActorIdName() const {
        return actorIdName_;
    }

    auto GetNameActorId() const {
        return nameActorId_;
    }

private:
    using EventId = arctic::Ui64;

    std::vector<Event> events_;
    std::map<std::string, size_t> actorNameSeet_;
    std::map<ActorId, std::string> actorIdName_;
    std::map<std::string, std::vector<ActorId>> nameActorId_;
};