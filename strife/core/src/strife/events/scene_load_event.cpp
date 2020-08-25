#include "strife/events/scene_load_event.h"

using namespace strife::core;
using namespace strife::events;

Scene& SceneLoadEvent::scene() const {
    return scene_;
}

SceneLoadEvent::SceneLoadEvent(Scene& scene)
    : functional::Message()
    , scene_(scene) {}