#pragma once

#include <window/Window.hpp>

#include "Drawer.hpp"
#include "engine/arctic_types.h"

template<class T>
class DrawBox : public Drawer, public Window {
public:
    DrawBox(T* element) :
        Window(element->GetFrameSprite()),
        element_(element) {} 

    void Draw() const override {
        Drawer::Draw();

        element_->Draw(this);
    }
/*
    ~DrawBox() override {
        delete element_;
    }
*/
    arctic::Sprite GetDrawSprite() const override {
        return element_->GetFrameSprite();
    }

    const Window* GetWindow() const override {
        return element_;
    }

    const T* GetElement() const {
        return element_;
    }

private:
    DrawBox() = delete;

    T* element_;
};