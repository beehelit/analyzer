// Copyright (c) <year> Your name

#include "analizer/src/DrawElements/lines/TransportLine.hpp"
#include "engine/arctic_input.h"
#include "engine/easy.h"
#include "engine/easy_input.h"
#include "engine/easy_util.h"
#include "engine/vec2d.h"
#include "engine/vec2si32.h"

#include "src/MainFrame/MainFrame.hpp"
#include "src/DrawElements/actors/Actor.hpp"

#include <iostream>

void EasyMain() {
  arctic::Font g_font;
  g_font.Load("data/arctic_one_bmf.fnt");

  bool left_mouse = false;
  auto mouse_pos = arctic::MousePos();

  auto mouse_wheel_pos = arctic::MouseWheelDelta();

  while (!IsKeyDownward(arctic::kKeyEscape)) {
    arctic::Clear();
    MainFrame::EraseElements();

    arctic::ResizeScreen(arctic::WindowSize());

    MainFrame::CreateMainFrame();

    if (arctic::IsKeyDown(arctic::KeyCode::kKeyLeft)) {
      MainFrame::GetCameraOffset().x -= 2;
    }

    if (arctic::IsKeyDown(arctic::KeyCode::kKeyDown)) {
      MainFrame::GetCameraOffset().y -= 2;
    }

    if (arctic::IsKeyDown(arctic::KeyCode::kKeyRight)) {
      MainFrame::GetCameraOffset().x += 2;
    }

    if (arctic::IsKeyDown(arctic::KeyCode::kKeyUp)) {
      MainFrame::GetCameraOffset().y += 2;
    }

    if (arctic::IsKeyDown(arctic::KeyCode::kKeyEquals)) {
      MainFrame::GetScaleFactor() += 0.01;
    }

    if (arctic::IsKeyDown(arctic::KeyCode::kKeyMinus)) {
      MainFrame::GetScaleFactor() -= 0.01;
    }

    if (MainFrame::CheckMouseIn() && arctic::IsKeyDown(arctic::KeyCode::kKeyMouseLeft)) {
      if (left_mouse) {
        MainFrame::GetCameraOffset() += arctic::Vec2Si32(arctic::Vec2D(mouse_pos - arctic::MousePos()) / MainFrame::GetScaleFactor());
      } else {
        left_mouse = true;
      }
      mouse_pos = arctic::MousePos();
    } else {
      if (left_mouse) {
        left_mouse = false;
      }
    }

    
    MainFrame::GetScaleFactor() -= arctic::MouseWheelDelta() * 0.001;


    MainFrame::DrawFrame();
    MainFrame::DrawNCircles(100);

    MainFrame::AddDrawElement(new TransportLine(0, 10));
    MainFrame::AddDrawElement(new TransportLine(10, 45));

    MainFrame::DrawElements();

    arctic::ShowFrame();
  }
}
