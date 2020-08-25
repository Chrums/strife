#pragma once

#include "strife/math/vector/vector3.h"

namespace strife {
    namespace math {

        class Vector3i : public Vector3<Vector3i, int> {

            using Vector3<Vector3i, int>::Vector3;

        public:

            static Vector3i Zero;
            static Vector3i One;
            static Vector3i Left;
            static Vector3i Right;
            static Vector3i Down;
            static Vector3i Up;
            static Vector3i Backward;
            static Vector3i Forward;
            
        };

    }
}