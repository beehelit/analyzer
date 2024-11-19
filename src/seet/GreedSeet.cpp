#include "GreedSeet.hpp"
#include "analizer/src/Logs/Event/Event.hpp"
#include "arctic/engine/vec2si32.h"
#include <algorithm>
#include <iostream>

GreedSeet::GreedSeet(Window *window, const LogsReader &logsReader)
    : window_(window) {

  tables_.resize(1);

  auto name_id = logsReader.GetNameActorId();
  auto id_name = logsReader.GetActorIdName();
  auto info = logsReader.GetSeetInfo();

  std::map<ActorId, size_t> actorIdSeetLevel;

  for (auto it : info) {
    if (it.second >= tables_.size()) {
      tables_.resize(it.second + 1);
    }

    if (name_id.count(it.first)) {
      for (auto id : name_id[it.first]) {
        tables_[it.second].push_back(id);
      }
    }
  }

  for (auto it : id_name) {
    if (!info.count(it.second)) {
      tables_[0].push_back(it.first);
    }
  }

  ActorId maxActorId = 0;

  for (int i = 0; i < tables_.size(); ++i) {
    for (int j = 0; j < tables_[i].size(); ++j) {
      maxActorId = std::max(maxActorId, tables_[i][j]);
    }
  }

  coords_.resize(maxActorId + 1);

  for (int i = 0; i < tables_.size(); ++i) {
    for (int j = 0; j < tables_[i].size(); ++j) {
      coords_[tables_[i][j]] =
          arctic::Vec2Si32((j % 100) * 10, i * 500 + (j / 100) * 10);
    }
  }
}

arctic::Vec2Si32 GreedSeet::GetCoord(arctic::Ui32 number) {
  return coords_[number];
}
