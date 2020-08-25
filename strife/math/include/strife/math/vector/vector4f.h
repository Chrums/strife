#pragma once

#include "strife/math/vector/vector4.h"

namespace strife {
    namespace math {
        
        class Vector4f : public Vector4<Vector4f, float> {

            using Vector4<Vector4f, float>::Vector4;

        public:

            static Vector4f Zero;
            static Vector4f One;
            static Vector4f Left;
            static Vector4f Right;
            static Vector4f Down;
            static Vector4f Up;
            static Vector4f Backward;
            static Vector4f Forward;
            
        };
        
    }
}