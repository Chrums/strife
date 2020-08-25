#include "strife/events/scene_swap_event.h"

using namespace strife::core;
using namespace strife::events;

Scene* const SceneSwapEvent::from() const {
    return from_;
}

Scene* const SceneSwapEvent::to() const {
    return to_;
}

SceneSwapEvent::SceneSwapEvent(Scene* const from, Scene* const to)
    : functional::Message()
    , from_(from)
    , to_(to) {}