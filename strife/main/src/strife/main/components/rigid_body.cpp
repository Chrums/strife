#include "strife/main/components/rigid_body.h"
#include "strife/main/systems/physics_system.h"
#include "strife/core/engine.h"

#include <iostream>

using namespace std;
using namespace strife::core;
using namespace strife::main;

const btRigidBody& RigidBody::rigidBody() const {
    return *rigidBody_;
}

btRigidBody& RigidBody::rigidBody() {
    return *rigidBody_;
}

const float& RigidBody::mass() const {
    return mass_;
}

void RigidBody::mass(const float& value) {
    mass_ = value;
    btVector3 inertia = rigidBody_->getLocalInertia();
    rigidBody_->setMassProps(mass_, inertia);
}

void RigidBody::initialize() {
    // transform_ = entity().components().find<Transform>();

    // colliderBase_ = entity().components().find<ColliderBase>();
    // colliderBase_->collisionShape().calculateLocalInertia(mass_, intertia_);

    // motionState_ = new btDefaultMotionState(transform_->transform());

    // btRigidBody::btRigidBodyConstructionInfo rigidBodyConstructionInfo(mass_, motionState_, &colliderBase_->collisionShape(), intertia_);
    // rigidBody_ = new btRigidBody(rigidBodyConstructionInfo);

    // Engine& engine = Engine::Instance();
    // PhysicsSystem& physicsSystem = engine.systems.at<PhysicsSystem>();
    // physicsSystem.world().addRigidBody(rigidBody_);

    transform_ = entity().components().find<Transform>();
    colliderBase_ = entity().components().find<ColliderBase>();

    btCollisionShape* collisionShape = &colliderBase_->collisionShape();

    // btTransform transform;
    // transform.setIdentity();
    btTransform& transform = transform_->transform();

    float mass = 1.0f;
    bool isDynamic = mass != 0.0f;

    btVector3 localInertia(0.0f, 0.0f, 0.0f);

    if (isDynamic) {
        collisionShape->calculateLocalInertia(mass, localInertia);
    }

    transform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));

    btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyConstructionInfo(mass, motionState, collisionShape, localInertia);
    // btRigidBody* rigidBody = new btRigidBody(rigidBodyConstructionInfo);
    rigidBody_ = new btRigidBody(rigidBodyConstructionInfo);

    // discreteDynamicsWorld_.addRigidBody(rigidBody);
    Engine::Instance().systems.at<PhysicsSystem>().world().addRigidBody(rigidBody_);
}

void RigidBody::dispose() {
    delete rigidBody_;
    delete motionState_;
}