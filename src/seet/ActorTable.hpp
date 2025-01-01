#pragma once

#include "arctic/engine/vec2si32.h"
#include "engine/arctic_types.h"
#include "engine/font.h"
#include <vector>
#include <log/Logs.hpp>
#include <map>

using namespace arctic;

class ActorTable {
public:
    const  Si32 kXDelta = 30;
    const  Si32 kYDelta = 35;

    ActorTable( Font& font) :
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
    void SetLineLength( Si32 lineLength) { lineLength_ = lineLength; }

    void SetYAdd( Si32 yAdd) { yAdd_ = yAdd; }
     Si32 GetYAdd() const { return yAdd_; }

    void SetXAdd( Si32 xAdd) { xAdd_ = xAdd; }
     Si32 GetXAdd() const { return xAdd_; }

     Si32 GetY() const { return positions_.back().y + yAdd_; }
     Si32 GetLineLength() const { return lineLength_; }

     Vec2Si32 GetLeftDownCornerPosition(ActorId id) const {
        size_t positionIndex = idToPositionInd_.at(id);

        return positions_[positionIndex] - blocksSize_[positionIndex] + 
                Vec2Si32(xAdd_, yAdd_);
    }


    using RightUpKornerPositon =  Vec2Si32;
    using BlockSize =  Vec2Si32;
private:
    std::map<ActorId, size_t> idToPositionInd_;

    std::vector<BlockSize> blocksSize_;
    std::vector<RightUpKornerPositon> positions_;

     Si32 lineLength_ = 1920;

     Font& gFont_;

     Si32 yAdd_ = 0;
     Si32 xAdd_ = 0;
};