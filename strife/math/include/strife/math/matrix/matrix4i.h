#pragma once

#include "strife/math/matrix/matrix4.h"

namespace strife {
    namespace math {

        class Matrix4i : public Matrix4Base<Matrix4i, int> {

            using Matrix4Base<Matrix4i, int>::Matrix4Base;

        public:

            static Matrix4i Identity;
            
        };

    }
}