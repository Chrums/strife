#pragma once

#include "strife/math/matrix/matrix.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Matrix4 : public Matrix<Derived, T, 4, 4> {

            using Matrix<Derived, T, 4, 4>::Matrix;

        };
        
    }
}