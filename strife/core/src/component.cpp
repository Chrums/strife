#include "component.h"

using namespace strife::common;
using namespace strife::core;

Component::Component(const Entity entity)
    : entity(entity) {}

const Data Component::serialize() const {
    return Data();
}

void Component::deserialize(const Data& data) {}