#include "analizer/src/Logs/LogsReader/LogsReader.hpp"
#include "analizer/src/Logs/Event/Event.hpp"
#include "engine/easy_util.h"
#include <algorithm>
#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <span>
#include <sstream>

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

  std::vector<std::tuple<std::string, Time, std::string>> received;
  std::vector<std::tuple<std::string, std::string, Time>> sended;
  for (const auto &logLine : logLines) {
    std::stringstream logLineStream(logLine);

    std::string what;
    logLineStream >> what;

    if (what == "Receive") {
      std::string actorName, to, message, time;

      logLineStream >> actorName >> to >> message >> time;
      received.push_back({to, fromTimestempToTime(time), actorName});
    } else if (what == "Send") {
      std::string to, from, message, time;

      logLineStream >> to >> from >> message >> time;
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

    auto receivedIt = std::lower_bound(received.begin(), received.end(),
                                       std::tuple{to, 0, ""});

    if (receivedIt != received.end() && std::get<0>(*receivedIt) == to) {
      curEvent.end = std::get<1>(*receivedIt);
      actorIdName_[actorId[to]] = std::get<2>(*receivedIt);
      received.erase(receivedIt);
      events_.push_back(curEvent);
    }
  }

  for (auto it : actorIdName_) {
    nameActorId_[it.second].push_back(it.first);
  }
}

void LogsReader::ReadConfig(std::string fileName, Config cfg) {
  switch (cfg) {
  case Config::SEET: {
    std::ifstream seetIn(fileName);

    std::string actorName;
    size_t actorSeet;
    while (seetIn >> actorName) {
      seetIn >> actorSeet;

      actorNameSeet_[actorName] = actorSeet;
    }
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

  Time cur =
      std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch())
          .count();
  cur *= 1'000'000;
  cur += std::stoi(tailWithMcS);

  return cur;
}