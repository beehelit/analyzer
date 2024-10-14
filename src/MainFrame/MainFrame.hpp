#pragma once

#include "analizer/src/DrawElements/IDrawElement.hpp"
#include "engine/arctic_types.h"
#include "engine/easy_sprite.h"
#include "engine/vec2si32.h"
class MainFrame {
public:
    static const arctic::Si32 kBottom_div = 10;
    static const arctic::Si32 kTop_div = 20;
    static const arctic::Si32 kSides_div = 25;
    
    static void CreateMainFrame();
    
    static void DrawFrame();
    static arctic::Vec2Si32 FrameSize();

    static void DrawElipse();
    static void DrawNCircles(arctic::Ui32);

    static void DrawElements();
    static void AddDrawElement(IDrawElement*);

    static void EraseElements();

    static arctic::Vec2Si32& GetCameraOffset() {
        return cameraOffset_;
    }

    static double& GetScaleFactor() {
        return scaleFactor_;
    }

    static arctic::Sprite GetSprite() {
        return mainFrameSprite_;
    }

    static arctic::Vec2Si32 GetCenter() {
        return cameraOffset_ + FrameSize() / 2;
    }

    static bool CheckMouseIn();

    static arctic::Vec2Si32& GetMouseOffset() {
        return mouseOffset_;
    }

    static void ActorAdded() {
        actorNumbers_.push_back(drawElements_.size() - 1);
    }

    static auto& GetActorsList() {
        return actorNumbers_;
    }

    static auto& GetDrawElements() {
        return drawElements_;
    }

private:
    MainFrame();


    static arctic::Sprite mainFrameSprite_;

    static double ElipseLen();
    static arctic::Vec2Si32 PixFromElipseCoord(double);

    static std::vector<IDrawElement*> drawElements_;
    static arctic::Vec2Si32 cameraOffset_;

    static double scaleFactor_;

    static arctic::Vec2Si32 mouseOffset_;

    static std::vector<arctic::Si32> actorNumbers_;
};