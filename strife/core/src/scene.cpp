#include "scene.h"

#include <iostream>
#include "serialization/serialization.h"

using namespace std;
using namespace strife::common;
using namespace strife::core;

Scene::Entities::Entities(Scene& scene)
    : scene_(scene) {}

const Entity Scene::Entities::add() {
    const Entity& entity = *entities_.emplace(scene_).first;
    return entity;
}

void Scene::Entities::remove(const Entity entity) {
    scene_.components.remove(entity);
    entities_.erase(entity);
}

set<Entity>::const_iterator Scene::Entities::begin() const {
    return entities_.begin();
}

set<Entity>::const_iterator Scene::Entities::end() const {
    return entities_.end();
}

Scene::Components::Components(Scene& scene)
    : scene_(scene) {}
    
Scene::Components::~Components() {
    for (auto& [type, storage] : storages_) {
        delete storage;
    }
}

const type_index Scene::Components::type(string typeName) const {
    return types_.at(typeName);
}

IStorage& Scene::Components::at(const type_index type) const {
    return *storages_.at(type);
}

IStorage* const Scene::Components::find(const type_index type) const {
    auto iterator = storages_.find(type);
    return iterator != storages_.end()
        ? iterator->second
        : nullptr;
}

Component& Scene::Components::add(const type_index type, const Entity entity) {
    return storages_.at(type)->add(entity);
}

void Scene::Components::remove(const Entity entity) {
    for (auto& [type, storage] : storages_) {
        storage->remove(entity);
    }
}

void Scene::Components::remove(const type_index type, const Entity entity) {
    return storages_.at(type)->remove(entity);
}

Component& Scene::Components::at(const type_index type, const Entity entity) const {
    return storages_.at(type)->at(entity);
}

Component* const Scene::Components::find(const type_index type, const Entity entity) const {
    return storages_.at(type)->find(entity);
}

map<const type_index, IStorage* const>::const_iterator Scene::Components::begin() const {
    return storages_.begin();
}

map<const type_index, IStorage* const>::const_iterator Scene::Components::end() const {
    return storages_.end();
}

Scene::Scene()
    : entities(*this)
    , components(*this) {}
    
const Data Scene::serialize() const {
    Data data;

    Data entitiesData;
    for (auto& entity : entities) {
        string entityId = boost::uuids::to_string(entity.id());
        entitiesData.push_back(entityId);
    }

    Data componentsData;
    for (auto& [type, storage] : components) {
        
        // TODO: Extract this to a reflection library?
        int status;
        char* typeName = abi::__cxa_demangle(type.name(), 0, 0, &status);

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

    return data;
}

void Scene::deserialize(const Data& data) {

    Contexts::Context<map<const Identifier, const Entity>>& context = Serialization::Contexts().instantiate<map<const Identifier, const Entity>>();

    Data entitiesData = data["entities"];
    Data componentsData = data["components"];

    for (auto& entityIdData : entitiesData) {
        const string entityIdString = entityIdData.get<string>();
        const Identifier id = strife::common::ToIdentifier(entityIdString);
        const Entity entity = entities.add();
        context.items().insert({id, entity});
    }

    for (auto& [typeName, storageData] : componentsData.items()) {
        const std::type_index type = components.type(typeName);
        IStorage& storage = components.at(type);
        for (auto& [entityIdString, componentData] : storageData.items()) {
            const Identifier id = strife::common::ToIdentifier(entityIdString);
            const Entity entity = context.items().at(id);
            for (auto& [keyString, valueData] : componentData.items()) {
                if (Serialization::IsReference(valueData)) {
                    context.apply(valueData);
                }
            }

            Component& component = storage.add(entity);
            component.deserialize(componentData);
        }
    }

    context.dispose();

}