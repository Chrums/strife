#include <iostream>
#include <emscripten.h>
#include "engine.h"
#include "input_system.h"
#include "render_system.h"
#include "action.h"
#include "vector2.h"
#include "input/mouse_input.h"
#include "serialization/data.h"
#include "vector.h"

#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;
using namespace strife::common;
using namespace strife::core;
using namespace strife::math;
using namespace strife::main;

class TestComponent : public Component {
    
using Component::Component;

public:

    int a;
    int b;
    int c;

    const Data serialize() const {
        Data data;

        data["a"] = a;
        data["b"] = b;
        data["c"] = c;

        return data;
    }

    void deserialize(const Data data) {
        a = data["a"].get<int>();
        b = data["b"].get<int>();
        c = data["c"].get<int>();
    }

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

public:

    TestSystem() 
        : ComponentSystem()
        , inputSystem_(Engine::Instance().systems.at<InputSystem>()) {}

    ~TestSystem() = default;

private:
    
    InputSystem& inputSystem_;

    void onUpdate(TestComponent& testComponent) {
        
    }
    
};

int main(int argc, char* argv[]) {

    Vector<int> v0(2);
    v0.values[0] = 1;
    v0.values[1] = 1;
    
    Vector<int> v1(2);
    v1.values[0] = 3;
    v1.values[1] = 3;

    cout << v0.distanceSquared(v1) << endl;
    
    // Engine& engine = Engine::Instance();

    // engine.systems.add<InputSystem>();
    // engine.systems.add<RenderSystem>(Vector2(640.0f, 480.0f));
    // engine.systems.add<TestSystem>();
    
    // string path = "...";
    // Scene& scene = engine.scenes.load(path);
    // scene.components.add<TestComponent>();
    // Entity entity0 = scene.entities.add();
    // entity0.components.add<TestComponent>();
    // Entity entity1 = scene.entities.add();
    // entity1.components.add<TestComponent>();
    // Entity entity2 = scene.entities.add();
    // entity2.components.add<TestComponent>();
    // engine.scenes.swap(path);

    // Data data = scene.serialize();
    // cout << data << endl;
    // scene.deserialize(data);

    // engine.run();
    
    return 0;
}