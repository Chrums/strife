#include "component.h"

using namespace strife::common;
using namespace strife::serialization;
using namespace strife::core;

const Entity& Component::entity() {
    return entity_;
}

Component::Component(const Entity& entity)
    : entity_(entity) {}

const Data Component::serialize() const {
    return Data();
}

void Component::deserialize(const Data& data) {}