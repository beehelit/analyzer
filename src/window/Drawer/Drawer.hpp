#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <DrawElements/actors/Actor.hpp>
#include <_types/_uint64_t.h>
#include <camera/Camera.hpp>
#include <window/Window.hpp>
#include <map>

#include "engine/easy_sprite.h"

#include <memory>

class Drawer {
public:
  virtual void Draw() const;
  void AddDrawElement(IDrawElement *drawElement);

  virtual arctic::Sprite GetDrawSprite() const = 0;
  virtual void SetDrawSprite(arctic::Sprite sprite) = 0;

  virtual const Window* GetWindow() const = 0;

  void SetCamera(Camera *camera) { camera_ = camera; }

  Camera *GetCamera() const {
    if (camera_ == std::nullopt) {
      return nullptr;
    }

    return *camera_;
  }

  const std::vector<Actor*>& GetActorStorage() const { return actorStorage_; }

  const std::map<uint64_t, size_t>& GetActorIdToStorageInd() const { return actorIdToStorageInd_; }

  ~Drawer() = default;
  Drawer() = default;

private:
  Drawer(const Drawer &) = delete;

  std::vector<IDrawElement *> drawStorage_;
  std::optional<Camera *> camera_;

  std::vector<Actor *> actorStorage_;
  std::map<uint64_t, size_t> actorIdToStorageInd_;
};
