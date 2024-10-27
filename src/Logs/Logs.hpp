#pragma once

#include "LogsReader/LogsReader.hpp"
#include "analizer/src/Logs/Event/Event.hpp"

class Logs {
public:
    Logs(const LogsReader& logsReader);

    const std::vector<Event>& GetEvents() const {
        return events;
    }

    size_t GetActorsCount() const;

    ~Logs() = default;
private:
    Logs() = delete;
    Logs(const Logs&) = delete;

    std::vector<Event> events;
};