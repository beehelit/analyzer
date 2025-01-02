#include <camera/Camera.hpp>
#include <seet/ElipseSeet.hpp>
#include <seet/GreedSeet.hpp>
#include <window/RectWinDraw.hpp>
#include <window/RectangleWindow/RectangleWindow.hpp>
#include <DrawElements/actors/Actor.hpp>
#include <log/log_reader/LogReader.hpp>
#include <log/Logs.hpp>
#include <DrawElements/lines/TransportLine.hpp>
#include <DrawElements/lines/SelfTransportLine.hpp>
#include <DrawElements//fps/FpsCounter.hpp>
#include <DrawElements/fps/Fps.hpp>
#include <window/buttons/cbutton/CButton.hpp>
#include <window/Drawer/DrawBox.hpp>
#include <window/RectangleWindow/Footer.hpp>
#include <window/buttons/cbutton/speed/SpeedUpButton.hpp>
#include <window/buttons/cbutton/speed/SpeedDownButton.hpp>
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
#include "engine/font.h"
#include "engine/rgba.h"
#include "engine/vec2d.h"
#include "engine/vec2si32.h"
#include "window/Drawer/DrawBoxOptions.hpp"

#include <iostream>
#include <memory>

#include <fstream>

using namespace arctic;

void EasyMain() {

  Font gFont_;
  gFont_.Load("data/arctic_one_bmf.fnt");

  Logs::ReadLogs("data/storage_start_err.log");

  GreedSeet gseet(std::pair(WindowSize().x, WindowSize().y), 
                  std::max(static_cast<ActorId>(1), 9000 / Logs::GetMaxActorId()));
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
    timeLine.SetSpeed(timeLine.GetSpeed() + 2);
  });

  SpeedDownButton speedDownButton;
  speedDownButton.SetMouse(&mouse);
  speedDownButton.SetAction([&timeLine]() {
    timeLine.SetSpeed(timeLine.GetSpeed() - 2);
  });

  while (!IsKeyDownward( kKeyEscape)) {
     Clear();
     ResizeScreen( WindowSize());

    DrawBox screen;
    screen.SetDrawSprite( GetEngine()->GetBackbuffer());
    screen.SetDrawOptions(DrawBoxOptions{
      .flex_type="column",
      .flex_list={0.05, 0.95}  
    });

    DrawBox footer;
    footer.SetDrawOptions(DrawBoxOptions{
      .flex_type="row",
      .flex_list={0.02, 0.90, 0.08},
      .background_color= Rgba(131, 131, 131)
    });

    DrawBox playerPausePlay;
    DrawBox timeLineBox;
    timeLineBox.SetDrawOptions(DrawBoxOptions{
      .background_color= Rgba(131, 131, 131),
      .padding_right=0.05,
      .padding_left=0.05,
      .padding_top=0.3,
      .padding_bottom=0.3
    });

    DrawBox speedBox;
    speedBox.SetDrawOptions(DrawBoxOptions{
      .flex_type="column",
      .flex_list={0.5, 0.5}
    });

    DrawBox speedChangeBox;
    speedChangeBox.SetDrawOptions(DrawBoxOptions{
      .flex_type="row",
    });

    DrawBox speedUpBox;
    speedUpBox.SetDrawOptions(DrawBoxOptions{
      .background_color=Rgba(131, 131, 131),
      .padding_right=0.3,
      .padding_left=0.3,
      .padding_top=0.2,
      .padding_bottom=0.2
    });

    DrawBox speedDownBox;
    speedDownBox.SetDrawOptions(DrawBoxOptions{
      .background_color=Rgba(131, 131, 131),
      .padding_right=0.3,
      .padding_left=0.3
    });

    timeLineBox.SetDrawElement(&timeLine);
    
    playerPausePlay.SetDrawOptions(DrawBoxOptions{
      .background_color= Rgba(0, 0, 0, 0)
    });

    playerPausePlay.SetDrawElement(&ppp);

    speedUpBox.SetDrawElement(&speedUpButton);
    speedDownBox.SetDrawElement(&speedDownButton);

    footer.AddDrawer(&playerPausePlay);
    footer.AddDrawer(&timeLineBox);

    footer.AddDrawer(&speedBox);
    //footer.AddDrawer(&speedUpBox);

    RectWinDraw empty1;
    empty1.SetBackgroundColor(Rgba(131, 131, 131));

    speedBox.AddDrawer(&empty1);
    speedBox.AddDrawer(&speedChangeBox);

    speedChangeBox.AddDrawer(&speedDownBox);
    speedChangeBox.AddDrawer(&speedUpBox);

    RectWinDraw mainFrame;

    screen.AddDrawer(&footer);
    screen.AddDrawer(&mainFrame);

    mainFrame.SetBackgroundColor( Rgba(232, 227, 227));

    screen.Draw();

    mainFrame.SetCamera(&camera);
    mainFrame.SetMouse(&mouse);
    
    mainFrame.SetGreedSeet(&gseet);

    for (ActorId i = 0; i <= Logs::GetMaxActorId(); ++i) {
      if (!gseet.HaveCoord(i)) {
        continue;
      }

      bool visible = Logs::IsAlife(i, timeLine.GetTime());
      bool active = Logs::CheckActorActivity(i, timeLine.GetTime());

      mainFrame.AddDrawElement(
        new Actor(gseet.GetCoord(i), 
                                      std::max(static_cast<ActorId>(1), 9000 / Logs::GetMaxActorId()), 
                                      i, 
                                      visible, 
                                      active,
                                      gFont_)
      );
    }

    for (Logs::LogMessage event : Logs::GetLogMessages()) {
      if (!gseet.HaveCoord(event.from) || !gseet.HaveCoord(event.to)) {
        continue;
      }

      if (event.start <= timeLine.GetTime() && event.end >= timeLine.GetTime()) {
        TransportLine* tLine = nullptr;
        if (event.from == event.to) {
          tLine = new SelfTransportLine(event.from, event.to);
        } else {
          tLine = new TransportLine(event.from, event.to);
        }

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
    speedDownButton.Listen();
    mainFrame.Listen();

    VisualisationTime curTime = timeLine.GetTime();
    std::string time = std::to_string(curTime / 1'000'000) + '.' + 
                       std::to_string(curTime % 1'000'000) + "s";
    Vec2Si32 timeSize = gFont_.EvaluateSize(time.c_str(), false);
    gFont_.Draw(mainFrame.GetDrawSprite(), time.c_str(),
                mainFrame.GetDrawSprite().Size().x - timeSize.x, mainFrame.GetDrawSprite().Size().y - timeSize.y,
                 kTextOriginTop,  kTextAlignmentLeft,
                 kDrawBlendingModeColorize,  kFilterNearest,
                 Rgba(255, 0, 0));

    int curSpeed = timeLine.GetSpeed();
    std::string speed = "Speed: " + std::to_string(curSpeed) + "x";
    Vec2Si32 speedSize = gFont_.EvaluateSize(speed.c_str(), false);
    gFont_.Draw(footer.GetDrawSprite(), speed.c_str(),
                footer.GetDrawSprite().Size().x - speedSize.x, 0,
                kTextOriginBottom, kTextAlignmentRight,
                kDrawBlendingModeColorize, kFilterNearest,
                Rgba(0, 255, 120));

     ShowFrame();
  }
}
