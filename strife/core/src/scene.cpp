#include "scene.h"

using namespace strife::core;
using namespace std;

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

Scene::Components::Components(Scene& scene)
    : scene_(scene) {}
    
Scene::Components::~Components() {
    for (auto [type, storage] : components_) {
        delete storage;
    }
}

Component& Scene::Components::add(const type_index type, const Entity entity) {
    return components_.at(type)->add(entity);
}

void Scene::Components::remove(const Entity entity) {
    // TODO: Implement this...
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

Scene::Scene()
    : entities(*this)
    , components(*this) {}