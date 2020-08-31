#pragma once

#include "btBulletDynamicsCommon.h"
#include "strife/core/system.h"

namespace strife {
    namespace main {

        class PhysicsSystem : public core::System<PhysicsSystem> {

        public:

            btDiscreteDynamicsWorld& world();

            PhysicsSystem();
            ~PhysicsSystem() = default;

            void initialize();
            void onUpdate(const events::UpdateEvent& updateEvent);

        private:

            btDefaultCollisionConfiguration defaultCollisionConfiguration_;
            btCollisionDispatcher collisionDispatcher_;
            btDbvtBroadphase dbvtBroadphase_;
            btSequentialImpulseConstraintSolver sequentialImpulseConstraintSolver_;
            btDiscreteDynamicsWorld discreteDynamicsWorld_;

        };

    }
}