#pragma once

#include "strife/math/vector/vector.h"

namespace strife {
    namespace math {
        
        template <typename Derived, typename T>
        class Vector3Base : public VectorBase<Derived, T, 3> {

            using VectorBase<Derived, T, 3>::VectorBase;

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

            Vector3Base(const T& x, const T& y, const T& z)
                : Vector3Base({ x, y, z }) {}

            template <typename OtherDerived>
            Derived cross(const OtherDerived& other) {
                Derived result;
                result.data() = this->data().cross(other.data());
                return result;
            }

        };

        template <typename T>
        class Vector3 : public Vector3Base<Vector3<T>, T> {

            using Vector3Base<Vector3<T>, T>::Vector3Base;

        };

    }
}