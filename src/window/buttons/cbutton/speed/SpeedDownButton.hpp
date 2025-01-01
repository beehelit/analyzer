#pragma once

#include <DrawElements/IDrawElement.hpp>
#include <window/Drawer/Drawer.hpp>
#include <window/buttons/cbutton/CButton.hpp>

class SpeedDownButton : public IDrawElement, public CButton {
public:
  SpeedDownButton( Sprite sprite, Mouse *mouse,
                std::function<void()> action)
      : Window(sprite), CButton(sprite, mouse, action) {}

  SpeedDownButton() {}

  void Action() override;

  bool IsMouseIn() const override;

  void Listen() override;

  void SetSprite( Sprite sprite) override;

  void Draw(const Drawer *drawer) const override;
  DrawElementType GetDrawElementType() const override {
    return DrawElementType::SPEED_DOWN_BUTTON;
  } 

private:
  void DrawPicture();

  std::vector<std::vector<bool>> usePix_;
};
