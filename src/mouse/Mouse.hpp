#pragma once

#include <window/IListener.hpp>

#include "engine/easy_input.h"
#include "engine/vec2si32.h"

#include <optional>

class Mouse : public IListener {
public:
    auto GetOffset() {
        return offset_;
    }

    bool IsLeftDown() const {
        return leftMouse_;
    }

    bool IsLeftDownward() const {
        return leftMouseDownward_;
    }

    void Listen() override;


    void SafeOffset() {
        safeOffset_ = offset_;
    }

    auto GetSafeOffset() {
        return safeOffset_;
    }

    bool GetFlag() {
        return leftMouseFlag_;
    }

    void SetFlag(bool toSet) {
        leftMouseFlag_ = toSet;
    }

private:
    bool leftMouse_ = false;

    arctic::Vec2Si32 offset_ = {};
    arctic::Vec2Si32 safeOffset_ = {};

    bool leftMouseFlag_ = false;

    bool leftMouseDownward_ = false;
};