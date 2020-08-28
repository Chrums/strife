#pragma once

#include "strife/main/components/collider_base.h"

namespace strife {
    namespace main {

        class SphereCollider : ColliderBase {

            using ColliderBase::ColliderBase;

        public:

            const btSphereShape& sphereShape() const;
            btSphereShape& sphereShape();

            const float& radius() const;
            void radius(const float& value);

            void initialize();

        private:

            float radius_;

        };

    }
}