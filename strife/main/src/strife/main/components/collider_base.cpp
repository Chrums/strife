#include "strife/main/components/collider_base.h"

using namespace strife::main;

const btCollisionShape& ColliderBase::collisionShape() const {
    return *collisionShape_;
}

btCollisionShape& ColliderBase::collisionShape() {
    return *collisionShape_;
}

void ColliderBase::initialize() {
    if (collisionShape_ == nullptr) {
        collisionShape_ = new btSphereShape(1.0f);
    }
}

void ColliderBase::dispose() {
    delete collisionShape_;
}