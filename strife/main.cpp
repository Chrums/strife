#include <iostream>
#include <optional>
#include <emscripten.h>
#include "strife/core/engine.h"
#include "input_system.h"
#include "render_system.h"
#include "strife/functional/action.h"
#include "strife/math/vector2.h"
#include "strife/input/mouse_input.h"
#include "strife/serialization/data.h"
#include "strife/math/vector.h"
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
        cout << inputSystem_.inputManager.mouse().position().x << endl;
    }
    
};

int main(int argc, char* argv[]) {
    
    Engine& engine = Engine::Instance();

    engine.components.add<TestComponent>();

    engine.systems.add<InputSystem>();
    engine.systems.add<RenderSystem>(Vector2(640.0f, 480.0f));
    engine.systems.add<TestSystem>();
    
    string path = "...";
    Scene& s0 = engine.scenes.load(path);
    Entity e0 = s0.entities().add();
    TestComponent& tc0 = e0.components().add<TestComponent>();
    Entity e1 = s0.entities().add();
    TestComponent& tc1 = e1.components().add<TestComponent>();
    Entity e2 = s0.entities().add();
    TestComponent& tc2 = e2.components().add<TestComponent>();
    engine.scenes.swap(path);

    tc0.a = 1;

    tc1.e = e0;
    tc2.e = e0;

    Data d0 = s0.serialize();
    s0.deserialize(d0);

    // engine.run();
    
    return 0;
}