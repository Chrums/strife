#pragma once

#include <algorithm>
#include <vector>
#include <math.h>

#include <iostream>

namespace strife {
    namespace math {

        template <typename T>
        class Vector {

        public:

            const int size() const {
                return values.size();
            }

            const float length() const {
                const float valueSquared = lengthSquared();
                return sqrt(valueSquared);
            }

            const float lengthSquared() const {
                float lengthSquared = 0.0f;

                const int size = values.size();
                for (int index = 0; index < size; ++index) {
                    lengthSquared += values[index] * values[index];
                }

                return lengthSquared;
            }

            const float distance(const Vector& vector) const {
                const float valueSquared = distanceSquared(vector);
                return sqrt(valueSquared);
            }

            const float distanceSquared(const Vector& vector) const {
                Vector difference = Vector(vector).subtract(*this);
                return difference.lengthSquared();
            }

            Vector add(const Vector& vector) {
                const int size = std::min(values.size(), vector.values.size());
                for (int index = 0; index < size; ++index) {
                    values[index] += vector.values[index];
                }

                return *this;
            }

            Vector add(const T value) {
                const int size = values.size();
                for (int index = 0; index < size; ++index) {
                    values[index] += value;
                }

                return *this;
            }

            Vector subtract(const Vector& vector) {
                const int size = std::min(values.size(), vector.values.size());
                for (int index = 0; index < size; ++index) {
                    values[index] -= vector.values[index];
                }

                return *this;
            }

            Vector subtract(const T value) {
                const int size = values.size();
                for (int index = 0; index < size; ++index) {
                    values[index] -= value;
                }

                return *this;
            }

            Vector multiply(const Vector& vector) {
                const int size = std::min(values.size(), vector.values.size());
                for (int index = 0; index < size; ++index) {
                    values[index] *= vector.values[index];
                }

                return *this;
            }

            Vector multiply(const T value) {
                const int size = values.size();
                for (int index = 0; index < size; ++index) {
                    values[index] *= value;
                }

                return *this;
            }

            Vector divide(const Vector& vector) {
                const int size = std::min(values.size(), vector.values.size());
                for (int index = 0; index < size; ++index) {
                    values[index] /= vector.values[index];
                }

                return *this;
            }

            Vector divide(const T value) {
                const int size = values.size();
                for (int index = 0; index < size; ++index) {
                    values[index] /= value;
                }

                return *this;
            }

        // protected:

            std::vector<T> values;

            Vector(const int size)
                : values(size) {}
            Vector(const Vector& vector)
                : values(vector.size()) {
                const int size = values.size();
                for (int index = 0; index < size; ++index) {
                    values[index] = vector.values[index];
                }
            }

            ~Vector() = default;

        };

    }
}