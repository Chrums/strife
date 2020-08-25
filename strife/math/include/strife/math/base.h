#pragma once

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>
#include <Eigen/Dense>

namespace strife {
    namespace math {

        template <typename Derived, typename T, int Rows, int Columns>
        class Base {

        public:

            const int& size() const {
                return data_.rows() * data_.columns();
            }

            const int& rows() const {
                return data_.rows();
            }

            const int& columns() const {
                return data_.columns();
            }

            Base() = default;

            Base(const Base& base) {
                data_ = base.data_;
            }

            Base(std::initializer_list<T> values) {
                int size = std::min((int)values.size(), Rows * Columns);
                int index = 0;
                for (const T& value : values) {
                    this->operator[](index) = value;
                    if (++index > size) {
                        return;
                    }
                }
            }

            ~Base() = default;

            friend std::ostream& operator<<(std::ostream& os, const Base& base)
            {
                return os << base.data_;
            }

            friend std::istream& operator<<(const std::istream& is, Base& base)
            {
                return base.data_ << is;
            }

            const T& operator()(const int& row, const int& column) const {
                return data_(row, column);
            }

            T& operator()(const int& row, const int& column) {
                return data_(row, column);
            }

            const T& operator[](const int& index) const {
                int row = index / Columns;
                int column = index % Columns;
                return data_(row, column);
            }

            T& operator[](const int& index) {
                int row = index / Columns;
                int column = index % Columns;
                return data_(row, column);
            }

            Derived operator+(const T& value) {
                Derived result;
                result.data_ = this->data_ + value;
                return result;
            }

            Derived& operator+=(const T& value) {
                data_ += value;
                return derived();
            }

            Derived operator-(const T& value) {
                Derived result;
                result.data_ = this->data_ - value;
                return result;
            }

            Derived& operator-=(const T& value) {
                data_ -= value;
                return derived();
            }

            Derived operator*(const T& value) {
                Derived result;
                result.data_ = this->data_ * value;
                return result;
            }

            Derived& operator*=(const T& value) {
                data_ *= value;
                return derived();
            }

            Derived operator/(const T& value) {
                Derived result;
                result.data_ = this->data_ / value;
                return result;
            }

            Derived& operator/=(const T& value) {
                data_ /= value;
                return derived();
            }

            template <typename OtherDerived>
            Derived operator+(const OtherDerived& other) {
                Derived result;
                result.data_ = this->data_ + other.data_;
                return result;
            }

            template <typename OtherDerived>
            Derived& operator+=(const OtherDerived& other) {
                const Base& base = (const Base&)other;
                data_ += base.data_;
                return derived();
            }

            template <typename OtherDerived>
            Derived operator-(const OtherDerived& other) {
                Derived result;
                result.data_ = this->data_ - other.data_;
                return result;
            }

            template <typename OtherDerived>
            Derived& operator-=(const OtherDerived& other) {
                const Base& base = (const Base&)other;
                data_ -= base.data_;
                return derived();
            }

            template <typename OtherDerived>
            Derived operator*(const OtherDerived& other) {
                Derived result;
                result.data_ = this->data_ * other.data_;
                return result;
            }

            template <typename OtherDerived>
            Derived& operator*=(const OtherDerived& other) {
                const Base& base = (const Base&)other;
                data_ *= base.data_;
                return derived();
            }

            template <typename OtherDerived>
            Derived operator/(const OtherDerived& other) {
                Derived result;
                result.data_ = this->data_ / other.data_;
                return result;
            }

            template <typename OtherDerived>
            Derived& operator/=(const OtherDerived& other) {
                const Base& base = (const Base&)other;
                data_ /= base.data_;
                return derived();
            }

            template <typename OtherDerived>
            Derived& add(const OtherDerived& other) {
                return this->operator+=(other);
            }

            template <typename OtherDerived>
            Derived& subtract(const OtherDerived& other) {
                return this->operator-=(other);
            }

            template <typename OtherDerived>
            Derived& multiply(const OtherDerived& other) {
                return this->operator*=(other);
            }

            template <typename OtherDerived>
            Derived& divide(const OtherDerived& other) {
                return this->operator/=(other);
            }

            T sum() const {
                return data_.sum();
            }

            T product() const {
                return data_.prod();
            }

            T mean() const {
                return data_.mean();
            }

            T trace() const {
                return data_.trace();
            }

        protected:

            const Eigen::Matrix<T, Rows, Columns>& data() const {
                return data_;
            }

            Eigen::Matrix<T, Rows, Columns>& data() {
                return data_;
            }

            const Derived& derived() const {
                return *static_cast<const Derived*>(this);
            }

            Derived& derived() {
                return *static_cast<Derived*>(this);
            }

        private:

            Eigen::Matrix<T, Rows, Columns> data_;

        };

    }
}