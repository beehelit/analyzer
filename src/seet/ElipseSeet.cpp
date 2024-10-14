#include "ElipseSeet.hpp"
#include "analizer/src/window/RectangleWindow/RectangleWindow.hpp"
#include "engine/vec2si32.h"

double ElipseSeet::ElipseLen() {
    // TODO for all window
    auto window = dynamic_cast<RectangleWindow*>(window_);
    auto frameSize = window->GetWindowSize();

    auto widthHalf = frameSize.x / 2;
    auto heightHalf = frameSize.y / 2;
    const auto& a = widthHalf;
    const auto& b = heightHalf;

    // ramanudjana formula
    double elipseLen = std::acos(-1) * (3*(a+b) - std::sqrt((3*a + b) * (a + 3*b)));

    return elipseLen;
}

void ElipseSeet::SeetN(arctic::Ui32 count) {
    seetCount_ = count;
}

arctic::Vec2Si32 ElipseSeet::PixFromElipseCoord(double elipseCoord) {
    double radCoord = (elipseCoord / ElipseLen()) * 2 * std::acos(-1);    

    // TODO for all window
    auto window = dynamic_cast<RectangleWindow*>(window_);
    auto frameSize = window->GetWindowSize();

    double x = (frameSize.x / 2.0) * std::cos(radCoord);
    double y = (frameSize.y / 2.0) * std::sin(radCoord);

    return arctic::Vec2Si32(x + frameSize.x / 2.0, y + frameSize.y / 2.0);
}

arctic::Vec2Si32 ElipseSeet::GetCoord(arctic::Ui32 number) {
    auto elipseLen = ElipseLen();
    auto delta = elipseLen / seetCount_;

    return PixFromElipseCoord(delta * number);
}