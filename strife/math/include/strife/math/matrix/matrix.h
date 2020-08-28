#pragma once

#include <vector>
#include "strife/math/base.h"

namespace strife {
    namespace math {

        template <typename Derived, typename T, int Rows, int Columns>
        class MatrixBase : public Base<Derived, T, Rows, Columns> {

            using Base<Derived, T, Rows, Columns>::Base;

        };

        template <typename T, int Rows, int Columns>
        class Matrix : public MatrixBase<Matrix<T, Rows, Columns>, T, Rows, Columns> {

            using MatrixBase<Matrix<T, Rows, Columns>, T, Rows, Columns>::MatrixBase;

        };

    }
}