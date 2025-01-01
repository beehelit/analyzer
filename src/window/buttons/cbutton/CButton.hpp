#pragma once

#include "analizer/src/window/MWindow/MWindow.hpp"
#include "analizer/src/window/buttons/Button.hpp"
#include <functional>

class CButton : public VisualizatorButton {
public:
  CButton( Sprite sprite, std::function<void()> action)
      : Window(sprite), VisualizatorButton(sprite, action) {}

  CButton( Sprite sprite, Mouse* mouse, std::function<void()> action)
      : Window(sprite), VisualizatorButton(sprite, mouse, action) {}

  CButton() = default;

  void Listen() override;
};
