#pragma once

#include "LogsReader/LogsReader.hpp"
#include "analizer/src/Logs/Event/Event.hpp"
#include <_types/_uint64_t.h>

class Logs {
public:
    Logs(const LogsReader& logsReader);

    const std::vector<Event>& GetEvents() const {
        return events;
    }

    size_t GetActorsCount() const;
    Time GetMaxTime() const;

    void Normalize();

    ~Logs() = default;
private:
    Logs() = delete;
    Logs(const Logs&) = delete;

    std::vector<Event> events;
};