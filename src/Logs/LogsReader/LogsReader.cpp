#include "analizer/src/Logs/LogsReader/LogsReader.hpp"
#include "analizer/src/Logs/Event/Event.hpp"
#include "engine/easy_util.h"
#include <fstream>
#include <span>
#include <sstream>
#include <queue>
#include <set>
#include <map>

void LogsReader::ReadFile(std::string fileName, size_t count) {
    std::ifstream logIn(fileName);

    std::string logLine;
    std::vector<std::string> logLines;

    size_t readCount = 0;

    while (std::getline(logIn, logLine)) {
        if (count != std::dynamic_extent && readCount >= count) {
            break;
        }

        logLines.push_back(logLine);
        readCount++;
    }

    ActorId maxId = std::min(logLines.size() / 2, 200ul);;

    std::queue<std::pair<ActorId, ActorId>> sended;
    std::map<std::pair<ActorId, ActorId>, EventId> eventsIdMap;
    std::set<EventId> eventsIdSet;
    
    for (const auto& logLine : logLines) {
        std::stringstream logLineStream(logLine);

        std::string what;
        logLineStream >> what;
        
        std::pair<ActorId, ActorId> fromTo;
        EventId curId = arctic::Random64();

        if (what == "Receive") {
            fromTo = sended.front();
            sended.pop();
            curId = eventsIdMap[fromTo];

            eventsType.push_back(LogsReader::EventType::RECEIVE);
        } else if (what == "Send") {
            fromTo = std::make_pair(arctic::Random(0, maxId), arctic::Random(0, maxId));
            sended.push(fromTo);

            while (eventsIdSet.count(curId)) {
                curId = arctic::Random64();
            }

            eventsIdMap[fromTo] = curId;
            eventsIdSet.insert(curId);

            eventsType.push_back(LogsReader::EventType::SEND);
        } else {
            continue;
        }

        
        std::string time;
        logLineStream >> time;

        auto delTime = time.find(':');
        Time curTime = 0;
        curTime += 1ull * 60 * 1000 * (std::stoi(time.substr(delTime + 1, 2))) +
                   1ull * 1000 * (std::stoi(time.substr(delTime + 4, 2))) +
                   std::stoi(time.substr(delTime + 7, 4));

        actorsEvents.push_back(fromTo);
        eventsId.push_back(curId);
        eventsTime.push_back(curTime);
    }
}

std::vector<Event> LogsReader::CreateLogEvents() {
    std::map<EventId, Event> eventIdMap;
    std::set<EventId> sended;
    std::set<EventId> received;

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

    std::vector<Event> logEvents;

    for (auto eventId: sended) {
        if (received.contains(eventId)) {
            logEvents.push_back(eventIdMap[eventId]);
        }
    }

    return logEvents;
}

/*
using token = int64_t;
class th {
public:
    void generate() {
        while (true) {
            sleep(1000 - );
            for (int i = 0; i < N; ++i) {
                generated.fetch_add(1);
                cv.notify_one();
            }
        }
    }

    token get() {
        cv.wait(mut, [&]{
            return cur < generated;
        });

        return cur.fetch_add(1);
    }

private:
    std::atomic<token> generated = 0;
    std::atomic<token> cur = 0;

    std::condition_variable cv;
    std::mutex mut;
    std::mutex mut2;
};
*/