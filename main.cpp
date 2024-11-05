#include "analizer/src/camera/Camera.hpp"
#include "analizer/src/seet/ElipseSeet.hpp"
#include "analizer/src/window/RectWinDraw.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"
#include "analizer/src/DrawElements/actors/Actor.hpp"
#include "analizer/src/Logs/LogsReader/LogsReader.hpp"
#include "analizer/src/Logs/Logs.hpp"
#include "analizer/src/DrawElements/lines/TransportLine.hpp"
#include "analizer/src/DrawElements//fps/FpsCounter.hpp"
#include "analizer/src/DrawElements/fps/Fps.hpp"
#include "analizer/src/window/buttons/cbutton/CButton.hpp"
#include "analizer/src/window/Drawer/DrawBox.hpp"
#include "analizer/src/window/RectangleWindow/Footer.hpp"
#include "analizer/src/window/buttons/cbutton/time_line/TimeLine.hpp"
#include "analizer/src/DrawElements/messages/message.hpp"

#include "analizer/src/window/buttons/cbutton/CButton.hpp"
#include "analizer/src/window/buttons/cbutton/player_pause_play/PlayerPausePlay.hpp"
#include "engine/arctic_input.h"
#include "engine/easy.h"
#include "engine/easy_advanced.h"
#include "engine/easy_input.h"
#include "engine/easy_util.h"
#include "engine/rgba.h"
#include "engine/vec2d.h"
#include "engine/vec2si32.h"

#include <iostream>
#include <memory>

void EasyMain() {
  LogsReader logsReader;
  logsReader.ReadFile("data/storage_start_err.log", 40000);
  
  Logs logs(logsReader);
  logs.Normalize();

  size_t actorsCount = logs.GetActorsCount();

  std::shared_ptr<Camera> mainCamera = std::make_shared<Camera>();
  std::shared_ptr<Mouse> globalMouse = std::make_shared<Mouse>();
  std::shared_ptr<PlayerPausePlay> pausePlay = std::make_shared<PlayerPausePlay>();
  std::shared_ptr<TimeLine> timeLine = std::make_shared<TimeLine>();
  
  pausePlay->SetMouse(globalMouse.get());
  pausePlay->SetAction([&timeLine](){
    timeLine->SetStatus(!timeLine->GetStatus());
  });

  timeLine->SetMouse(globalMouse.get());
  timeLine->SetMaxTime(logs.GetMaxTime());

  std::cout << logs.GetMaxTime() << std::endl;


  while (!IsKeyDownward(arctic::kKeyEscape)) {
    FpsCounter::Start();

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
      mainCamera.get(), globalMouse.get());
    mainFrame.Fill(arctic::Rgba(232, 227, 227));

    arctic::Sprite footerSprite;
    footerSprite.Reference(arctic::GetEngine()->GetBackbuffer(),
      arctic::Vec2Si32(0, 0),
      arctic::Vec2Si32(screenSize.x - 1, marginBottom - 1));
    Footer footer(footerSprite);
    footer.Fill(arctic::Rgba(34, 88, 224));

    ElipseSeet seet(&mainFrame);
    seet.SeetN(actorsCount);

    for (int i = 0; i < actorsCount; ++i) {
      mainFrame.AddDrawElement(new Actor(seet.GetCoord(i), std::max(1ul, 1000 / actorsCount)));
    }

    for (auto event : logs.GetEvents()) {
      if (event.start <= timeLine->GetTime() && event.end >= timeLine->GetTime()) {
        auto tLine = new TransportLine(event.from, event.to);
        mainFrame.AddDrawElement(tLine);
        mainFrame.AddDrawElement(new Message(
          tLine, (1.0 * timeLine->GetTime() - event.start) / (event.end - event.start)
        ));
      }
    }


//----------------

    arctic::Sprite playButtonSprite;
    playButtonSprite.Reference(footerSprite,
      arctic::Vec2Si32(0, 0),
      arctic::Vec2Si32(footerSprite.Size().y, footerSprite.Size().y)
      );
    pausePlay->SetSprite(playButtonSprite);    
    footer.AddSubWindow(new DrawBox(pausePlay.get()));
    

    arctic::Sprite timeLineSprite;
    timeLineSprite.Reference(footerSprite,
      arctic::Vec2Si32(playButtonSprite.Size().x, footerSprite.Size().y / 24 * 8),
      arctic::Vec2Si32(footerSprite.Size().x - 4*playButtonSprite.Size().x, footerSprite.Size().y / 24 * 9));
    timeLine->SetSprite(timeLineSprite);
    footer.AddSubWindow(new DrawBox(timeLine.get()));

    mainFrame.AddDrawElement(new Fps());
    mainFrame.Listen();
    footer.Listen();

    mainFrame.Draw();
    footer.Draw();
    arctic::ShowFrame();
  }
}
