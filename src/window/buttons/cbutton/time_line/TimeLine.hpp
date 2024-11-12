#pragma once

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"
#include "analizer/src/window/buttons/cbutton/CButton.hpp"

using Time = uint64_t;

class TimeLine : 
    public RectangleWindow,
    public CButton,
    public IDrawElement {
public:
    TimeLine() {
        time_ = 0;
        maxTime_ = 0;
        status_ = false;
        speed_ = 1;
    }

    void SetMaxTime(Time maxTime) {
        maxTime_ = maxTime;
    }

    void Draw(const Drawer* drawer) const override;
    void Action() override;
    void Listen() override {
        CButton::Listen();

        if (status_ && time_ < maxTime_) {
            time_ += speed_;
            time_ = std::min(time_, maxTime_);
        }
    }

    void SetStatus(bool status) {
        status_ = status;
    }

    bool GetStatus() const {
        return status_;
    }

    Time GetTime() const {
        return time_;
    }

    DrawElementType GetDrawElementType() const override {
        return DrawElementType::TIME_LINE;
    }

    auto GetSpeed() const { return speed_; }
    void SetSpeed(int speed) { speed_ = speed; }

private:
    Time time_;
    Time maxTime_;

    bool status_;

    int speed_;
};