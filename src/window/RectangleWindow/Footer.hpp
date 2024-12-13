#pragma once

#include <window/Drawer/DrawBox.hpp>
#include <window/Drawer/Drawer.hpp>
#include <window/IListener.hpp>
#include <window/RectangleWindow/RectangleWindow.hpp>

#include "engine/easy_sprite.h"

class Footer : public Drawer, public RectangleWindow {
public:
  Footer(arctic::Sprite sprite) : Window(sprite), RectangleWindow(sprite) {}

  Footer() = default;

  void Listen() override {
    RectangleWindow::Listen();

    for (Window* window : GetSubWindows()) {
      const Window* elem = dynamic_cast<Drawer *>(window)->GetWindow();
      Window* nonConst = const_cast<Window *>(elem);
      dynamic_cast<IListener *>(nonConst)->Listen();
    }
  }

  const Window *GetWindow() const override { return this; }

  arctic::Sprite GetDrawSprite() const override { return GetFrameSprite(); }

  void SetDrawSprite(arctic::Sprite sprite) override {
    SetSprite(sprite);
  }
};
