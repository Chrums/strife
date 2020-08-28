#pragma once

#include "strife/math/matrix/matrix.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Matrix4Base : public MatrixBase<Derived, T, 4, 4> {

            using MatrixBase<Derived, T, 4, 4>::MatrixBase;

        };
        
        template <typename T>
        class Matrix4 : Matrix4Base<Matrix4<T>, T> {

            using Matrix4Base<Matrix4<T>, T>::Matrix4Base;

        };
        
    }
}