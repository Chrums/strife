#include "strife/core/component.h"

using namespace strife::core;
using namespace strife::serialization;
using namespace strife::unique;

const Entity& Component::entity() {
    return entity_;
}

Component::Component(const Entity& entity)
    : Unique()
    , entity_(entity) {}

const Data Component::serialize() const {
    return Data();
}

void Component::deserialize(const Data& data) {}