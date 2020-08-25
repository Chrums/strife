#pragma once

#include "strife/math/matrix/matrix4.h"

namespace strife {
    namespace math {

        class Matrix4i : public Matrix4<Matrix4i, int> {

            using Matrix4<Matrix4i, int>::Matrix4;

        public:

            static Matrix4i Identity;
            
        };

    }
}