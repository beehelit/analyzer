#pragma once

#include "arctic/engine/vec2si32.h"
#include "engine/arctic_types.h"
#include "engine/font.h"
#include <vector>
#include <log/Logs.hpp>
#include <map>

class ActorTable {
public:
    const arctic::Si32 kXDelta = 4;
    const arctic::Si32 kYDelta = 2;

    ActorTable(arctic::Font& font) :
        gFont_(font) {}


    ActorTable(const ActorTable&) = delete;
    ~ActorTable() = default;
    ActorTable& operator=(const ActorTable&) = delete;
    ActorTable(const ActorTable&& actorTable) :
        gFont_(actorTable.gFont_) {
        idToPositionInd_ = std::move(actorTable.idToPositionInd_);
        blocksSize_ = std::move(actorTable.blocksSize_);
        positions_ = std::move(actorTable.positions_);
        lineLength_ = actorTable.lineLength_;
        yAdd_ = actorTable.yAdd_;
    }

    void AddActor(ActorId id);
    void SetLineLength(arctic::Si32 lineLength) { lineLength_ = lineLength; }
    void SetYAdd(arctic::Si32 yAdd) { yAdd_ = yAdd; }
    arctic::Si32 GetY() const { return positions_.back().y; }

    arctic::Vec2Si32 GetLeftDownCornerPosition(ActorId id) const {
        size_t positionIndex = idToPositionInd_.at(id);

        return positions_[positionIndex] - blocksSize_[positionIndex] + 
               arctic::Vec2Si32(0, yAdd_);
    }


    using RightUpKornerPositon = arctic::Vec2Si32;
    using BlockSize = arctic::Vec2Si32;
private:
    std::map<ActorId, size_t> idToPositionInd_;

    std::vector<BlockSize> blocksSize_;
    std::vector<RightUpKornerPositon> positions_;

    arctic::Si32 lineLength_ = 1920;

    arctic::Font& gFont_;

    arctic::Si32 yAdd_ = 0;
};