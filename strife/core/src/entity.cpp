#include "entity.h"

#include "scene.h"
#include "storage.h"

using namespace strife::core;
using namespace strife::common;
using namespace std;

Entity::Components::Components(Entity& entity)
    : entity_(entity) {}
    
Component& Entity::Components::add(const type_index type) {
	return entity_.scene.components.add(type, entity_);
}

void Entity::Components::remove(const type_index type) {
	entity_.scene.components.remove(type, entity_);
}

Component& Entity::Components::at(const type_index type) const {
	return entity_.scene.components.at(type, entity_);
}

Component* const Entity::Components::get(const type_index type) const {
	return entity_.scene.components.get(type, entity_);
}

Entity::Entity(const Entity& entity)
    : Unique(entity)
    , scene(entity.scene)
    , components(*this) {}
    
Entity::Entity(Scene& scene)
    : scene(scene)
    , components(*this) {}
    
bool Entity::operator==(const Entity& entity) const {
	return id == entity.id;
}

bool Entity::operator!=(const Entity& entity) const {
	return !(id == entity.id);
}

void Entity::destroy() {
	scene.entities.remove(*this);
}