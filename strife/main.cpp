#include <iostream>
#include <optional>
#include <emscripten.h>
#include "engine.h"
#include "input_system.h"
#include "render_system.h"
#include "action.h"
#include "vector2.h"
#include "input/mouse_input.h"
#include "strife/serialization/data.h"
#include "vector.h"
#include "strife/reflection/type.h"

#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;
using namespace strife::reflection;
using namespace strife::math;
using namespace strife::common;
using namespace strife::serialization;
using namespace strife::core;
using namespace strife::main;

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
        Storage<C>& storage = scene_->components().at<C>();
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

    const Type& type = Type::Of<int>();
    cout << type.name() << endl;

    const Type& inverse = Type::Of(type.name());
    cout << type.name() << endl;

    // Vector<int> v0(2);
    // v0[0] = 1;
    // v0[1] = 1;
    
    // Vector<int> v1(2);
    // v1[0] = 3;
    // v1[1] = 3;

    // cout << v0.distanceSquared(v1) << endl;

    // Data data = v0;
    // cout << data << endl;

    // Vector<int> v2(2);
    // v2 = data.get<Vector<int>>();
    
    Engine& engine = Engine::Instance();

    engine.systems.add<InputSystem>();
    engine.systems.add<RenderSystem>(Vector2(640.0f, 480.0f));
    engine.systems.add<TestSystem>();
    
    string path = "...";
    Scene& scene = engine.scenes.load(path);
    scene.components().add<TestComponent>();
    Entity e0 = scene.entities().add();
    auto& tc0 = e0.components().add<TestComponent>();
    Entity e1 = scene.entities().add();
    auto& tc1 = e1.components().add<TestComponent>();
    Entity e2 = scene.entities().add();
    auto& tc2 = e2.components().add<TestComponent>();
    engine.scenes.swap(path);

    tc0.a = 1;

    tc1.e = e0;
    tc2.e = e0;

    Data data = scene.serialize();
    cout << data << endl << endl;
    scene.deserialize(data);
    cout << scene.serialize() << endl;

    // engine.run();
    
    return 0;
}