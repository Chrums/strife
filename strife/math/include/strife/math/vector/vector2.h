#pragma once

#include "strife/math/vector/vector.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Vector2Base : public VectorBase<Derived, T, 2> {

            using VectorBase<Derived, T, 2>::VectorBase;

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

            Vector2Base(const T& x, const T& y)
                : Vector2Base({ x, y }) {}

        };

        template <typename T>
        class Vector2 : public Vector2Base<Vector2<T>, T> {

            using Vector2Base<Vector2<T>, T>::Vector2Base;

        };
        
    }
}