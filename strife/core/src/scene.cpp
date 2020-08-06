#include "scene.h"

#include <iostream>

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

const Data Scene::Entities::serialize() const {
    Data data;

    for (auto& entity : entities_) {
        string entityId = boost::uuids::to_string(entity.id);
        data.push_back(entityId);
    }

    return data;
}

const Data Scene::Entities::deserialize(const Data data) {
    Data context;

    // for (auto& identifier : data) {
    //     Entity entity = add();
    //     context[entity.id] = identifier.get<Identifier>();
    // }

    return context;
}

Scene::Components::Components(Scene& scene)
    : scene_(scene) {}
    
Scene::Components::~Components() {
    for (auto& [type, storage] : components_) {
        delete storage;
    }
}

Component& Scene::Components::add(const type_index type, const Entity entity) {
    return components_.at(type)->add(entity);
}

void Scene::Components::remove(const Entity entity) {
    for (auto& [type, storage] : components_) {
        storage->remove(entity);
    }
}

void Scene::Components::remove(const type_index type, const Entity entity) {
    return components_.at(type)->remove(entity);
}

Component& Scene::Components::at(const type_index type, const Entity entity) const {
    return components_.at(type)->at(entity);
}

Component* const Scene::Components::get(const type_index type, const Entity entity) const {
    return components_.at(type)->get(entity);
}

map<const type_index, IStorage* const>::const_iterator Scene::Components::begin() const {
    return components_.begin();
}

map<const type_index, IStorage* const>::const_iterator Scene::Components::end() const {
    return components_.end();
}

const Data Scene::Components::serialize() const {
    Data data;

    for (auto& [type, storage] : components_) {
        int status;
        char* typeName = abi::__cxa_demangle(type.name(), 0, 0, &status);

        Data storageData;
        Storage<Component>& componentStorage = *static_cast<Storage<Component>*>(storage);
        for (auto [entity, component] : componentStorage) {
            string entityId = boost::uuids::to_string(entity.id);
            Data componentData = component.serialize();
            storageData[entityId] = componentData;
        }

        data[typeName] = storageData;
    }

    return data;
}

            // void deserialize(const common::Data data) {
            //     for (auto& [identifier, componentData] : data.items()) {
            //         std::cout << identifier << std::endl;
            //     }
            // }

void Scene::Components::deserialize(const Data data) {
    for (auto& [typeName, type] : types_) {
        IStorage* storage = components_.at(type);
        Data storageData = data[typeName];
        // storage->deserialize(storageData);
    }
}

Scene::Scene()
    : entities(*this)
    , components(*this) {}
    
const Data Scene::serialize() const {

    // Data entitiesData;
    // for (auto& entity : entities) {
    //     std::string entityIdentifier = boost::uuids::to_string(entity.id);
    //     entitiesData.push_back(entityIdentifier);
    // }

    // Data componentsData;
    // for (auto& [type, storage] : components) {
    //     int status;
    //     char* typeName = abi::__cxa_demangle(type.name(), 0, 0, &status);
    //     Data storageData = storage->serialize();
    //     data[typeName] = storageData;
    // }

    Data data;
    
    data["entities"] = entities.serialize();
    data["components"] = components.serialize();

    return data;
}

void Scene::deserialize(const Data data) {

    // Data entitiesData = data["entities"];
    

    // Data componentsData = data["components"];

    // entities.deserialize(entitiesData);
    // components.deserialize(componentsData);

}