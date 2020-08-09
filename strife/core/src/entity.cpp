#include "entity.h"

#include "component.h"
#include "scene.h"
#include "storage.h"
#include "strife/serialization/contexts.h"

#define TYPE "__TYPE__"
#define ENTITY "__ENTITY__"
#define IDENTIFIER "__IDENTIFIER__"

using namespace std;
using namespace strife::reflection;
using namespace strife::common;
using namespace strife::serialization;
using namespace strife::core;

Entity::Components::Components(Entity& entity)
    : entity_(entity) {}

Entity::Components::Components(const Entity::Components& components)
    : entity_(components.entity_) {}
    
Component& Entity::Components::add(const Type& type) {
	return entity_.scene_->components().add(type, entity_);
}

void Entity::Components::remove(const Type& type) {
	entity_.scene_->components().remove(type, entity_);
}

Component& Entity::Components::at(const Type& type) const {
	return entity_.scene_->components().at(type, entity_);
}

Component* const Entity::Components::find(const Type& type) const {
	return entity_.scene_->components().find(type, entity_);
}

bool Entity::Is(const Data& data) {
	return data.is_object() && data[TYPE].is_string() && data[TYPE].get<string>() == ENTITY;
}

const Identifier Entity::Resolve(const Data& data) {
	string id = data[IDENTIFIER].get<string>();
	return strife::common::ToIdentifier(id);
}

Scene& Entity::scene() const {
	return *scene_;
}

Entity::Components& Entity::components() {
	return components_;
}

Entity::Entity()
	: Unique(Unique::Nil())
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
	scene_ = entity.scene_;
	return *this;
}

bool Entity::operator==(const Entity& entity) const {
	return id_ == entity.id_;
}

bool Entity::operator!=(const Entity& entity) const {
	return !(id_ == entity.id_);
}

void Entity::apply(Data& data) const {
	data[TYPE] = ENTITY;
	data[IDENTIFIER] = strife::common::ToString(id_);
}

void Entity::dispose() {
	scene_->entities().remove(*this);
}

void strife::core::to_json(Data& data, const Entity& entity) {
	IContext::Apply(data);
	entity.apply(data);
}

void strife::core::from_json(const Data& data, Entity& entity) {
	if (Contexts::Exists(data)) {
		Context<ContextType>& context = Contexts::Resolve<ContextType>(data);
		const Identifier& id = Entity::Resolve(data);
		ContextType::iterator iterator = context.items().find(id);
		if (iterator != context.items().end()) {
			entity = iterator->second;
		}
	}
}