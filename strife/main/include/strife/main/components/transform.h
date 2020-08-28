#pragma once

#include "btBulletDynamicsCommon.h"
#include "strife/core/component.h"

namespace strife {
    namespace main {

        class Transform : public core::Component {

            using core::Component::Component;

        public:

            const btTransform& transform() const;
            btTransform& transform();

            void initialize();

            const serialization::Data serialize() const;
            void deserialize(const serialization::Data& data);

        private:

            btTransform transform_;

        };

    }
}