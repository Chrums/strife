#include "strife/core/entity.h"

#include "strife/core/component.h"
#include "strife/core/scene.h"
#include "strife/core/storage.h"
#include "strife/serialization/context.h"
#include "strife/serialization/contexts.h"

#define IDENTIFIER_INDEX "__IDENTIFIER__"

using namespace std;
using namespace strife::core;
using namespace strife::reflection;
using namespace strife::serialization;
using namespace strife::unique;

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

const Scene& Entity::scene() const {
	return *scene_;
}

Scene& Entity::scene() {
	return *scene_;
}

const Entity::Components& Entity::components() const {
	return components_;
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
	id(entity.id());
	scene_ = entity.scene_;
	return *this;
}

bool Entity::operator==(const Entity& entity) const {
	return id() == entity.id();
}

bool Entity::operator!=(const Entity& entity) const {
	return !(id() == entity.id());
}

void Entity::dispose() {
	scene_->entities().remove(*this);
}

const Data Entity::serialize() const {
	Data data;
	Contexts::Require(data); // TODO: Make Contexts::Require and Contexts::Resolve take a std::string index?
	data[IDENTIFIER_INDEX] = id();
	return data;
}

void Entity::deserialize(const Data& data) {
	Context<ContextType>& context = Contexts::Resolve<ContextType>(data);

	const Identifier& entityId = data[IDENTIFIER_INDEX].get<Identifier>();
	ContextType::iterator iterator = context.value().find(entityId);
	if (iterator != context.value().end()) {
		*this = iterator->second;
	} else {
		context.value().insert({entityId, *this});
	}
}

void strife::core::to_json(Data& data, const Entity& entity) {
	data = entity.serialize();
}

void strife::core::from_json(const Data& data, Entity& entity) {
	entity.deserialize(data);
}