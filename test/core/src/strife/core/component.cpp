#include "strife/core/component.h"
#include "strife/core/entity.h"

using namespace strife;

const Entity& Component::entity() const {
    return *entity_;
}

Entity& Component::entity() {
    return *entity_;
}

Component::Component()
    : identifier_(Identifier::Nil())
    , entity_(nullptr) {}

Component::Component(const Entity& entity)
    : identifier_(Identifier::Random())
    , entity_(new Entity(entity)) {}

Component::~Component() {
    delete entity_;
}