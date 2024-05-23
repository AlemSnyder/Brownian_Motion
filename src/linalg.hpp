#pragma once

#include <array>
#include <cmath>
#include <utility>

namespace linalg {

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
    T operator[](std::size_t i) const;

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

template<class T, int n>
T vec<T, n>::operator[](std::size_t i) const {
    // assert(i < n);
    return data_[i];
}

template <class T, int n>
T norm_squared(vec<T, n> arg){
    return arg * arg;
}

template <class T, int n>
inline T norm(vec<T, n> arg){
    return std::sqrt(norm_squared(arg));
}

template<class T, int n>
inline vec<T, n> normalize(const vec<T, n> arg) {
    return arg / norm(arg);
}

using vec2 = vec<float, 2>;

inline vec2 perpendicular(const vec2 arg){
    return vec2({arg[1], -arg[0]});
}

template<class T, int n>
inline std::pair<vec<T, n>, vec<T, n>> decomp(vec<T, n> arg, vec<T, n> p1, vec<T, n> p2){
    return {p1 * (p1 * arg), p2 * (p2 * arg)};
}

}
