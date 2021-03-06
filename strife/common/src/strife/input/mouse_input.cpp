#include "strife/input/mouse_input.h"

using namespace strife::input;
using namespace strife::math;

const Vector2i& MouseInput::position() const {
    return position_;
}

const ButtonInput& MouseInput::button(const int index) {
    return findMouseButtonProcessor(index);
}

MouseButtonProcessor& MouseInput::findMouseButtonProcessor(const int index) {
    return mouseButtonProcessors_.try_emplace(index).first->second;
}