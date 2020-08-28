#pragma once

#include "strife/math/matrix/matrix4.h"

namespace strife {
    namespace math {

        class Matrix4f : public Matrix4Base<Matrix4f, float> {

            using Matrix4Base<Matrix4f, float>::Matrix4Base;

        public:

            static Matrix4f Identity;
            
        };

    }
}