#pragma once

#include <iostream>

template <typename T>
struct PhysicsUnit {
    PhysicsUnit() = default;
    
    explicit PhysicsUnit(double v);

    T& operator=(const T& other);

    T& operator+=(const T& other);
    T operator+(const T& other) const;
    T operator-(const T& other) const;
    T operator-() const;

    operator double() const;

    // Comparison operators
    bool operator==(const T& other) const;
    bool operator!=(const T& other) const;
    bool operator<(const T& other) const;
    bool operator<=(const T& other) const;
    bool operator>(const T& other) const;
    bool operator>=(const T& other) const;

    double value_;
};

/* --------------------- Class PhysicsUnit Implementation --------------------- */
template <typename T>
PhysicsUnit<T>::PhysicsUnit(double v) : value_(v) {}

template <typename T>
T& PhysicsUnit<T>::operator=(const T& other) {
    if (this != &other) {
        value_ = other.value_;
    }
    return *this;
}

template <typename T>
T& PhysicsUnit<T>::operator+=(const T& other) {
    value_ += other.value_;
    // return *this;
    return static_cast<T&>(*this);
}

template <typename T>
T PhysicsUnit<T>::operator+(const T& other) const {
    T result(*this);
    // T result(static_cast<const T&>(*this));
    return result += other;
}

template <typename T>
T PhysicsUnit<T>::operator-(const T& other) const {
    T result(*this);
    return result += -(other);
    return result;
}

template <typename T>
T PhysicsUnit<T>::operator-() const {
    return T(-value_);
}

template <typename T>
PhysicsUnit<T>::operator double() const {
    return value_;
}

// Comparison operators
template <typename T>
bool PhysicsUnit<T>::operator==(const T& other) const {
    return value_ == other.value_;
}
template <typename T>
bool PhysicsUnit<T>::operator!=(const T& other) const {
    return !(*this == other);
}
template <typename T>
bool PhysicsUnit<T>::operator<(const T& other) const {
    return value_ < other.value_;
}
template <typename T>
bool PhysicsUnit<T>::operator<=(const T& other) const {
    return value_ <= other.value_;
}
template <typename T>
bool PhysicsUnit<T>::operator>(const T& other) const {
    return value_ > other.value_;
}
template <typename T>
bool PhysicsUnit<T>::operator>=(const T& other) const {
    return value_ >= other.value_;
}