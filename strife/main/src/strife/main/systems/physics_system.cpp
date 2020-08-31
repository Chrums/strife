#include "strife/core/engine.h"
#include "strife/main/systems/physics_system.h"

#include <iostream>

using namespace std;
using namespace strife::core;
using namespace strife::events;
using namespace strife::main;

btDiscreteDynamicsWorld& PhysicsSystem::world() {
    return discreteDynamicsWorld_;
}

PhysicsSystem::PhysicsSystem()
    : defaultCollisionConfiguration_()
    , collisionDispatcher_(&defaultCollisionConfiguration_)
    , dbvtBroadphase_()
    , sequentialImpulseConstraintSolver_()
    , discreteDynamicsWorld_(&collisionDispatcher_, &dbvtBroadphase_, &sequentialImpulseConstraintSolver_, &defaultCollisionConfiguration_) {

    btVector3 gravity(0.0f, -9.81f, 0.0f);
    discreteDynamicsWorld_.setGravity(gravity);

    // btCollisionShape* collisionShape = new btSphereShape(1.0f);

    // btTransform transform;
    // transform.setIdentity();

    // float mass = 1.0f;
    // bool isDynamic = mass != 0.0f;

    // btVector3 localInertia(0.0f, 0.0f, 0.0f);

    // if (isDynamic) {
    //     collisionShape->calculateLocalInertia(mass, localInertia);
    // }

    // transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));

    // btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    // btRigidBody::btRigidBodyConstructionInfo rigidBodyConstructionInfo(mass, motionState, collisionShape, localInertia);
    // btRigidBody* rigidBody = new btRigidBody(rigidBodyConstructionInfo);

    // discreteDynamicsWorld_.addRigidBody(rigidBody);
}

void PhysicsSystem::onUpdate(const UpdateEvent& updateEvent) {
    cout << "Physics Update" << endl;
    Engine& engine = Engine::Instance();
    float deltaTime = engine.time.delta();
    discreteDynamicsWorld_.stepSimulation(deltaTime, 1.0f / deltaTime);
    int collisionObjectCount = discreteDynamicsWorld_.getNumCollisionObjects();
    btCollisionObjectArray& collisionObjects = discreteDynamicsWorld_.getCollisionObjectArray();
    for (int index = 0; index < collisionObjectCount; ++index) {
        btCollisionObject& collisionObject = *collisionObjects.at(index);
        cout << collisionObject.getWorldTransform().getOrigin().getX() << ", " << collisionObject.getWorldTransform().getOrigin().getY() << ", " << collisionObject.getWorldTransform().getOrigin().getZ() << endl;
    }
}