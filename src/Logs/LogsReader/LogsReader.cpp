#include "analizer/src/Logs/LogsReader/LogsReader.hpp"
#include "analizer/src/Logs/Event/Event.hpp"
#include "engine/easy_util.h"
#include <fstream>
#include <span>
#include <sstream>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

static Time fromTimestempToTime(std::string timeStemp);

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

    std::vector<std::pair<std::string, Time>> received;
    std::vector<std::tuple<std::string, std::string, Time>> sended;
    for (const auto& logLine : logLines) {
        std::stringstream logLineStream(logLine);

        std::string what;
        logLineStream >> what;
        
        if (what == "Receive") {
            std::string from, message, time;

            logLineStream >> from >> message >> time;
            received.push_back({from, fromTimestempToTime(time)});
        } else if (what == "Send") {
            std::string from, to, message, time;

            logLineStream >> from >> to >> message >> time;
            sended.push_back({from, to, fromTimestempToTime(time)});
        }
    }

    std::sort(received.begin(), received.end());

    ActorId curId = 0;
    std::map<std::string, ActorId> actorId;

    for (auto evStr : sended) {
        std::string from, to;
        Time time = 0;

        from = std::get<0>(evStr);
        to = std::get<1>(evStr);
        time = std::get<2>(evStr);

        if (!actorId.count(from)) {
            actorId[from] = curId++;
        }

        if (!actorId.count(to)) {
            actorId[to] = curId++;
        }

        Event curEvent = {};
        curEvent.from = actorId[from];
        curEvent.to = actorId[to];
        curEvent.start = time;

        auto receivedIt = 
            std::lower_bound(received.begin(), received.end(), std::pair{from, 0});

        if (receivedIt != received.end() && receivedIt->first == from) {
            curEvent.end = receivedIt->second;
            received.erase(receivedIt);
            events_.push_back(curEvent);
        }
    }
}

static Time fromTimestempToTime(std::string timeStemp) {
    std::string tailWithMcS = timeStemp.substr(timeStemp.length() - 8);
    timeStemp.resize(timeStemp.length() - 8);
    tailWithMcS.pop_back();
    tailWithMcS.erase(tailWithMcS.begin());

    std::tm tm = {};
    std::stringstream tsStream(timeStemp);
    tsStream >> std::get_time(&tm, "%Y-%m-%dT%H%N%S");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    Time cur = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
    cur *= 1'000'000;
    cur += std::stoi(tailWithMcS);

    return cur;
}