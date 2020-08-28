#pragma once

#include "strife/math/vector/vector3.h"

namespace strife {
    namespace math {
        
        class Vector3f : public Vector3Base<Vector3f, float> {

            using Vector3Base<Vector3f, float>::Vector3Base;

        public:

            static Vector3f Zero;
            static Vector3f One;
            static Vector3f Left;
            static Vector3f Right;
            static Vector3f Down;
            static Vector3f Up;
            static Vector3f Backward;
            static Vector3f Forward;
            
        };
        
    }
}