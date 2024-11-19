#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <DrawElements/actors/Actor.hpp>
#include <camera/Camera.hpp>
#include <window/Window.hpp>

#include "engine/easy_sprite.h"

#include <memory>

class Drawer {
public:
  virtual void Draw() const;
  void AddDrawElement(IDrawElement *drawElement);

  virtual arctic::Sprite GetDrawSprite() const = 0;
  virtual const Window *GetWindow() const = 0;

  void SetCamera(Camera *camera) { camera_ = camera; }

  Camera *GetCamera() const {
    if (camera_ == std::nullopt) {
      return nullptr;
    }

    return *camera_;
  }

  const auto &GetActorStorage() const { return actorStorage_; }

  virtual ~Drawer();
  Drawer() = default;

private:
  Drawer(const Drawer &) = delete;

  std::vector<IDrawElement *> drawStorage_;
  std::optional<Camera *> camera_;

  std::vector<Actor *> actorStorage_;
};
