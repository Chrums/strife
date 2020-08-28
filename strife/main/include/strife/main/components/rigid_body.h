#pragma once

#include "btBulletDynamicsCommon.h"
#include "strife/core/component.h"
#include "strife/main/components/transform.h"
#include "strife/main/components/collider_base.h"

namespace strife {
    namespace main {

        class RigidBody : public core::Component {

            using core::Component::Component;

        public:

            const btRigidBody& rigidBody() const;
            btRigidBody& rigidBody();

            const float& mass() const;
            void mass(const float& value);

            void initialize();
            void dispose();

        private:

            float mass_;
            btVector3 intertia_;
            
            btRigidBody* rigidBody_;
            btDefaultMotionState* motionState_;
            Transform* transform_;
            ColliderBase* colliderBase_;

        };

    }
}