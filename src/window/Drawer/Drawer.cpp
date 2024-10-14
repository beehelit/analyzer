#include "Drawer.hpp"
#include "analizer/src/DrawElements/IDrawElement.hpp"
#include <stdexcept>

void Drawer::Draw() {
    for (auto* drawElement : drawStorage_) {
        if (!drawElement) {
            throw std::runtime_error("Null pointer, Draw: drawElement");
        }

        drawElement->Draw(this);
    }
}

void Drawer::AddDrawElement(IDrawElement* drawElement) {
    if (!drawElement) {
        throw std::runtime_error("Null pointer, Add: drawElement");
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