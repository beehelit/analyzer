#include "Logs.hpp"
#include "analizer/src/Logs/Event/Event.hpp"

#include <map>
#include <set>

size_t Logs::GetActorsCount() const {
  std::set<ActorId> actorsIds;
  for (const Event& event : events_) {
    actorsIds.insert(event.from);
    actorsIds.insert(event.to);
  }

  return actorsIds.size();
}

ActorId Logs::GetMaxActorNum() const {
  ActorId curMax = 0;
  for (const Event& event : events_) {
    curMax = std::max(curMax, event.from);
    curMax = std::max(curMax, event.to);
  }

  return curMax;
}

Time Logs::GetMaxTime() const {
  Time ret = events_[0].end;

  for (Event event : events_) {
    ret = std::max(event.end, ret);
  }

  return ret;
}

void Logs::Normalize() {
  Time minTime = events_[0].start;
  for (Event event : events_) {
    minTime = std::min(minTime, event.start);
  }

  for (Event& event : events_) {
    event.start -= minTime;
    event.end -= minTime;
  }
}
