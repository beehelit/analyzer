// Copyright (c) <year> Your name

#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/seet/ElipseSeet.hpp"
#include "analizer/src/window/RectWinDraw.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"
#include "analizer/src/DrawElements/actors/Actor.hpp"
#include "analizer/src/Logs/LogsReader/LogsReader.hpp"
#include "analizer/src/Logs/Logs.hpp"
#include "analizer/src/DrawElements/lines/TransportLine.hpp"

#include "engine/arctic_input.h"
#include "engine/easy.h"
#include "engine/easy_advanced.h"
#include "engine/easy_input.h"
#include "engine/easy_util.h"
#include "engine/vec2d.h"
#include "engine/vec2si32.h"

#include <iostream>

void EasyMain() {
  std::shared_ptr<Camera> mainCamera = std::make_shared<Camera>();

  LogsReader logsReader;
  logsReader.ReadFile("storage_start_err.log", 40000);
  
  Logs logs(logsReader);
  size_t actorsCount = logs.GetActorsCount();

  while (!IsKeyDownward(arctic::kKeyEscape)) {
    arctic::Clear();
    arctic::ResizeScreen(arctic::WindowSize());

    auto screenSize = arctic::ScreenSize();
    auto marginBottom = screenSize.y / 10;
    auto leftBottomCorner = arctic::Vec2Si32(0, marginBottom);

    arctic::Sprite mainFrameSprite;
    mainFrameSprite.Reference(arctic::GetEngine()->GetBackbuffer(), 
      leftBottomCorner,
      arctic::Vec2Si32(screenSize.x, screenSize.y - marginBottom));
    RectWinDraw mainFrame(mainFrameSprite,
      arctic::Vec2Si32(screenSize.x, screenSize.y - marginBottom),
      mainCamera);
    mainFrame.Fill(arctic::Rgba(232, 227, 227));

    mainCamera->SetMouse(Mouse(&mainFrame));
    mainCamera->Listen();

    arctic::Sprite timeLineSprite;
    timeLineSprite.Reference(arctic::GetEngine()->GetBackbuffer(),
      arctic::Vec2Si32(0, 0),
      arctic::Vec2Si32(screenSize.x - 1, marginBottom - 1));
    RectWinDraw timeLineFrame(timeLineSprite,
      arctic::Vec2Si32(screenSize.x, marginBottom));
    timeLineFrame.Fill(arctic::Rgba(34, 88, 224));

    ElipseSeet seet(&mainFrame);
    seet.SeetN(actorsCount);

    for (int i = 0; i < actorsCount; ++i) {
      mainFrame.AddDrawElement(new Actor(seet.GetCoord(i), std::max(1ul, 1000 / actorsCount)));
    }

    for (auto event : logs.GetEvents()) {
      mainFrame.AddDrawElement(new TransportLine(event.from, event.to));
    }

    mainFrame.Draw();
    arctic::ShowFrame();
  }
}
