#pragma once

#include <chrono>

class FpsCounter {
public:
  static void Start() { time_ = std::chrono::steady_clock::now(); }

  static long long GetFps() {
    auto oldTime = time_;
    time_ = std::chrono::steady_clock::now();
    auto delta =
        std::chrono::duration_cast<std::chrono::milliseconds>(time_ - oldTime);

    uint64_t uintDelta = delta.count();
    if (uintDelta == 0) {
      uintDelta++;
    }

    return 1000 / delta.count();
  }

private:
  FpsCounter();

  static std::chrono::time_point<std::chrono::steady_clock,
                                 std::chrono::nanoseconds>
      time_;
};
