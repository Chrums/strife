#pragma once

#include "strife/math/matrix/matrix.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Matrix3 : public Matrix<Derived, T, 3, 3> {

            using Matrix<Derived, T, 3, 3>::Matrix;

        };
        
    }
}