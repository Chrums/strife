#pragma once

#include "strife/math/matrix/matrix4.h"

namespace strife {
    namespace math {

        class Matrix4f : public Matrix4<Matrix4f, float> {

            using Matrix4<Matrix4f, float>::Matrix4;

        public:

            static Matrix4f Identity;
            
        };

    }
}