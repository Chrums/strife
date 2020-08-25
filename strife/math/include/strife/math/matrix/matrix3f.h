#pragma once

#include "strife/math/matrix/matrix3.h"

namespace strife {
    namespace math {

        class Matrix3f : public Matrix3<Matrix3f, float> {

            using Matrix3<Matrix3f, float>::Matrix3;

        public:

            static Matrix3f Identity;
            
        };

    }
}