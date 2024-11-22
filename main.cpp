#include <camera/Camera.hpp>
#include <seet/ElipseSeet.hpp>
#include <seet/GreedSeet.hpp>
#include <window/RectWinDraw.hpp>
#include <window/RectangleWindow/RectangleWindow.hpp>
#include <DrawElements/actors/Actor.hpp>
#include <Logs/log_reader/LogReader.hpp>
#include <Logs/Logs.hpp>
#include <DrawElements/lines/TransportLine.hpp>
#include <DrawElements//fps/FpsCounter.hpp>
#include <DrawElements/fps/Fps.hpp>
#include <window/buttons/cbutton/CButton.hpp>
#include <window/Drawer/DrawBox.hpp>
#include <window/RectangleWindow/Footer.hpp>
#include <window/buttons/cbutton/speed/SpeedUpButton.hpp>
#include <window/buttons/cbutton/time_line/TimeLine.hpp>
#include <DrawElements/messages/message.hpp>

#include <window/buttons/cbutton/CButton.hpp>
#include <window/buttons/cbutton/player_pause_play/PlayerPausePlay.hpp>

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
  LogReader logReader;
  logReader.ReadFile("data/storage_start_err.log", 10000);
  logReader.ReadConfig("data/seet.config", Config::SEET);

  std::map<std::string, size_t> seetInfo = logReader.GetSeetInfo();
  
  Logs logs(logReader);
  logs.Normalize();

  size_t actorsCount = logs.GetActorsCount();
  ActorId maxActorId = logs.GetMaxActorNum();

  // 

  std::shared_ptr<Camera> mainCamera = std::make_shared<Camera>();
  std::shared_ptr<Mouse> globalMouse = std::make_shared<Mouse>();
  std::shared_ptr<PlayerPausePlay> pausePlay = std::make_shared<PlayerPausePlay>();
  std::shared_ptr<TimeLine> timeLine = std::make_shared<TimeLine>();
  std::shared_ptr<SpeedUpButton> speedUp = std::make_shared<SpeedUpButton>();
  
  pausePlay->SetMouse(globalMouse.get());
  pausePlay->SetAction([&timeLine](){
    timeLine->SetStatus(!timeLine->GetStatus());
  });

  speedUp->SetMouse(globalMouse.get());
  speedUp->SetAction([&timeLine]() {
    timeLine->SetSpeed(timeLine->GetSpeed() + 1);
  });

  timeLine->SetMouse(globalMouse.get());
  timeLine->SetMaxTime(logs.GetMaxTime());


  while (!IsKeyDownward(arctic::kKeyEscape)) {
    FpsCounter::Start();

    arctic::Clear();
    arctic::ResizeScreen(arctic::WindowSize() / 2);

    arctic::Vec2Si32 screenSize = arctic::ScreenSize();
    int marginBottom = screenSize.y / 10;
    arctic::Vec2Si32 leftBottomCorner = arctic::Vec2Si32(0, marginBottom);

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

    GreedSeet gseet(&mainFrame, logReader);

    for (int i = 0; i <= maxActorId; ++i) {
      mainFrame.AddDrawElement(new Actor(gseet.GetCoord(i), std::max(1ul, 1000 / actorsCount)));
    }

    for (Event event : logs.GetEvents()) {
      if (event.start <= timeLine->GetTime() && event.end >= timeLine->GetTime()) {
        TransportLine* tLine = new TransportLine(event.from, event.to);
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

    arctic::Sprite speedUpSprite;
    speedUpSprite.Reference(footerSprite,
      arctic::Vec2Si32(footerSprite.Size().x - playButtonSprite.Size().x, 0),
      arctic::Vec2Si32(footerSprite.Size().x, footerSprite.Size().y));
    speedUp->SetSprite(speedUpSprite);
    footer.AddSubWindow(new DrawBox(speedUp.get()));

    mainFrame.AddDrawElement(new Fps());
    mainFrame.Listen();
    footer.Listen();

    mainFrame.Draw();
    footer.Draw();
    arctic::ShowFrame();
  }
}
