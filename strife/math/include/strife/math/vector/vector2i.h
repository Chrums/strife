#pragma once

#include "strife/math/vector/vector2.h"

namespace strife {
    namespace math {

        class Vector2i : public Vector2Base<Vector2i, int> {

            using Vector2Base<Vector2i, int>::Vector2Base;

        public:

            static Vector2i Zero;
            static Vector2i One;
            static Vector2i Left;
            static Vector2i Right;
            static Vector2i Down;
            static Vector2i Up;
            
        };

    }
}