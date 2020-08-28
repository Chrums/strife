#pragma once

#include "btBulletDynamicsCommon.h"
#include "strife/core/component.h"

namespace strife {
    namespace main {

        class ColliderBase : public core::Component {

            using core::Component::Component;

        public:

            const btCollisionShape& collisionShape() const;
            btCollisionShape& collisionShape();

            virtual void initialize();
            virtual void dispose();

        protected:

            btCollisionShape* collisionShape_;

        };

    }
}