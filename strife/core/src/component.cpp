#include "component.h"

using namespace strife::common;
using namespace strife::core;

Component::Component(const Entity entity)
    : entity(entity) {}

Data Component::serialize() {
    return Data();
}

void Component::deserialize(Data data) {}