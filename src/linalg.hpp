#pragma once

#include <array>


template <class T, int n>
class vec
{
private:
    std::array<T, n> data_;

public:
    vec(std::array<T, n> data);
    vec<T, n> operator+(const vec<T, n> other) const;
    vec<T, n> operator+=(const vec<T, n> other);

    vec<T, n> operator-(const vec<T, n> other) const;
    vec<T, n> operator-=(const vec<T, n> other);

    vec<T, n> operator*(const T other) const;
    vec<T, n> operator*=(const T other);

    vec<T, n> operator/(const T other) const;
    vec<T, n> operator/=(const T other);

    // dot product
    T operator*(const vec<T, n> other) const;

};

template <class T, int n>
vec<T, n>::vec(std::array<T, n> data) {
    data_ = data;
}

template <class T, int n>
vec<T, n> vec<T, n>::operator+(const vec<T, n> other) const {
    std::array<T, n> data;

    for (std::size_t i = 0; i < n; i++){
        data[i] = data_[i] + other.data_[i];
    }
    return data;

}

template <class T, int n>
vec<T, n> vec<T, n>::operator+=(const vec<T, n> other) {
    for (std::size_t i = 0; i < n; i++){
        data_[i] += other.data_[i];
    }
    return &this;
}

template <class T, int n>
vec<T, n> vec<T, n>::operator-(const vec<T, n> other) const {
    std::array<T, n> data;

    for (std::size_t i = 0; i < n; i++){
        data[i] = data_[i] - other.data_[i];
    }
    return data;

}

template <class T, int n>
vec<T, n> vec<T, n>::operator-=(const vec<T, n> other) {
    for (std::size_t i = 0; i < n; i++){
        data_[i] -= other.data_[i];
    }
    return &this;
}

template <class T, int n>
vec<T, n> vec<T, n>::operator*(const T other) const {
    std::array<T, n> data;

    for (std::size_t i = 0; i < n; i++){
        data[i] = data_[i] * other;
    }
    return data;

}

template <class T, int n>
vec<T, n> vec<T, n>::operator*=(const T other) {
    for (std::size_t i = 0; i < n; i++){
        data_[i] *= other;
    }
    return &this;
}

template <class T, int n>
vec<T, n> vec<T, n>::operator/(const T other) const {
    std::array<T, n> data;

    for (std::size_t i = 0; i < n; i++){
        data[i] = data_[i] / other;
    }
    return data;

}

template <class T, int n>
vec<T, n> vec<T, n>::operator/=(const T other) {
    for (std::size_t i = 0; i < n; i++){
        data_[i] /= other;
    }
    return &this;
}

template<class T, int n>
T vec<T, n>::operator*(const vec<T, n> other) const{
    T total = 0;
    for (std::size_t i = 0; i < n; i++) {
        total += data_[i] * other.data_[i];
    }
    return total;
    
}

using vec2 = vec<float, 2>;
