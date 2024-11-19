#pragma once

#include "LogsReader/LogsReader.hpp"
#include <Logs/Event/Event.hpp>
#include <_types/_uint64_t.h>

class Logs {
public:
  Logs(LogsReader &logsReader) { events_ = logsReader.MoveEvents(); }

  const std::vector<Event> &GetEvents() const { return events_; }

  size_t GetActorsCount() const;
  ActorId GetMaxActorNum() const;
  Time GetMaxTime() const;

  void Normalize();

  ~Logs() = default;

private:
  Logs() = delete;
  Logs(const Logs &) = delete;

  std::vector<Event> events_;
};