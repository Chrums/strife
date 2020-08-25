#pragma once

#include "strife/math/vector/vector4.h"

namespace strife {
    namespace math {

        class Vector4i : public Vector4<Vector4i, int> {

            using Vector4<Vector4i, int>::Vector4;

        public:

            static Vector4i Zero;
            static Vector4i One;
            static Vector4i Left;
            static Vector4i Right;
            static Vector4i Down;
            static Vector4i Up;
            static Vector4i Backward;
            static Vector4i Forward;
            
        };

    }
}