#include "strife/core/scene.h"

#include "strife/core/engine.h"
#include "strife/serialization/context.h"
#include "strife/serialization/contexts.h"

#define ENTITIES_INDEX "__ENTITIES__"
#define COMPONENTS_INDEX "__COMPONENTS__"

using namespace std;
using namespace strife::core;
using namespace strife::reflection;
using namespace strife::serialization;
using namespace strife::unique;

Scene::Entities::Entities(Scene& scene)
    : scene_(scene) {}

Entity& Scene::Entities::add() {
    Entity entity(scene_);
    return entities_.insert({entity.id(), entity}).first->second;
}

void Scene::Entities::remove(const Entity& entity) {
    scene_.components().remove(entity);
    entities_.erase(entity.id());
}

map<const Identifier, Entity>::const_iterator Scene::Entities::begin() const {
    return entities_.begin();
}

map<const Identifier, Entity>::const_iterator Scene::Entities::end() const {
    return entities_.end();
}

const Data Scene::Entities::serialize() const {
    Data data;

    for (auto& [entityId, entity] : entities_) {
        const Data entityData = entity.serialize();
        data += entityData;
    }
    
    return data;
}

void Scene::Entities::deserialize(const Data& data) {
    for (const Data& entityData : data) {
        Entity& entity = add();
        entity.deserialize(entityData);
    }
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

const Data Scene::Components::serialize() const {
    Data data;

    for (auto& [type, storage] : storages_) {
        string typeName = type.name();
        Data storageData = storage->serialize();
        data[typeName] = storageData;
    }
    
    return data;
}

void Scene::Components::deserialize(const Data& data) {
    for (auto& [typeName, storageData] : data.items()) {
        const Type& type = Type::Of(typeName);
        IStorage& storage = *storages_.at(type);
        storage.deserialize(storageData);
    }
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

void Scene::dispose() {
    Engine& engine = Engine::Instance();
    // engine.scenes.unload(*this); TODO: Implement this...
}

const Data Scene::serialize() const {
    Data data;

    data[ENTITIES_INDEX] = entities_.serialize();
    data[COMPONENTS_INDEX] = components_.serialize();

    return data;
}

void Scene::deserialize(const Data& data) {
    Context& context = Contexts::Instantiate(data);

    const Data& entitiesData = context.data[ENTITIES_INDEX];
    entities_.deserialize(entitiesData);

    const Data& componentsData = context.data[COMPONENTS_INDEX];
    components_.deserialize(componentsData);

    context.dispose();
}

void strife::core::to_json(Data& data, const Scene& scene) {
    data = scene.serialize();
}

void strife::core::from_json(const Data& data, Scene& scene) {
    scene.deserialize(data);
}