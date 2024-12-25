#include "ActorTable.hpp"
#include "arctic/engine/vec2si32.h"

using namespace arctic;

void ActorTable::AddActor(ActorId id) {
     Vec2Si32 curBlockSize = gFont_.EvaluateSize(
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
            curBlockSize +  Vec2Si32(0, positions_.back().y + kYDelta)
        );
    } else {
        positions_.push_back(
             Vec2Si32(positions_.back().x + kXDelta + curBlockSize.x, positions_.back().y)
        );
    }
}