#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <window/RectangleWindow/RectangleWindow.hpp>
#include <window/buttons/cbutton/CButton.hpp>

using VisualisationTime = uint64_t;

class TimeLine : public RectangleWindow, public CButton, public IDrawElement {
public:
  TimeLine() {
    time_ = 0;
    maxTime_ = 0;
    status_ = false;
    speed_ = 1;
  }

  void SetMaxTime(VisualisationTime maxTime) { maxTime_ = maxTime; }

  void Draw(const Drawer* drawer) const override;
  void Action() override;
  void Listen() override {
    CButton::Listen();

    if (status_ && time_ < maxTime_) {
      if (speed_ < 0 && time_ < -speed_) {
        time_ = 0;
      } else {
        time_ += speed_;
      }
      time_ = std::min(time_, maxTime_);
    }
  }

  void SetStatus(bool status) { status_ = status; }

  bool GetStatus() const { return status_; }

  VisualisationTime GetTime() const { return time_; }

  DrawElementType GetDrawElementType() const override {
    return DrawElementType::TIME_LINE;
  }

  int GetSpeed() const { return speed_; }
  void SetSpeed(int speed) { speed_ = speed; }

private:
  VisualisationTime time_;
  VisualisationTime maxTime_;

  bool status_;

  int speed_;
};
