#include "GreedSeet.hpp"

#include "DrawElements/actors/Actor.hpp"
#include "arctic/engine/vec2si32.h"
#include <algorithm>
#include <fstream>
#include <set>

#include "ActorTable.hpp"

using namespace arctic;

void GreedSeet::ReadConfig(std::string fileName) {
  std::ifstream seetIn(fileName);

  std::string actorName;
  size_t actorSeet;
  while (seetIn >> actorName) {
    seetIn >> actorSeet;

    actorNameSeet_[actorName] = actorSeet;
  }
}

void GreedSeet::PrepareTables() {
  tables_.resize(1);
  gFont_.Load("data/arctic_one_bmf.fnt");

  ReadConfig("data/seet.config");

  const std::map<std::string_view, std::vector<ActorId>>& name_id = Logs::GetActorTypeToActorId();
  const std::map<ActorId, std::string_view>& id_name = Logs::GetActorIdToActorType();
  const std::map<std::string, size_t>& info = actorNameSeet_;

  for (std::pair<std::string, size_t> it : info) {
    if (it.second >= tables_.size()) {
      tables_.resize(it.second + 1);
    }

    if (name_id.count(it.first)) {
      for (ActorId id : name_id.at(it.first)) {
        tables_[it.second].push_back(id);
      }
    }
  }

  for (std::pair<ActorId, std::string_view> it : id_name) {
    if (!info.count(std::string(it.second))) {
      tables_[0].push_back(it.first);
    }
  }

  // std::vector<ActorTable> actorTables;
  for (size_t i = 0; i < tables_.size(); ++i) {
    actorTables_.emplace_back(gFont_);
    actorTables_[i].SetLineLength(windowSize_.x);
  }

  for (size_t tableNum = 0; tableNum < tables_.size(); ++tableNum) {
    for (const ActorId& actorId : tables_[tableNum]) {
      actorTables_[tableNum].AddActor(actorId);
    }
  }

  for (size_t tableNum = 2; tableNum < tables_.size(); ++tableNum) {
    actorTables_[tableNum].SetYAdd(actorTables_[tableNum-1].GetY() + 5);
  }
  actorTables_[0].SetYAdd(actorTables_[actorTables_.size() - 1].GetY() + 5);
  
  coords_.resize(Logs::GetMaxActorId() + 1);


  for (size_t i = 0; i < tables_.size(); ++i) {
    for (size_t j = 0; j < tables_[i].size(); ++j) {
      coords_[tables_[i][j]] = actorTables_[i].GetLeftDownCornerPosition(tables_[i][j]);
      coordActorId_[std::pair(coords_[tables_[i][j]].x, coords_[tables_[i][j]].y)] = tables_[i][j];

      coordedId_.insert(tables_[i][j]);
    }
  }
}

GreedSeet::GreedSeet(std::pair<uint64_t, uint64_t> windowSize, uint64_t actorRadius) {
  windowSize_.x = windowSize.first;
  windowSize_.y = windowSize.second;
  actorRadius_ = actorRadius;
}

 Vec2Si32 GreedSeet::GetCoord(ActorId id) {
  return coords_[id];
}

ActorId GreedSeet::GetId( Vec2Si32 coord) {
  return coordActorId_[{coord.x, coord.y}];
}