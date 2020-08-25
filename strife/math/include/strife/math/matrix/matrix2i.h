#pragma once

#include "strife/math/matrix/matrix2.h"

namespace strife {
    namespace math {

        class Matrix2i : public Matrix2<Matrix2i, int> {

            using Matrix2<Matrix2i, int>::Matrix2;

        public:

            static Matrix2i Identity;
            
        };

    }
}