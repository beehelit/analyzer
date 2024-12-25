#include "ActorTable.hpp"
#include "arctic/engine/vec2si32.h"

void ActorTable::AddActor(ActorId id) {
    arctic::Vec2Si32 curBlockSize = gFont_.EvaluateSize(
        std::string(Logs::GetActorIdToActorType().at(id)).c_str(),
        false
    );

    blocksSize_.push_back(curBlockSize);
    idToPositionInd_[id] = positions_.size();

    if (positions_.empty()) { 
        positions_.push_back(curBlockSize);

        return;
    }

    if (positions_.back().x + kXDelta + curBlockSize.x > lineLength_) {
        positions_.push_back(
            curBlockSize + arctic::Vec2Si32(0, positions_.back().y + kYDelta)
        );
    } else {
        positions_.push_back(
            arctic::Vec2Si32(positions_.back().x + kXDelta + curBlockSize.x, positions_.back().y)
        );
    }
}