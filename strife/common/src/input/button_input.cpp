#include "input/button_input.h"

using namespace strife::common;

const float ButtonInput::value() const {
    return value_;
}

const bool ButtonInput::isDown() const {
    return value_ != 0.0f;
}