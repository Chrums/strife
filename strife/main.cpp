#include <iostream>
#include <optional>
#include <emscripten.h>
#include "strife/core/engine.h"
#include "strife/main/components/collider_base.h"
#include "strife/main/components/rigid_body.h"
#include "strife/main/components/transform.h"
#include "strife/main/systems/input_system.h"
#include "strife/main/systems/render_system.h"
#include "strife/main/systems/physics_system.h"
#include "strife/functional/action.h"
#include "strife/input/mouse_input.h"
#include "strife/serialization/data.h"
#include "strife/math/math.h"
#include "strife/reflection/type.h"

#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;
using namespace strife::reflection;
using namespace strife::math;
using namespace strife::input;
using namespace strife::serialization;
using namespace strife::core;
using namespace strife::main;
using namespace strife::events;

class TestComponent : public Component {
    
using Component::Component;

public:

    int a;
    int b;
    int c;

    Entity e;

    const Data serialize() const {
        Data data;

        data["a"] = a;
        data["b"] = b;
        data["c"] = c;

        data["e"] = e;

        return data;
    }

    void deserialize(const Data& data) {
        a = data["a"].get<int>();
        b = data["b"].get<int>();
        c = data["c"].get<int>();

        e = data["e"].get<Entity>();
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
        Storage<C>& storage = scene()->components().template at<C>();
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
        cout << inputSystem_.inputManager.mouse().position().x() << endl;
    }
    
};

int main(int argc, char* argv[]) {
    
    Engine& engine = Engine::Instance();

    // engine.components.add<TestComponent>();
    engine.components.add<ColliderBase>();
    engine.components.add<RigidBody>();
    engine.components.add<Transform>();

    // engine.systems.add<TestSystem>();
    engine.systems.add<InputSystem>();
    engine.systems.add<RenderSystem>(Vector2i(640, 480));
    engine.systems.add<PhysicsSystem>();
    
    string path = "...";

    Scene& s0 = engine.scenes.load(path);

    Entity e0 = s0.entities().add();

    Transform& e0_transform = e0.components().add<Transform>();
    ColliderBase& e0_colliderBase = e0.components().add<ColliderBase>();
    RigidBody& e0_rigidBody = e0.components().add<RigidBody>();

    // TestComponent& tc0 = e0.components().add<TestComponent>();
    // Entity e1 = s0.entities().add();
    // TestComponent& tc1 = e1.components().add<TestComponent>();
    // Entity e2 = s0.entities().add();
    // TestComponent& tc2 = e2.components().add<TestComponent>();
    
    engine.scenes.swap(path);

    // tc0.a = 1;

    // tc1.e = e0;
    // tc2.e = e0;

    // Data d0 = s0.serialize();
    // cout << d0 << endl;
    // s0.deserialize(d0);
    
    cout << s0.serialize() << endl;

    engine.run();
    
    return 0;
}