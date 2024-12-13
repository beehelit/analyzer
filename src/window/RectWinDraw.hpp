#pragma once

#include <camera/Camera.hpp>
#include <window/Drawer/Drawer.hpp>

#include "RectangleWindow/RectangleWindow.hpp"
#include <window/MWindow/MWindow.hpp>

#include "engine/vec2si32.h"
#include "log/log_reader/LogReader.hpp"
#include <memory>

class GreedSeet;

class RectWinDraw : public RectangleWindow, public Drawer {
public:
  RectWinDraw(arctic::Sprite sprite, Camera *camera, Mouse *mouse)
      : RectWinDraw(sprite, camera) {
    SetMouse(mouse);
    gFont_.Load("data/arctic_one_bmf.fnt");
  }

  RectWinDraw(arctic::Sprite sprite, Camera *camera) : RectWinDraw(sprite) {
    SetCamera(camera);
    gFont_.Load("data/arctic_one_bmf.fnt");
  }

  RectWinDraw(arctic::Sprite sprite)
      : Window(sprite), Drawer(), RectangleWindow(sprite) {
    gFont_.Load("data/arctic_one_bmf.fnt");
  }

  RectWinDraw() {
    gFont_.Load("data/arctic_one_bmf.fnt");
  }

  arctic::Sprite GetDrawSprite() const override;

  void SetDrawSprite(arctic::Sprite sprite) override;

  void Listen() override;

  const Window *GetWindow() const override;

  void SetGreedSeet(GreedSeet* gs) {
    gs_ = gs;
  }

  GreedSeet* GetGreedSeet() {
    return *gs_;
  }

  void Draw() const override;

  void SetBackgroundColor(arctic::Rgba color);

private:
  std::optional<GreedSeet*> gs_;
  mutable arctic::Font gFont_;

  arctic::Rgba backgroundColor_;
};
