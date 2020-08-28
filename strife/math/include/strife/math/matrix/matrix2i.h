#pragma once

#include "strife/math/matrix/matrix2.h"

namespace strife {
    namespace math {

        class Matrix2i : public Matrix2Base<Matrix2i, int> {

            using Matrix2Base<Matrix2i, int>::Matrix2Base;

        public:

            static Matrix2i Identity;
            
        };

    }
}