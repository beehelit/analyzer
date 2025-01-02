#include "Drawer.hpp"
#include "analizer/src/DrawElements/IDrawElement.hpp"
#include <stdexcept>

void Drawer::Draw() const {
  for (Actor* actor : actorStorage_) {
    actor->Draw(this);
  }

  for (IDrawElement* drawElement : drawStorage_) {
    if (!drawElement) {
      throw std::runtime_error("Null pointer, Draw: drawElement");
    }

    drawElement->Draw(this);
  }

  const Window* curWindow = GetWindow();
  for (Window* window : curWindow->GetSubWindows()) {
    Drawer* drawer = dynamic_cast<Drawer *>(window);
    drawer->Draw();
  }
}

void Drawer::AddDrawElement(IDrawElement *drawElement) {
  if (!drawElement) {
    throw std::runtime_error("Null pointer, Add: drawElement");
  }

  if (drawElement->GetDrawElementType() == DrawElementType::MESSAGE) {
    messageExtendedStorage_.push_back(dynamic_cast<Message*>(drawElement));
  }

  if (drawElement->GetDrawElementType() == DrawElementType::ACTOR) {
    actorStorage_.push_back(dynamic_cast<Actor *>(drawElement));
    actorIdToStorageInd_[dynamic_cast<Actor *>(drawElement)->GetId()] = actorStorage_.size() - 1;
    return;
  }

  drawStorage_.push_back(drawElement);
}

/*
Drawer::~Drawer() {
  for (IDrawElement* drawElement : drawStorage_) {
    if (drawElement) {
      delete drawElement;
    }
  }
}
*/