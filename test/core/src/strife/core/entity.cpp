#include "strife/core/entity.h"
#include "strife/core/scene.h"

using namespace strife;

#pragma region Components

Entity::Components::Components(Entity& entity)
    : entity_(entity) {}

Component& Entity::Components::add(const Type& type) {
    return entity_.scene().components().add(type, entity_);
}

void Entity::Components::remove(const Type& type) {
    entity_.scene().components().remove(type, entity_);
}

Component* const Entity::Components::find(const Type& type) {
    return entity_.scene().components().find(type, entity_);
}

#pragma endregion

const Scene& Entity::scene() const {
    return *scene_;
}

Scene& Entity::scene() {
    return *scene_;
}

const Identifier& Entity::identifier() const {
    return identifier_;
}

Identifier& Entity::identifier() {
    return identifier_;
}

const Entity::Components& Entity::components() const {
    return components_;
}

Entity::Components& Entity::components() {
    return components_;
}

Entity::Entity()
    : scene_(nullptr)
    , identifier_(Identifier::Nil())
    , components_(*this) {}

Entity::Entity(Scene& scene)
    : scene_(&scene)
    , identifier_(Identifier::Random())
    , components_(*this) {}

Entity& Entity::operator=(const Entity& entity) {
    scene_ = entity.scene_;
    identifier_ = entity.identifier_;
    return *this;
}

bool Entity::operator==(const Entity& entity) const {
    return identifier_ == entity.identifier_;
}

bool Entity::operator<(const Entity& entity) const {
    return identifier_ < entity.identifier_;
}