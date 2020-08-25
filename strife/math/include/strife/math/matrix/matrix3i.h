#pragma once

#include "strife/math/matrix/matrix3.h"

namespace strife {
    namespace math {

        class Matrix3i : public Matrix3<Matrix3i, int> {

            using Matrix3<Matrix3i, int>::Matrix3;

        public:

            static Matrix3i Identity;
            
        };

    }
}