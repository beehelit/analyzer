#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <DrawElements/lines/TransportLine.hpp>
#include <_types/_uint64_t.h>

class Message : public IDrawElement {
public:
  Message(TransportLine *line, double progress)
      : line_(line), progress_(progress) {}

  void Draw(const Drawer *drawer) const override;

  DrawElementType GetDrawElementType() const override {
    return DrawElementType::MESSAGE;
  }

private:
  double progress_;
  TransportLine *line_;
};
