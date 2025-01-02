#include "TransportLine.hpp"
#include <window/Drawer/Drawer.hpp>

void TransportLine::Draw(const Drawer *drawer) const {
    Actor* fromActor = drawer->GetActorStorage()[
      drawer->GetActorIdToStorageInd().at(fromTo_.first)
    ];
    Actor* toActor = drawer->GetActorStorage()[
      drawer->GetActorIdToStorageInd().at(fromTo_.second)
    ];

     Vec2Si32 fromCoord = fromActor->GetOffset();
     Vec2Si32 toCoord = toActor->GetOffset();

    Camera* camera = drawer->GetCamera();
     Vec2Si32 center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

    fromCoord -= camera->GetOffset();
    toCoord -= camera->GetOffset();

    fromCoord.x =
        center.x - (center.x - fromCoord.x) * camera->GetScaleFactor();
    fromCoord.y =
        center.y - (center.y - fromCoord.y) * camera->GetScaleFactor();

    Vec2Si32 typeBlockSizeFrom = fromActor->GetSize();
    Vec2F leftDownBlockCornerFrom = Vec2F(fromCoord) -  Vec2F(8, 40);
    Vec2F rightUpCornerFrom = Vec2F(fromCoord + typeBlockSizeFrom) -  Vec2F(-5, 20);
    Vec2Si32 fromCenter = Vec2Si32(leftDownBlockCornerFrom + (rightUpCornerFrom - leftDownBlockCornerFrom) / 2);

    toCoord.x = center.x - (center.x - toCoord.x) * camera->GetScaleFactor();
    toCoord.y = center.y - (center.y - toCoord.y) * camera->GetScaleFactor();

    Vec2Si32 typeBlockSizeTo = toActor->GetSize();
    Vec2F leftDownBlockCornerTo = Vec2F(toCoord) -  Vec2F(8, 40);
    Vec2F rightUpCornerTo = Vec2F(toCoord + typeBlockSizeTo) -  Vec2F(-5, 20);
    Vec2Si32 toCenter = Vec2Si32(leftDownBlockCornerTo + (rightUpCornerTo - leftDownBlockCornerTo) / 2);

    Vec2F fromEdge = BlockEdgePos(leftDownBlockCornerFrom, Vec2F(typeBlockSizeFrom), 5.0, Vec2F(toCenter - fromCenter));
    Vec2F toEdge = BlockEdgePos(leftDownBlockCornerTo, Vec2F(typeBlockSizeTo), 5.0, Vec2F(fromCenter - toCenter));

    Sprite sprite = drawer->GetDrawSprite();

     DrawArrow(sprite,  Vec2F(fromEdge),  Vec2F(toEdge),
                     2, 30, 50,
                      Rgba(120, 0, 0));
}

Vec2Si32 TransportLine::GetTransportLinePoint(const Drawer* drawer, double part) const {
    part = std::min(part, 1.);
    part = std::max(part, 0.);

    Actor* fromActor = drawer->GetActorStorage()[
      drawer->GetActorIdToStorageInd().at(fromTo_.first)
    ];
    Actor* toActor = drawer->GetActorStorage()[
      drawer->GetActorIdToStorageInd().at(fromTo_.second)
    ];

     Vec2Si32 fromCoord = fromActor->GetOffset();
     Vec2Si32 toCoord = toActor->GetOffset();

    Camera* camera = drawer->GetCamera();
     Vec2Si32 center = drawer->GetWindow()->GetFrameSprite().Size() / 2;

    fromCoord -= camera->GetOffset();
    toCoord -= camera->GetOffset();

    fromCoord.x =
        center.x - (center.x - fromCoord.x) * camera->GetScaleFactor();
    fromCoord.y =
        center.y - (center.y - fromCoord.y) * camera->GetScaleFactor();

    Vec2Si32 typeBlockSizeFrom = fromActor->GetSize();
    Vec2F leftDownBlockCornerFrom = Vec2F(fromCoord) -  Vec2F(8, 40);
    Vec2F rightUpCornerFrom = Vec2F(fromCoord + typeBlockSizeFrom) -  Vec2F(-5, 20);
    Vec2Si32 fromCenter = Vec2Si32(leftDownBlockCornerFrom + (rightUpCornerFrom - leftDownBlockCornerFrom) / 2);

    toCoord.x = center.x - (center.x - toCoord.x) * camera->GetScaleFactor();
    toCoord.y = center.y - (center.y - toCoord.y) * camera->GetScaleFactor();

    Vec2Si32 typeBlockSizeTo = toActor->GetSize();
    Vec2F leftDownBlockCornerTo = Vec2F(toCoord) -  Vec2F(8, 40);
    Vec2F rightUpCornerTo = Vec2F(toCoord + typeBlockSizeTo) -  Vec2F(-5, 20);
    Vec2Si32 toCenter = Vec2Si32(leftDownBlockCornerTo + (rightUpCornerTo - leftDownBlockCornerTo) / 2);

    Vec2F fromEdge = BlockEdgePos(leftDownBlockCornerFrom, Vec2F(typeBlockSizeFrom), 5.0, Vec2F(toCenter - fromCenter));
    Vec2F toEdge = BlockEdgePos(leftDownBlockCornerTo, Vec2F(typeBlockSizeTo), 5.0, Vec2F(fromCenter - toCenter));

    double len = std::sqrt((fromEdge - toEdge).x * (fromEdge - toEdge).x + 
                 (fromEdge - toEdge).y * (fromEdge - toEdge).y);

    double curPoint = len * part;
    Vec2F dirNormal = (toEdge - fromEdge) / len;


    return Vec2Si32(fromEdge + dirNormal * curPoint);
}