#include "scene.h"

#include "strife/serialization/context.h"
#include "strife/serialization/contexts.h"

using namespace std;
using namespace strife::reflection;
using namespace strife::serialization;
using namespace strife::common;
using namespace strife::core;

Scene::Entities::Entities(Scene& scene)
    : scene_(scene) {}

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
    : scene_(scene) {}
    
Scene::Components::~Components() {
    for (auto& [type, storage] : storages_) {
        delete storage;
    }
}

IStorage& Scene::Components::at(const Type& type) const {
    return *storages_.at(type);
}

IStorage* const Scene::Components::find(const Type& type) const {
    map<const Type, IStorage* const>::const_iterator iterator = storages_.find(type);
    return iterator != storages_.end()
        ? iterator->second
        : nullptr;
}

Component& Scene::Components::add(const Type& type, const Entity& entity) {
    return storages_.at(type)->add(entity);
}

void Scene::Components::remove(const Entity& entity) {
    for (auto& [type, storage] : storages_) {
        storage->remove(entity);
    }
}

void Scene::Components::remove(const Type& type, const Entity& entity) {
    return storages_.at(type)->remove(entity);
}

Component& Scene::Components::at(const Type& type, const Entity& entity) const {
    return storages_.at(type)->at(entity);
}

Component* const Scene::Components::find(const Type& type, const Entity& entity) const {
    return storages_.at(type)->find(entity);
}

map<const Type, IStorage* const>::const_iterator Scene::Components::begin() const {
    return storages_.begin();
}

map<const Type, IStorage* const>::const_iterator Scene::Components::end() const {
    return storages_.end();
}

Scene::Entities& Scene::entities() {
    return entities_;
}

Scene::Components& Scene::components() {
    return components_;
}

Scene::Scene()
    : entities_(*this)
    , components_(*this) {}
    
const Data Scene::serialize() const {
    Data data;

    Data entitiesData;
    for (auto& entity : entities_) {
        string entityId = boost::uuids::to_string(entity.id());
        entitiesData.push_back(entityId);
    }

    Data componentsData;
    for (auto& [type, storage] : components_) {
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

    return data;
}

void Scene::deserialize(const Data& data) {

    Context<ContextType>& context = Contexts::Instantiate<ContextType>();

    Data entitiesData = data["entities"];
    Data componentsData = data["components"];

    for (auto& entityIdData : entitiesData) {
        const string entityIdString = entityIdData.get<string>();
        const Identifier id = strife::common::ToIdentifier(entityIdString);
        const Entity entity = entities_.add();
        context.items().insert({id, entity});
    }

    for (auto& [typeName, storageData] : componentsData.items()) {
        const Type& type = Type::Of(typeName);
        IStorage& storage = components_.at(type);
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