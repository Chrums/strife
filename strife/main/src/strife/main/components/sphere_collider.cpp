#include "strife/main/components/sphere_collider.h"

using namespace std;
using namespace strife::main;

const btSphereShape& SphereCollider::sphereShape() const {
    return *static_cast<const btSphereShape* const>(collisionShape_);
}

btSphereShape& SphereCollider::sphereShape() {
    return *static_cast<btSphereShape*>(collisionShape_);
}

const float& SphereCollider::radius() const {
    return radius_;
}

void SphereCollider::radius(const float& value) {
    sphereShape().setUnscaledRadius(radius_);
}

void SphereCollider::initialize() {
    collisionShape_ = new btSphereShape(radius_);
}