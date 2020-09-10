#include "strife/core/scene.h"

#include <iostream>

using namespace std;
using namespace strife;

#pragma region Entities

Scene::Entities::Entities(Scene& scene)
    : scene_(scene) {}

const Entity Scene::Entities::add() {
    const Entity entity(scene_);
    identifierEntityMap_.insert({entity.identifier(), entity});
    return entity;
}

void Scene::Entities::remove(const Entity& entity) {
    identifierEntityMap_.erase(entity.identifier());
}

#pragma endregion

#pragma region Components

Scene::Components::Components(Scene& scene)
    : scene_(scene) {}

map<const Type, Component* const> Scene::Components::all(const Entity& entity) {
    return entityComponentsMap_[entity];
}

Component& Scene::Components::add(const Type& type, const Entity& entity) {
    IStorage& storage = *typeStorageMap_.at(type);
    Component& component = storage.add(entity);

    map<const Type, Component* const>& entityComponents = entityComponentsMap_[entity];
    entityComponents.insert({type, &component});

    return component;
}

void Scene::Components::remove(const Type& type, const Entity& entity) {
    IStorage& storage = *typeStorageMap_.at(type);

    map<const Type, Component* const>& entityComponents = entityComponentsMap_[entity];
    entityComponents.erase(type);

    storage.remove(entity);
}

Component* const Scene::Components::find(const Type& type, const Entity& entity) {
    map<const Type, IStorage* const>::iterator iterator = typeStorageMap_.find(type);
    if (iterator == typeStorageMap_.end()) {
        return nullptr;
    }

    IStorage& storage = *iterator->second;
    return storage.find(entity);
}

#pragma endregion

const Scene::Entities& Scene::entities() const {
    return entities_;
}

Scene::Entities& Scene::entities() {
    return entities_;
}

const Scene::Components& Scene::components() const {
    return components_;
}

Scene::Components& Scene::components() {
    return components_;
}

Scene::Scene()
    : entities_(*this)
    , components_(*this) {}