#pragma once

#include "strife/math/matrix/matrix3.h"

namespace strife {
    namespace math {

        class Matrix3i : public Matrix3Base<Matrix3i, int> {

            using Matrix3Base<Matrix3i, int>::Matrix3Base;

        public:

            static Matrix3i Identity;
            
        };

    }
}