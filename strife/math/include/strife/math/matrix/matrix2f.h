#pragma once

#include "strife/math/matrix/matrix2.h"

namespace strife {
    namespace math {

        class Matrix2f : public Matrix2Base<Matrix2f, float> {

            using Matrix2Base<Matrix2f, float>::Matrix2Base;

        public:

            static Matrix2f Identity;
            
        };

    }
}