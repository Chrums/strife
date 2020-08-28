#pragma once

#include "strife/math/matrix/matrix.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Matrix2Base : public MatrixBase<Derived, T, 2, 2> {

            using MatrixBase<Derived, T, 2, 2>::MatrixBase;

        };
        
        template <typename T>
        class Matrix2 : Matrix2Base<Matrix2<T>, T> {

            using Matrix2Base<Matrix2<T>, T>::Matrix2Base;

        };

    }
}