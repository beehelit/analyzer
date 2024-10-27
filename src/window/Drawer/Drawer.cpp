#include "Drawer.hpp"
#include "analizer/src/DrawElements/IDrawElement.hpp"
#include <stdexcept>

void Drawer::Draw() {
    for (auto* actor : actorStorage_) {
        actor->Draw(this);
    }

    for (auto* drawElement : drawStorage_) {
        if (!drawElement) {
            throw std::runtime_error("Null pointer, Draw: drawElement");
        }

        drawElement->Draw(this);
    }

    auto curWindow = GetWindow();
    for (auto window : curWindow->GetSubWindows()) {
        auto drawer = dynamic_cast<Drawer*>(window);
        drawer->Draw();
    }
}

void Drawer::AddDrawElement(IDrawElement* drawElement) {
    if (!drawElement) {
        throw std::runtime_error("Null pointer, Add: drawElement");
    }

    if (drawElement->GetDrawElementType() == DrawElementType::ACTOR) {
        actorStorage_.push_back(dynamic_cast<Actor*>(drawElement));
        return;
    }

    drawStorage_.push_back(drawElement);
}

Drawer::~Drawer() {
    for (auto* drawElement: drawStorage_) {
        if (drawElement) {
            delete drawElement;
        }
    }
}