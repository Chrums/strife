#include "strife/events/scene_unload_event.h"

using namespace strife::core;
using namespace strife::events;

Scene& SceneUnloadEvent::scene() const {
    return scene_;
}

SceneUnloadEvent::SceneUnloadEvent(Scene& scene)
    : functional::Message()
    , scene_(scene) {}