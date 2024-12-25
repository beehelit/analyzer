#include <camera/Camera.hpp>
#include <seet/ElipseSeet.hpp>
#include <seet/GreedSeet.hpp>
#include <window/RectWinDraw.hpp>
#include <window/RectangleWindow/RectangleWindow.hpp>
#include <DrawElements/actors/Actor.hpp>
#include <log/log_reader/LogReader.hpp>
#include <log/Logs.hpp>
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
#include "engine/easy_sprite.h"
#include "engine/easy_util.h"
#include "engine/rgba.h"
#include "engine/vec2d.h"
#include "engine/vec2si32.h"
#include "window/Drawer/DrawBoxOptions.hpp"

#include <iostream>
#include <memory>

void EasyMain() {
  arctic::Font gFont_;
  gFont_.Load("data/arctic_one_bmf.fnt");

  Logs::ReadLogs("data/storage_start_err.log");

  GreedSeet gseet(std::pair(arctic::WindowSize().x, arctic::WindowSize().y), 
                  std::max(1ull, 9000 / Logs::GetMaxActorId()));
  gseet.PrepareTables();

  Camera camera;
  Mouse mouse;
  PlayerPausePlay ppp;
  ppp.SetMouse(&mouse);

  TimeLine timeLine;
  timeLine.SetMouse(&mouse);
  timeLine.SetMaxTime(Logs::GetMaxTime());

  ppp.SetAction([&timeLine](){
    timeLine.SetStatus(!timeLine.GetStatus());
  });

  SpeedUpButton speedUpButton;
  speedUpButton.SetMouse(&mouse);
  speedUpButton.SetAction([&timeLine]() {
    timeLine.SetSpeed(timeLine.GetSpeed() + 10);
  });

  while (!IsKeyDownward(arctic::kKeyEscape)) {
    arctic::Clear();
    arctic::ResizeScreen(arctic::WindowSize());

    DrawBox screen;
    screen.SetDrawSprite(arctic::GetEngine()->GetBackbuffer());
    screen.SetDrawOptions(DrawBoxOptions{
      .flex_type="column",
      .flex_list={0.05, 0.95}  
    });

    DrawBox footer;
    footer.SetDrawOptions(DrawBoxOptions{
      .flex_type="row",
      .background_color=arctic::Rgba(131, 131, 131),
      .flex_list={0.02, 0.96, 0.02}
    });

    DrawBox playerPausePlay;
    DrawBox timeLineBox;
    timeLineBox.SetDrawOptions(DrawBoxOptions{
      .background_color=arctic::Rgba(255, 0, 255)
    });
    DrawBox speedUpBox;
    speedUpBox.SetDrawOptions(DrawBoxOptions{
      .background_color=arctic::Rgba(100, 100, 140)
    });

    timeLineBox.SetDrawElement(&timeLine);
    
    playerPausePlay.SetDrawOptions(DrawBoxOptions{
      .background_color=arctic::Rgba(0, 0, 0, 0)
    });

    playerPausePlay.SetDrawElement(&ppp);

    speedUpBox.SetDrawElement(&speedUpButton);
    speedUpBox.SetDrawOptions(DrawBoxOptions{
      .background_color=arctic::Rgba(130, 56, 90)
    });

    footer.AddDrawer(&playerPausePlay);
    footer.AddDrawer(&timeLineBox);
    footer.AddDrawer(&speedUpBox);

    RectWinDraw mainFrame;

    screen.AddDrawer(&footer);
    screen.AddDrawer(&mainFrame);

    mainFrame.SetBackgroundColor(arctic::Rgba(232, 227, 227));

    screen.Draw();

    mainFrame.SetCamera(&camera);
    mainFrame.SetMouse(&mouse);
    
    mainFrame.SetGreedSeet(&gseet);

    for (ActorId i = 0; i <= Logs::GetMaxActorId(); ++i) {
      if (!gseet.HaveCoord(i)) {
        continue;
      }

      bool visible = Logs::IsAlife(i, timeLine.GetTime());

      mainFrame.AddDrawElement(
        new Actor(gseet.GetCoord(i), 
                                      std::max(1ull, 9000 / Logs::GetMaxActorId()), 
                                      i, 
                                      visible)
      );
    }

    for (Logs::LogMessage event : Logs::GetLogMessages()) {
      if (!gseet.HaveCoord(event.from) || !gseet.HaveCoord(event.to)) {
        continue;
      }

      if (event.start <= timeLine.GetTime() && event.end >= timeLine.GetTime()) {
        TransportLine* tLine = new TransportLine(event.from, event.to);
        mainFrame.AddDrawElement(tLine);
        mainFrame.AddDrawElement(new Message(
          tLine, (1.0 * timeLine.GetTime() - event.start) / (event.end - event.start)
        ));
      }
    }

    screen.Draw();
    ppp.Listen();
    timeLine.Listen();
    speedUpButton.Listen();
    mainFrame.Listen();

    Time curTime = timeLine.GetTime();
    std::string time = std::to_string(curTime / 1'000'000) + '.' + 
                       std::to_string(curTime % 1'000'000) + "s";

    arctic::Vec2Si32 timeSize = gFont_.EvaluateSize(time.c_str(), false);
    gFont_.Draw(mainFrame.GetDrawSprite(), time.c_str(),
                mainFrame.GetDrawSprite().Size().x - timeSize.x, mainFrame.GetDrawSprite().Size().y - timeSize.y,
                arctic::kTextOriginTop, arctic::kTextAlignmentLeft,
                arctic::kDrawBlendingModeColorize, arctic::kFilterNearest,
                arctic::Rgba(255, 0, 0));

    arctic::ShowFrame();
  }
}
