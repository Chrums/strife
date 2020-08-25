#pragma once

#include "strife/math/vector/vector.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Vector2 : public Vector<Derived, T, 2> {

            using Vector<Derived, T, 2>::Vector;

        public:

            const T& x() const {
                return this->operator[](0);
            }

            T& x() {
                return this->operator[](0);
            }

            const T& y() const {
                return this->operator[](1);
            }

            T& y() {
                return this->operator[](1);
            }

            Vector2(const T& x, const T& y)
                : Vector2({ x, y }) {}

        };
        
    }
}