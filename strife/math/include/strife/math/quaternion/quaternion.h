#include "strife/math/base.h"

namespace strife {
    namespace math {

        template <typename Derived, typename T>
        class QuaternionBase : public Base<Derived, T, 4, 1> {
            
            using Base<Derived, T, 4, 1>::Base;

        public:



        }

        template <typename T>
        class Quaternion : public QuaternionBase<Quaternion<T>, T> {

            using QuaternionBase<Quaternion<T>, T>::QuaternionBase;

        }

    }
}