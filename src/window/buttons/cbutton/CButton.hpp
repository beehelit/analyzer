#pragma once

#include "analizer/src/window/MWindow/MWindow.hpp"
#include "analizer/src/window/buttons/Button.hpp"
#include <functional>

class CButton : public Button {
public:
  CButton(arctic::Sprite sprite, std::function<void()> action)
      : Window(sprite), Button(sprite, action) {}

  CButton(arctic::Sprite sprite, Mouse *mouse, std::function<void()> action)
      : Window(sprite), Button(sprite, mouse, action) {}

  CButton() = default;

  void Listen() override;
};