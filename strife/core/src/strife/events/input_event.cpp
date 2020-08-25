#include "strife/events/input_event.h"

using namespace strife::events;

const SDL_Event& InputEvent::event() const {
    return event_;
}

InputEvent::InputEvent(const SDL_Event& event)
    : functional::Message()
    , event_(event) {}