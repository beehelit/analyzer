#pragma once

#include <camera/Camera.hpp>
#include <window/Drawer/Drawer.hpp>

#include "RectangleWindow/RectangleWindow.hpp"
#include <window/MWindow/MWindow.hpp>

#include "engine/vec2si32.h"
#include "log/log_reader/LogReader.hpp"
#include <memory>

using namespace arctic;

class GreedSeet;

class RectWinDraw : public RectangleWindow, public Drawer {
public:
  RectWinDraw( Sprite sprite, Camera *camera, Mouse *mouse)
      : RectWinDraw(sprite, camera) {
    SetMouse(mouse);
    gFont_.Load("data/arctic_one_bmf.fnt");
  }

  RectWinDraw( Sprite sprite, Camera *camera) : RectWinDraw(sprite) {
    SetCamera(camera);
    gFont_.Load("data/arctic_one_bmf.fnt");
  }

  RectWinDraw( Sprite sprite)
      : Window(sprite), Drawer(), RectangleWindow(sprite) {
    gFont_.Load("data/arctic_one_bmf.fnt");
  }

  RectWinDraw() {
    gFont_.Load("data/arctic_one_bmf.fnt");
  }

   Sprite GetDrawSprite() const override;

  void SetDrawSprite( Sprite sprite) override;

  void Listen() override;

  const Window *GetWindow() const override;

  void SetGreedSeet(GreedSeet* gs) {
    gs_ = gs;
  }

  GreedSeet* GetGreedSeet() {
    return *gs_;
  }

  void Draw() const override;

  void SetBackgroundColor( Rgba color);

private:
  std::optional<GreedSeet*> gs_;
  mutable  Font gFont_;

   Rgba backgroundColor_=Rgba(0, 0, 0);
};
