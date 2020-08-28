#pragma once

#include <strife/math/base.h>

namespace strife {
    namespace math {

        template <typename Derived, typename T, int Size>
        class VectorBase : public Base<Derived, T, Size, 1> {

            using Base<Derived, T, Size, 1>::Base;

        public:

            const T& operator()(const int& index) const {
                return Base<Derived, T, Size, 1>::operator()(index, 0);
            }

            T& operator()(const int& index) {
                return Base<Derived, T, Size, 1>::operator()(index, 0);
            }

            template <typename OtherDerived>
            const float dot(const OtherDerived& otherDerived) const {
                return this->data().dot(otherDerived.data());
            }
            
        };

        template <typename T, int Size>
        class Vector : public VectorBase<Vector<T, Size>, T, Size> {

            using VectorBase<Vector<T, Size>, T, Size>::VectorBase;

        };

    }
}

// namespace nlohmann {

//     template <class T>
//     struct adl_serializer<strife::math::Vector<T>> {

//         static void to_json(nlohmann::json& json, const strife::math::Vector<T>& vector) {
//             for (int index = 0; index < vector.size(); ++index) {
//                 json[index] = vector[index];
//             }
//         }

//         static void from_json(const nlohmann::json& json, strife::math::Vector<T>& vector) {
//             for (auto& [indexSizetring, value] : json.items()) {
//                 int index = std::stoi(indexSizetring);
//                 vector[index] = value.get<T>();
//             }
//         }

//     };
    
// }