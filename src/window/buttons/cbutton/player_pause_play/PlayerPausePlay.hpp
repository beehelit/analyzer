#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <window/Drawer/Drawer.hpp>
#include <window/buttons/cbutton/CButton.hpp>

#include "engine/vec2si32.h"

#include <functional>
#include <vector>

class PlayerPausePlay : public IDrawElement, public CButton {
public:
    PlayerPausePlay(arctic::Sprite sprite, Mouse* mouse, std::function<void()> action) :
        Window(sprite),
        CButton(sprite, mouse, action) {
        isActive_ = false;
    }

    PlayerPausePlay() {
        isActive_ = false;
    }

    void Action() override;

    bool IsMouseIn() const override;

    void Listen() override;

    void SetSprite(arctic::Sprite sprite) override;

    void Draw(const Drawer* drawer) const override;
    DrawElementType GetDrawElementType() const override {
        return DrawElementType::PLAYER_PAUSE_PLAY_BUTTON;
    }

private:
    void DrawPicture();

    bool isActive_;
    std::vector<std::vector<bool>> usePix_;
};
