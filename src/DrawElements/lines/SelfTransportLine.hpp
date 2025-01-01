#pragma once

#include "TransportLine.hpp"
#include "engine/easy_drawing.h"
#include "engine/vec2f.h"
#include "engine/vec2si32.h"
#include "log/Logs.hpp"

class SelfTransportLine : public TransportLine {
public:
    SelfTransportLine(ActorId from, ActorId to) :
        TransportLine(from, to) {}

    void Draw(const Drawer* drawer) const override {
        Actor* fromActor = drawer->GetActorStorage()[
            drawer->GetActorIdToStorageInd().at(fromTo_.first)
        ];

        Vec2Si32 fromCoord = fromActor->GetOffset();

        Camera* camera = drawer->GetCamera();
        Vec2Si32 center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

        fromCoord -= camera->GetOffset();

        fromCoord.x =
            center.x - (center.x - fromCoord.x) * camera->GetScaleFactor();
        fromCoord.y =
            center.y - (center.y - fromCoord.y) * camera->GetScaleFactor();

        Vec2Si32 typeBlockSizeFrom = fromActor->GetSize();
        Vec2F leftDownBlockCornerFrom = Vec2F(fromCoord) -  Vec2F(8, 40);
        Vec2F rightUpCornerFrom = Vec2F(fromCoord + typeBlockSizeFrom) -  Vec2F(-5, 20);

        

        double width = rightUpCornerFrom.x - leftDownBlockCornerFrom.x;
        double height = rightUpCornerFrom.y - leftDownBlockCornerFrom.y;

        Vec2F point1 =
            leftDownBlockCornerFrom + Vec2F(width / 2 - height / 2, height);

        Vec2F point4 = point1 + Vec2F(height, 0);

        Vec2F point2 = point1 + Vec2F(0, 2*height);
        Vec2F point3 = point4 + Vec2F(0, 2*height);

        DrawLine(drawer->GetDrawSprite(), Vec2Si32(point1), Vec2Si32(point2), Rgba(0, 0, 120));
        DrawLine(drawer->GetDrawSprite(), Vec2Si32(point2), Vec2Si32(point3), Rgba(0, 0, 120));

        Sprite sprite = drawer->GetDrawSprite();
        DrawArrow(sprite, point3, point4, 2, 30, 50, Rgba(0, 0, 120));
    }

    Vec2Si32 GetTransportLinePoint(const Drawer* drawer, double part) const override {
        Actor* fromActor = drawer->GetActorStorage()[
            drawer->GetActorIdToStorageInd().at(fromTo_.first)
        ];

        Vec2Si32 fromCoord = fromActor->GetOffset();

        Camera* camera = drawer->GetCamera();
        Vec2Si32 center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

        fromCoord -= camera->GetOffset();

        fromCoord.x =
            center.x - (center.x - fromCoord.x) * camera->GetScaleFactor();
        fromCoord.y =
            center.y - (center.y - fromCoord.y) * camera->GetScaleFactor();

        Vec2Si32 typeBlockSizeFrom = fromActor->GetSize();
        Vec2F leftDownBlockCornerFrom = Vec2F(fromCoord) -  Vec2F(8, 40);
        Vec2F rightUpCornerFrom = Vec2F(fromCoord + typeBlockSizeFrom) -  Vec2F(-5, 20);


        double width = rightUpCornerFrom.x - leftDownBlockCornerFrom.x;
        double height = rightUpCornerFrom.y - leftDownBlockCornerFrom.y;

        Vec2F point1 =
            leftDownBlockCornerFrom + Vec2F(width / 2 - height / 2, height);

        Vec2F point4 = point1 + Vec2F(height, 0);

        Vec2F point2 = point1 + Vec2F(0, 2*height);
        Vec2F point3 = point4 + Vec2F(0, 2*height);

        std::array<double, 3> distations{
          std::sqrt(((point2 - point1).x*(point2 - point1).x) +
          ((point2 - point1).y*(point2 - point1).y)),

          std::sqrt(((point3 - point2).x*(point3 - point2).x) +
          ((point3 - point2).y*(point3 - point2).y)),

          std::sqrt(((point4 - point3).x*(point4 - point3).x) +
          ((point4 - point3).y*(point4 - point3).y))
        };
        

        double sumLen = 0;
        for (double dist : distations) {
            sumLen += dist;
        }

        double curLen = sumLen * part;

        if (curLen <= distations[0]) {
            return Vec2Si32(point1 + (point2 - point1) * (curLen / distations[0]));
        }

        if (curLen <= distations[0] + distations[1]) {
            return Vec2Si32(point2 + (point3 - point2) * ((curLen - distations[0]) / distations[1]));
        }

        return Vec2Si32(point3 + (point4 - point3) * ((curLen - distations[0] - distations[1]) / distations[2]));
    }
};