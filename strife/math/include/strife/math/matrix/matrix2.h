#pragma once

#include "strife/math/matrix/matrix.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Matrix2 : public Matrix<Derived, T, 2, 2> {

            using Matrix<Derived, T, 2, 2>::Matrix;

        };
        
    }
}