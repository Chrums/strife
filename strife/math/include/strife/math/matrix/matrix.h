#pragma once

#include <vector>
#include "strife/math/base.h"

namespace strife {
    namespace math {

        template <typename Derived, typename T, int Rows, int Columns>
        class Matrix : public Base<Derived, T, Rows, Columns> {

            using Base<Derived, T, Rows, Columns>::Base;

        };

    }
}