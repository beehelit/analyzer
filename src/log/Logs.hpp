#pragma once

#include <log/log_reader/LogReader.hpp>
#include <_types/_uint64_t.h>

#include <sstream>
#include <string_view>
#include <chrono>
#include <iomanip>
#include <string>
#include <algorithm>
#include <set>

using ActorId = uint64_t;
using VisualisationTime = uint64_t;

class Logs {
public:
  struct RealLogLine {
    std::string_view type;
    std::string_view to;
    std::string_view from;
    std::string_view message;
    std::string_view time;
    std::optional<std::string_view> actorType;

    RealLogLine() = default;
    RealLogLine(const RealLogLine&) = default;
    ~RealLogLine() = default;
    RealLogLine& operator=(const RealLogLine&) = default;

    bool operator==(const RealLogLine&) const = default;

    RealLogLine(std::string_view type,
                std::string_view to,
                std::string_view from,
                std::string_view message,
                std::string_view time) :
      type(type), to(to), from(from), message(message), time(time) {}

    RealLogLine(std::string_view type,
                std::string_view to,
                std::string_view from,
                std::string_view message,
                std::string_view time,
                std::string_view argActorType) :
      RealLogLine(type, to, from, message, time)
      { actorType = argActorType;}
  };

  struct NewDieLogLine {
    std::string_view type;
    std::string_view id;
    std::string_view time;

    NewDieLogLine() = default;
    NewDieLogLine(const NewDieLogLine&) = default;
    ~NewDieLogLine() = default;
    NewDieLogLine& operator=(const NewDieLogLine&) = default;

    bool operator==(const NewDieLogLine&) const = default;    
  };

  struct ParsedLogLine {
    std::string_view type;
    ActorId to;
    ActorId from;
    std::string_view message;
    VisualisationTime time;
    std::optional<std::string_view> actorType;

    ParsedLogLine() = default;
    ParsedLogLine(const ParsedLogLine&) = default;
    ~ParsedLogLine() = default;
    ParsedLogLine& operator=(const ParsedLogLine&) = default;

    bool operator==(const ParsedLogLine&) const = default;

    ParsedLogLine(std::string_view type,
                  ActorId to,
                  ActorId from,
                  std::string_view message,
                  VisualisationTime time) :
    type(type), to(to), from(from), message(message), time(time) {}

    ParsedLogLine(std::string_view type,
                  ActorId to,
                  ActorId from,
                  std::string_view message,
                  VisualisationTime time,
                  std::string_view argActorType) :
    ParsedLogLine(type, to, from, message, time)
    {actorType = argActorType;}
  };

  struct LogMessage {
    ActorId to;
    ActorId from;
    VisualisationTime start;
    VisualisationTime end;
    std::string_view message;

    LogMessage() = default;
    LogMessage(const LogMessage&) = default;
    ~LogMessage() = default;
    LogMessage& operator=(const LogMessage&) = default;

    bool operator==(const LogMessage&) const = default;

    LogMessage(ActorId to, ActorId from, VisualisationTime start, VisualisationTime end, std::string_view message) :
      to(to), from(from), start(start), end(end), message(message) {}
  };

  static void ReadLogs(const std::string_view file) {
    LogReader::ReadFile(file);
    logLines_ = LogReader::GetLogLines();

    CreateRealLogLines();
    ParseRealLogLines();
    SetMessageToParsedLineInd();

    CreateLogMessages();
    NormalizeLogMessagesTime();

    CreateActorTypeToActorId();
    CreateActorIdToActorType();


    GetActorLifeInfo();
    SetActorLifeTime();
  }

  static const std::vector<RealLogLine>& GetRealLogLines() {
    return realLogLines_;
  }

  static const std::vector<ParsedLogLine>& GetParsedLogLines() {
    return parsedLogLines_;
  }

  static const std::vector<std::string_view>& GetLogLines() {
    return logLines_;
  }

  static const std::vector<LogMessage>& GetLogMessages() {
    return logMessages_;
  }

  static const std::map<std::string_view, std::vector<ActorId>>& GetActorTypeToActorId() {
    return actorTypeToActorId_;
  }

  static const std::map<ActorId, std::string_view>& GetActorIdToActorType() {
    return actorIdToActorType_;
  }

  static const std::map<std::string_view, std::vector<size_t>>& GetMessageToParsedLineInd() {
    return messageToParsedLineInd_;
  }

  static VisualisationTime GetMaxTime() {
    if (logMessages_.empty()) {
      return 0;
    }

    VisualisationTime maxTime = logMessages_.front().end;
    for (const LogMessage& logMessage : logMessages_) {
      maxTime = std::max(maxTime, logMessage.end);
    }

    return maxTime;
  }

  static ActorId GetMaxActorId() {
    return maxActorId_;
  }

  static void Clear() {
    logLines_.clear();
    realLogLines_.clear();
    parsedLogLines_.clear();

    realActorIdToActorNumId_.clear();
    actorNumIdToRealActorId_.clear();
    messageToParsedLineInd_.clear();

    logMessages_.clear();
    actorTypeToActorId_.clear();
    actorIdToActorType_.clear();
  }

  static bool IsAlife(ActorId id, VisualisationTime time) {

    if (!lifeTime_.count(id)) {
      return false;
    }

    if (lifeTime_[id].first <= time && lifeTime_[id].second >= time) {
      return true;
    }

    return false;
  }

private:

  static void SetActorLifeTime() {
    std::map<ActorId, VisualisationTime> newActors;
    std::map<ActorId, VisualisationTime> dieActors; 

    for (const NewDieLogLine& newDieLogLine : newDieLogLines_) {
      if (!realActorIdToActorNumId_.count(newDieLogLine.id)) {
        continue;
      }

      if (newDieLogLine.type == "New") {
        if (newActors.count(realActorIdToActorNumId_.at(newDieLogLine.id))) {
          throw std::runtime_error("actor created yet");
        }

        newActors[
          realActorIdToActorNumId_.at(newDieLogLine.id)] = 
          fromTimestempToTime(std::string(newDieLogLine.time)) - oldMinTime_;
      } else if (newDieLogLine.type == "Die") {
        if (dieActors.count(realActorIdToActorNumId_.at(newDieLogLine.id))) {
          throw std::runtime_error("actor die yet");
        }

        dieActors[
          realActorIdToActorNumId_.at(newDieLogLine.id)] = 
          fromTimestempToTime(std::string(newDieLogLine.time)) - oldMinTime_;
      }
    }

    VisualisationTime maxTime = GetMaxTime();

    for (ActorId id = 0; id <= maxActorId_; ++id) {
      lifeTime_[id].first = (newActors.count(id)) ? newActors[id] : 0;
      lifeTime_[id].second = (dieActors.count(id)) ? dieActors[id] : maxTime;
    }
  }

  static void GetActorLifeInfo() {
    for (std::string_view logLine : logLines_) {
      size_t charInd = 0, lastCharInd = 0;
      size_t curWordNum = 0;

      if (logLine[0] != 'N' && logLine[0] != 'D') {
        continue;
      }

      NewDieLogLine newDieLogLine;

      for (; charInd < logLine.size(); ++charInd) {
        if (logLine[charInd] == ' ') {
          switch (curWordNum) {
            case 0: {
              newDieLogLine.type = 
                std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);
              break;
            }

            case 1: {
              newDieLogLine.id = 
                std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);
              break;
            }
          }

          lastCharInd = charInd + 1;
          curWordNum++;
        }
      }

      newDieLogLine.time = 
        std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);

      newDieLogLines_.push_back(newDieLogLine);
    }
  }

  static void CreateRealLogLines() {
    for (std::string_view logLine : logLines_) {
      size_t charInd = 0, lastCharInd = 0;
      size_t curWordNum = 0;

      if (logLine[0] != 'R' && logLine[0] != 'S') {
        continue;
      }

      RealLogLine curRealLogLine;

      for (; charInd < logLine.size(); ++charInd) {
        if (logLine[charInd] == ' ') {
          switch (curWordNum) {
            case 0 : {
              curRealLogLine.type = 
                std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);
                break;
            }

            case 1 : {
              curRealLogLine.to =
                std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);
              break;
            }

            case 2 : {
              curRealLogLine.from = 
                std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);
              break;
            }

            case 3 : {
              curRealLogLine.message = 
                std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);
              break;
            }

            case 4 : {
              curRealLogLine.time = 
                std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);
              break;
            }
          }

          lastCharInd = charInd + 1;
          curWordNum++;
        }
      }

      if (curRealLogLine.type == "Receive") {
        curRealLogLine.actorType = 
          std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);
      } else {
        curRealLogLine.time = 
          std::string_view(logLine.begin() + lastCharInd, logLine.begin() + charInd);
      }

      realLogLines_.push_back(curRealLogLine);
    }
  }

  static void ParseRealLogLines() {
    realActorIdToActorNumId_["[0:0:0]"] = 0;
    actorNumIdToRealActorId_[0] = "[0:0:0]";

    ActorId curUnusedActorId = 1;

    parsedLogLines_.reserve(realLogLines_.size());

    for (const RealLogLine& realLogLine : realLogLines_) {
      ParsedLogLine curParsedLogLine;
      curParsedLogLine.type = realLogLine.type;

      if (!realActorIdToActorNumId_.count(realLogLine.to)) {
        realActorIdToActorNumId_[realLogLine.to] = curUnusedActorId;
        actorNumIdToRealActorId_[curUnusedActorId++] = realLogLine.to;
      }
      curParsedLogLine.to = realActorIdToActorNumId_[realLogLine.to];

      if (!realActorIdToActorNumId_.count(realLogLine.from)) {
        realActorIdToActorNumId_[realLogLine.from] = curUnusedActorId;
        actorNumIdToRealActorId_[curUnusedActorId++] = realLogLine.from;        
      }
      curParsedLogLine.from = realActorIdToActorNumId_[realLogLine.from];

      curParsedLogLine.message = realLogLine.message;

      curParsedLogLine.time = fromTimestempToTime(std::string(realLogLine.time));

      if (curParsedLogLine.type == "Receive") {
        curParsedLogLine.actorType = realLogLine.actorType;
      }

      parsedLogLines_.push_back(curParsedLogLine);
    }

    maxActorId_ = curUnusedActorId;
  }

  static VisualisationTime fromTimestempToTime(std::string timeStemp) {
    std::string tailWithMcS = timeStemp.substr(timeStemp.length() - 8);
    timeStemp.resize(timeStemp.length() - 8);
    tailWithMcS.pop_back();
    tailWithMcS.erase(tailWithMcS.begin());

    std::tm tm = {};
    std::stringstream tsStream(timeStemp);
    tsStream >> std::get_time(&tm, "%Y-%m-%dT%H%N%S");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    VisualisationTime cur =
        std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch())
            .count();
    cur *= 1'000'000;
    cur += std::stoi(tailWithMcS);

    return cur;
  }

  static void SetMessageToParsedLineInd() {
    for (size_t lineInd = 0; lineInd < parsedLogLines_.size(); ++lineInd) {
      messageToParsedLineInd_[parsedLogLines_[lineInd].message].push_back(lineInd);
    }

    for (auto it = messageToParsedLineInd_.begin(); it != messageToParsedLineInd_.end(); ++it) {
      std::sort(it->second.begin(), it->second.end(),
        [](size_t lhs, size_t rhs) {
          return parsedLogLines_[lhs].time < parsedLogLines_[rhs].time;
        }
      );
    }
  }

  static void CreateLogMessages() {
    for (auto it = messageToParsedLineInd_.begin(); it != messageToParsedLineInd_.end(); ++it) {
      for (size_t i = 0; i < it->second.size(); ++i) {
        size_t parsedInd = it->second[i];
        const ParsedLogLine& parsedLogLineSend = parsedLogLines_[parsedInd];
        if (parsedLogLineSend.type != "Send") {
          continue;
        }

        LogMessage cur;
        cur.message = it->first;
        cur.from = parsedLogLineSend.from;
        cur.to = parsedLogLineSend.to;
        cur.start = parsedLogLineSend.time;

        bool found = false;
        for (size_t j = i + 1; j < it->second.size(); ++j) {
          const ParsedLogLine& parsedLogLineReceive = parsedLogLines_[it->second[j]];
          if (parsedLogLineReceive.type != "Receive") {
            continue;
          }

          if (parsedLogLineReceive.from != cur.from ||
              parsedLogLineReceive.to != cur.to) {
            continue;
          }

          cur.end = parsedLogLineReceive.time;
          found = true;
          break;
        }

        if (found) {
          logMessages_.push_back(cur);
        }
      }
    }
  }

  static void NormalizeLogMessagesTime() {
    if (logMessages_.size() == 0) {
      return;
    }

    VisualisationTime minTime = logMessages_.front().start;
    for (LogMessage& message : logMessages_) {
      minTime = std::min(minTime, message.start);
    }

    oldMinTime_ = minTime;

    for (LogMessage& message: logMessages_) {
      message.start -= minTime;
      message.end -= minTime;
    }
  }

  static void CreateActorTypeToActorId() {
    std::set<ActorId> added;

    added.insert(0);
    actorTypeToActorId_["UNIVERSE"] = {0};

    for (const ParsedLogLine& parsedLogLine: parsedLogLines_) {
      if (!parsedLogLine.actorType) {
        continue;
      }

      if (!added.count(parsedLogLine.to)) {
        actorTypeToActorId_[*parsedLogLine.actorType].push_back(parsedLogLine.to);
        added.insert(parsedLogLine.to);
      }
    }
  }

  static void CreateActorIdToActorType() {
    actorIdToActorType_[0] = "UNIVERSE";

    for (const ParsedLogLine& parsedLogLine: parsedLogLines_) {
      if (!parsedLogLine.actorType) {
        continue;
      }

      actorIdToActorType_[parsedLogLine.to] = *parsedLogLine.actorType;
    }
  }

  static std::vector<std::string_view> logLines_;
  static std::vector<RealLogLine> realLogLines_;
  static std::vector<ParsedLogLine> parsedLogLines_;

  static std::map<ActorId, std::string_view> actorNumIdToRealActorId_;
  static std::map<std::string_view, ActorId> realActorIdToActorNumId_;

  static std::map<std::string_view, std::vector<size_t>> messageToParsedLineInd_;

  static std::vector<LogMessage> logMessages_;

  static std::map<std::string_view, std::vector<ActorId>> actorTypeToActorId_;
  static std::map<ActorId, std::string_view> actorIdToActorType_;

  static std::vector<NewDieLogLine> newDieLogLines_;
  static std::map<ActorId, std::pair<VisualisationTime, VisualisationTime>> lifeTime_;

  static ActorId maxActorId_;


  static VisualisationTime oldMinTime_;
};

std::ostream& operator<<(std::ostream& os, const Logs::LogMessage& lm);