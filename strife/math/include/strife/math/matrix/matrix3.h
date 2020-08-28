#pragma once

#include "strife/math/matrix/matrix.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Matrix3Base : public MatrixBase<Derived, T, 3, 3> {

            using MatrixBase<Derived, T, 3, 3>::MatrixBase;

        };
        
        template <typename T>
        class Matrix3 : Matrix3Base<Matrix3<T>, T> {

            using Matrix3Base<Matrix3<T>, T>::Matrix3Base;

        };
        
    }
}