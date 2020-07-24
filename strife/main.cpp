#include <iostream>
#include <emscripten.h>
#include "engine.h"
#include "input_system.h"

#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


using namespace std;
using namespace strife::common;
using namespace strife::core;
using namespace strife::main;

class TestComponent : public Component {
    
using Component::Component;

public:

    int a;
    int b;
    int c;

};

template <class C>
class ComponentSystem : public System {
    
using System::System;

public:

    ComponentSystem()
        : System() {};
    ~ComponentSystem() = default;
    
protected:

    void onUpdate(const UpdateEvent& updateEvent) {
        Storage<C>& storage = scene_->components.at<C>();
        for (auto [entity, component] : storage) {
            onUpdate(component);
        }
    }

    virtual void onUpdate(C& component) = 0;
    
};

class TestSystem : public ComponentSystem<TestComponent> {

using ComponentSystem<TestComponent>::ComponentSystem;
    
private:
    
    void onUpdate(TestComponent& testComponent) {
        cout << Engine::Instance().time.total << endl;
        cout << testComponent.id << endl;
    }
    
};

int main(int argc, char* argv[]) {
    
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* surface = NULL;
    
    Engine& engine = Engine::Instance();
    engine.systems.add<TestSystem>();
    engine.systems.add<InputSystem>();
    string path = "...";
    Scene& scene = engine.scenes.load(path);
    scene.components.add<TestComponent>();
    Entity entity0 = scene.entities.add();
    entity0.components.add<TestComponent>();
    Entity entity1 = scene.entities.add();
    entity1.components.add<TestComponent>();
    Entity entity2 = scene.entities.add();
    entity2.components.add<TestComponent>();
    engine.scenes.swap(path);
    
    engine.run();
    
    return 0;
}