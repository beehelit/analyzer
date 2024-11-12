#include "Logs.hpp"
#include "analizer/src/Logs/Event/Event.hpp"

#include <map>
#include <set>

size_t Logs::GetActorsCount() const {
    std::set<ActorId> actorsIds;
    for (const auto& event : events_) {
        actorsIds.insert(event.from);
        actorsIds.insert(event.to);
    }

    return actorsIds.size();
}

Time Logs::GetMaxTime() const {
    auto ret = events_[0].end;

    for (auto event : events_) {
        ret = std::max(event.end, ret);
    }

    return ret;
}

void Logs::Normalize() {
    auto minTime = events_[0].start;
    for (auto event : events_) {
        minTime = std::min(minTime, event.start);
    }

    for (auto& event : events_) {
        event.start -= minTime;
        event.end -= minTime;
    }
}