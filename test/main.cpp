#include <iostream>
#include <emscripten.h>
#include "strife/common.h"
#include "strife/core.h"

using namespace std;
using namespace strife;

class ICollider : public Component {
    using Component::Component;
public:
    virtual void test() {}
};

class BoxCollider : public ICollider {
    using ICollider::ICollider;
public:
    virtual void test() {
        cout << "Box" << endl;
    }
};

class SphereCollider : public ICollider {
    using ICollider::ICollider;
public:
    virtual void test() {
        cout << "Sphere" << endl;
    }
};

class UpdateMessage : public Message {

    using Message::Message;

};

class Test0 {

public:

    Test0(Dispatcher& dispatcher, string name) : name_(name) {
        dispatcher.subscribe<UpdateMessage>(this, &Test0::onUpdate);
    }

private:

    string name_;

    void onUpdate(const UpdateMessage& updateMessage) {
        cout << name_ << ": " << Type::Of(*this).name() << endl;
    }

};

class Test1 {

public:

    Test1(Dispatcher& dispatcher, string name) : name_(name) {
        dispatcher.subscribe<UpdateMessage>(this, &Test1::onUpdate);
    }

private:

    string name_;

    void onUpdate(const UpdateMessage& updateMessage) {
        cout << name_ << ": " << Type::Of(*this).name() << endl;
    }

};

class TestComponent : public Component {

    using Component::Component;

public:

    void initialize(Dispatcher& dispatcher) {
        dispatcher.subscribe<UpdateMessage>(this, &TestComponent::onUpdate);
    }

private:

    void onUpdate(const UpdateMessage& updateMessage) {
        cout << "Update!" << endl;
    }

};

int main(int argc, char* argv[]) {
    
    Dispatcher dispatcher;

    Test0 t00(dispatcher, "t00");
    Test0 t01(dispatcher, "t01");
    Test1 t10(dispatcher, "t10");

    Scene scene;
    scene.components().add<TestComponent>();
    scene.components().add<BoxCollider>();
    scene.components().add<SphereCollider>();

    Entity e0 = scene.entities().add();
    TestComponent& tc0 = e0.components().add<TestComponent>();
    tc0.initialize(dispatcher);

    BoxCollider& bc0 = e0.components().add<BoxCollider>();

    Entity e1 = scene.entities().add();
    TestComponent& tc1 = e1.components().add<TestComponent>();
    tc1.initialize(dispatcher);

    SphereCollider& sc1 = e1.components().add<SphereCollider>();

    ICollider* const collider = e1.components().find<ICollider>();
    if (collider != nullptr) {
        collider->test();
    }

    dispatcher.emit(UpdateMessage());
    
    return 0;
}