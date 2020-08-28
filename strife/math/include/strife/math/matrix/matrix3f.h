#pragma once

#include "strife/math/matrix/matrix3.h"

namespace strife {
    namespace math {

        class Matrix3f : public Matrix3Base<Matrix3f, float> {

            using Matrix3Base<Matrix3f, float>::Matrix3Base;

        public:

            static Matrix3f Identity;
            
        };

    }
}