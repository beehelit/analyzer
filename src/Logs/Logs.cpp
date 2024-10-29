#include "Logs.hpp"
#include "analizer/src/Logs/Event/Event.hpp"

#include <map>
#include <set>

Logs::Logs(const LogsReader& logsReader) {
    std::map<EventId, Event> eventIdMap;
    std::set<EventId> sended;
    std::set<EventId> received;

    const auto& eventsType = logsReader.GetEventsType();
    const auto& eventsId = logsReader.GetEventsId();
    const auto& actorsEvents = logsReader.GetActorsEvents();
    const auto& eventsTime = logsReader.GetEventsTime();

    for (size_t i = 0; i < eventsType.size(); ++i) {
        switch (eventsType[i]) {
            case LogsReader::EventType::SEND: {
                eventIdMap[eventsId[i]].from = actorsEvents[i].first;
                eventIdMap[eventsId[i]].to = actorsEvents[i].second;
                eventIdMap[eventsId[i]].start = eventsTime[i];
                eventIdMap[eventsId[i]].id = eventsId[i];

                sended.insert(eventsId[i]);
                break;
            }

            case LogsReader::EventType::RECEIVE: {
                eventIdMap[eventsId[i]].end = eventsTime[i];

                received.insert(eventsId[i]);
                break;
            }
        }
    }

    for (auto eventId: sended) {
        if (received.contains(eventId)) {
            events.push_back(eventIdMap[eventId]);
        }
    }
}

size_t Logs::GetActorsCount() const {
    std::set<ActorId> actorsIds;
    for (const auto& event : events) {
        actorsIds.insert(event.from);
        actorsIds.insert(event.to);
    }

    return actorsIds.size();
}

Time Logs::GetMaxTime() const {
    auto ret = events[0].end;

    for (auto event : events) {
        ret = std::max(event.end, ret);
    }

    return ret;
}

void Logs::Normalize() {
    auto minTime = events[0].start;
    for (auto event : events) {
        minTime = std::min(minTime, event.start);
    }

    for (auto& event : events) {
        event.start -= minTime;
        event.end -= minTime;
    }
}