#include "scene.h"

#include "engine.h"
#include "strife/serialization/context.h"
#include "strife/serialization/contexts.h"

#include <iostream>

using namespace std;
using namespace strife::reflection;
using namespace strife::serialization;
using namespace strife::common;
using namespace strife::core;

Scene::Entities::Entities(Scene& scene)
    : scene_(scene) {}

Scene::Entities& Scene::Entities::operator=(const Scene::Entities& entities) {

    return *this;
}

const Entity Scene::Entities::add() {
    const Entity& entity = *entities_.emplace(scene_).first;
    return entity;
}

void Scene::Entities::remove(const Entity entity) {
    scene_.components().remove(entity);
    entities_.erase(entity);
}

set<Entity>::const_iterator Scene::Entities::begin() const {
    return entities_.begin();
}

set<Entity>::const_iterator Scene::Entities::end() const {
    return entities_.end();
}

Scene::Components::Components(Scene& scene)
    : scene_(scene) {
    Engine& engine = Engine::Instance();
    for (auto& [type, dummy] : engine.components) {
        IStorage* const storage = dummy->copy();
        storages_.insert({type, storage});
    }
}
    
Scene::Components::~Components() {
    for (auto& [type, storage] : storages_) {
        delete storage;
    }
}

Scene::Components& Scene::Components::operator=(const Scene::Components& components) {
    
    return *this;
}

IStorage& Scene::Components::at(const Type& type) const {
    return *storages_.at(type);
}

Component& Scene::Components::add(const Type& type, const Entity& entity) {
    IStorage& storage = at(type);
    Component& component = storage.add(entity);
    return component;
}

void Scene::Components::remove(const Entity& entity) {
    for (auto& [type, storage] : storages_) {
        storage->remove(entity);
    }
}

void Scene::Components::remove(const Type& type, const Entity& entity) {
    IStorage& storage = at(type);
    storage.remove(entity);
}

Component& Scene::Components::at(const Type& type, const Entity& entity) const {
    IStorage& storage = at(type);
    Component& component = storage.at(entity);
    return component;
}

Component* const Scene::Components::find(const Type& type, const Entity& entity) const {
    IStorage& storage = at(type);
    Component* const component = storage.find(entity);
    return component;
}

map<const Type, IStorage* const>::const_iterator Scene::Components::begin() const {
    return storages_.begin();
}

map<const Type, IStorage* const>::const_iterator Scene::Components::end() const {
    return storages_.end();
}

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

Scene& Scene::operator=(const Scene& scene) {
    entities_ = scene.entities_;
    components_ = scene.components_;
    return *this;
}

void strife::core::to_json(Data& data, const Scene& scene) {
    Data entitiesData;
    for (auto& entity : scene.entities()) {
        string entityId = boost::uuids::to_string(entity.id());
        entitiesData.push_back(entityId);
    }

    Data componentsData;
    for (auto& [type, storage] : scene.components()) {
        string typeName = type.name();

        Data storageData;
        Storage<Component>& componentStorage = *static_cast<Storage<Component>*>(storage);
        for (auto& [entity, component] : componentStorage) {
            string entityId = boost::uuids::to_string(entity.id());
            Data componentData = component.serialize();
            storageData[entityId] = componentData;
        }

        componentsData[typeName] = storageData;
    }

    data["entities"] = entitiesData;
    data["components"] = componentsData;
}

void strife::core::from_json(const Data& data, Scene& scene) {
    Context<ContextType>& context = Contexts::Instantiate<ContextType>();

    Data entitiesData = data["entities"];
    Data componentsData = data["components"];

    for (auto& entityIdData : entitiesData) {
        const string entityIdString = entityIdData.get<string>();
        const Identifier id = strife::common::ToIdentifier(entityIdString);
        const Entity entity = scene.entities().add();
        context.items().insert({id, entity});
    }

    for (auto& [typeName, storageData] : componentsData.items()) {
        const Type& type = Type::Of(typeName);
        IStorage& storage = scene.components().at(type);
        for (auto& [entityIdString, componentData] : storageData.items()) {
            const Identifier id = strife::common::ToIdentifier(entityIdString);
            const Entity entity = context.items().at(id);
            for (auto& [keyString, valueData] : componentData.items()) {
                context.apply(valueData);
            }

            Component& component = storage.add(entity);
            component.deserialize(componentData);
        }
    }

    context.dispose();
}