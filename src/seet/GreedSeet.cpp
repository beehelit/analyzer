#include "GreedSeet.hpp"

#include "arctic/engine/vec2si32.h"
#include <_types/_uint64_t.h>
#include <algorithm>
#include <fstream>
#include <set>

void GreedSeet::ReadConfig(std::string fileName) {
  std::ifstream seetIn(fileName);

  std::string actorName;
  size_t actorSeet;
  while (seetIn >> actorName) {
    seetIn >> actorSeet;

    actorNameSeet_[actorName] = actorSeet;
  }

}

GreedSeet::GreedSeet(std::pair<uint64_t, uint64_t> windowSize, uint64_t actorRadius) {

  tables_.resize(1);

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

  size_t windowWidth = windowSize.first;
  size_t windowHeight = windowSize.second;

  size_t actorPerLine = windowWidth / (actorRadius * 10);
  
  coords_.resize(Logs::GetMaxActorId() + 1);

  std::vector<size_t> tablesHeight(tables_.size());
  for (size_t tableNum = 0; tableNum < tables_.size(); ++tableNum) {
    tablesHeight[tableNum] = (tables_[tableNum].size() / actorPerLine + 
                             (tables_[tableNum].size() % actorPerLine > 0)) * 5*actorRadius;
  }

  size_t curHeightAdd = 15*actorRadius;
  for (size_t i = 0; i < tables_.size(); ++i) {
    for (size_t j = 0; j < tables_[i].size(); ++j) {

      coords_[tables_[i][j]] =
          arctic::Vec2Si32(
            (j % actorPerLine) * 10*actorRadius, 
            j / actorPerLine * 5*actorRadius + curHeightAdd
          );

      coordActorId_[std::pair(coords_[tables_[i][j]].x, coords_[tables_[i][j]].y)] = tables_[i][j];

      coordedId_.insert(tables_[i][j]);
    }

    curHeightAdd += tablesHeight[i] + 20*actorRadius;
  }

}

arctic::Vec2Si32 GreedSeet::GetCoord(ActorId id) {
  return coords_[id];
}

ActorId GreedSeet::GetId(arctic::Vec2Si32 coord) {
  return coordActorId_[{coord.x, coord.y}];
}