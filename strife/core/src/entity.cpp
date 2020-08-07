#include "entity.h"

#include "component.h"
#include "scene.h"
#include "storage.h"
#include "serialization/serialization.h"

using namespace std;
using namespace strife::core;
using namespace strife::common;

Entity::Components::Components(Entity& entity)
    : entity_(entity) {}

Entity::Components::Components(const Entity::Components& components)
    : entity_(components.entity_) {}
    
Component& Entity::Components::add(const type_index type) {
	return entity_.scene_->components.add(type, entity_);
}

void Entity::Components::remove(const type_index type) {
	entity_.scene_->components.remove(type, entity_);
}

Component& Entity::Components::at(const type_index type) const {
	return entity_.scene_->components.at(type, entity_);
}

Component* const Entity::Components::find(const type_index type) const {
	return entity_.scene_->components.find(type, entity_);
}

Scene& Entity::scene() const {
	return *scene_;
}

Entity::Components& Entity::components() {
	return components_;
}

Entity::Entity()
	: Unique()
	, scene_(nullptr)
	, components_(*this) {}

Entity::Entity(const Entity& entity)
    : Unique(entity)
    , scene_(entity.scene_)
    , components_(*this) {}
    
Entity::Entity(Scene& scene)
    : Unique()
	, scene_(&scene)
    , components_(*this) {}
    
Entity& Entity::operator=(const Entity& entity) {
	id_ = entity.id_;
	return *this;
}

bool Entity::operator==(const Entity& entity) const {
	return id_ == entity.id_;
}

bool Entity::operator!=(const Entity& entity) const {
	return !(id_ == entity.id_);
}

void Entity::destroy() {
	scene_->entities.remove(*this);
}

void strife::core::to_json(Data& data, const Entity& entity) {
	const Identifier id = entity.id();
	Serialization::Reference(data, id);
}

void strife::core::from_json(const Data& data, Entity& entity) {
	Contexts::Context<map<const Identifier, const Entity>>& context = Serialization::Contexts().at<map<const Identifier, const Entity>>(data);
	const Identifier id = Serialization::Identify(data);
	entity = context.items().at(id);
}