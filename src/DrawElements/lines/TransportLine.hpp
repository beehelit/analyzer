#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <DrawElements/actors/Actor.hpp>

#include "engine/arctic_types.h"
#include "engine/easy_drawing.h"
#include "engine/vec2f.h"
#include "engine/vec2si32.h"

using namespace arctic;

class TransportLine : public IDrawElement {
public:
  void Draw(const Drawer *drawer) const override;

  virtual Vec2Si32 GetTransportLinePoint(const Drawer* drawer, double part) const;

  DrawElementType GetDrawElementType() const override {
    return DrawElementType::TRANSPORT_LINE;
  }

  TransportLine( Si32 from,  Si32 to) : fromTo_(from, to) {}

  std::pair< Si32,  Si32> GetFromTo() const { return fromTo_; }

protected:
  std::pair< Si32,  Si32> fromTo_;
};
