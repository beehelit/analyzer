#pragma once

#include "arctic/engine/arctic_types.h"
#include "arctic/engine/vec2si32.h"
#include <log/Logs.hpp>
#include <log/log_reader/LogReader.hpp>
#include <vector>
#include <window/RectWinDraw.hpp>
#include <config.hpp>
#include <set>

#include "ActorTable.hpp"

using namespace arctic;

class GreedSeet {
public:
  GreedSeet(std::pair<uint64_t, uint64_t> windowSize, uint64_t actorRadius);
   Vec2Si32 GetCoord(ActorId id);
  ActorId GetId( Vec2Si32 coord);

  bool HaveCoord(ActorId id) const {
    return coordedId_.count(id);
  }
  void ReadConfig(std::string fileName);
  void PrepareTables();

  const std::vector<ActorTable>& GetActorTables() const {
    return actorTables_;
  }

private:
  std::vector<ActorTable> actorTables_;
  std::vector<std::vector<ActorId>> tables_;
  std::vector< Vec2Si32> coords_;
  std::map<std::pair< Si32,  Si32>, ActorId> coordActorId_;

  std::map<std::string, size_t> actorNameSeet_;
  std::set<ActorId> coordedId_;

   Vec2Si32 windowSize_;
  uint64_t actorRadius_;

   Font gFont_;
};
