#include "strife/main/components/transform.h"

using namespace strife::main;
using namespace strife::serialization;

const btTransform& Transform::transform() const {
    return transform_;
}

btTransform& Transform::transform() {
    return transform_;
}

void Transform::initialize() {
    btVector3 origin(0.0f, 0.0f, 0.0f);
    transform_.setOrigin(origin);
}

const Data Transform::serialize() const {
    Data data;

    btScalar values[16];
    transform_.getOpenGLMatrix(values);
    
    for (int index = 0; index < 16; ++index) {
        data.push_back(values[index]);
    }

    return data;
}

void Transform::deserialize(const Data& data) {

}