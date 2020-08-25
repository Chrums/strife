#pragma once

#include "strife/math/matrix/matrix2.h"

namespace strife {
    namespace math {

        class Matrix2f : public Matrix2<Matrix2f, float> {

            using Matrix2<Matrix2f, float>::Matrix2;

        public:

            static Matrix2f Identity;
            
        };

    }
}