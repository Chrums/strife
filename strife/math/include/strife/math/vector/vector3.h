#pragma once

#include "strife/math/vector/vector.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Vector3 : public Vector<Derived, T, 3> {

            using Vector<Derived, T, 3>::Vector;

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

            Vector3(const T& x, const T& y, const T& z)
                : Vector3({ x, y, z }) {}

            template <typename OtherDerived>
            Derived cross(const OtherDerived& other) {
                Derived result;
                result.data() = this->data().cross(other.data());
                return result;
            }

        };

    }
}