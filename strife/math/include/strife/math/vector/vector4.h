#pragma once

#include "strife/math/vector/vector.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Vector4 : public Vector<Derived, T, 4> {

            using Vector<Derived, T, 4>::Vector;

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

            const T& z() const {
                return this->operator[](2);
            }

            T& z() {
                return this->operator[](2);
            }

            const T& w() const {
                return this->operator[](3);
            }

            T& w() {
                return this->operator[](4);
            }

            Vector4(const T& x, const T& y, const T& z, const T& w)
                : Vector4({ x, y, z, w }) {}

        };

    }
}