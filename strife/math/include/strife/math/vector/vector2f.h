#pragma once

#include "strife/math/vector/vector2.h"

namespace strife {
    namespace math {
        
        class Vector2f : public Vector2Base<Vector2f, float> {

            using Vector2Base<Vector2f, float>::Vector2Base;

        public:

            static Vector2f Zero;
            static Vector2f One;
            static Vector2f Left;
            static Vector2f Right;
            static Vector2f Down;
            static Vector2f Up;
            
        };
        
    }
}