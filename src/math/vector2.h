#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <iostream>

namespace BS
{
template<class T>
class Vector2
{
private:
    T mElements[2];

    constexpr static float EPSILON = 0.0001f;

public:
    Vector2() : Vector2(0, 0) {}
    Vector2(T x, T y)
        : mElements { x, y } {}
    Vector2(T elements[2])
        : mElements { elements[0], elements[1] } {}
    Vector2(const Vector2<T>& other);

    ~Vector2() {}

    Vector2<T>& operator=(Vector2<T> other);

    const T& getX() const { return mElements[0]; }
    const T& getY() const { return mElements[1]; }

    const T& getWidth() const { return getX(); }
    const T& getHeight() const { return getY(); }

    void setX(const T& x) { mElements[0] = x; }
    void setY(const T& y) { mElements[1] = y; }

    void setWidth(const T& width) { setX(width); }
    void setHeight(const T& height) { setY(height); }

    const Vector2<T>& translate(const Vector2<T>& vec);

    float getLength() const;
    float distanceTo(const Vector2<T>& v2) const;

    const Vector2<T>& normalize();

    bool operator==(const Vector2<T>& vec2) const;
    bool operator!=(const Vector2<T>& vec2) const;
    bool operator<(const Vector2<T>& vec2) const;
    bool operator>(const Vector2<T>& vec2) const;
    bool operator<=(const Vector2<T>& vec2) const;
    bool operator>=(const Vector2<T>& vec2) const;

    const Vector2<T>& operator+=(const Vector2<T>& vec2);
    Vector2<T> operator+(const Vector2<T>& vec2) const;
    const Vector2<T>& operator -=(const Vector2<T>& vec2);
    Vector2<T> operator-(const Vector2<T>& vec2) const;
    const Vector2<T>& operator*=(float scalar);

    const T& operator[](size_t i) const;
    T& operator[](size_t i);

    template<typename U>
    friend void swap(Vector2<U> &vec1, Vector2<U> &vec2);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& v);

template<typename T>
Vector2<T> operator*(float scalar, const Vector2<T>& v);
template<typename T>
Vector2<T> operator*(const Vector2<T>& v, float scalar);

typedef Vector2<double> Vector2d;
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

template<typename T>
Vector2<T>::Vector2(const Vector2<T>& other)
    : Vector2<T>(other.getX(), other.getY())
{
}

template<typename T>
void swap(Vector2<T> &vec1, Vector2<T> &vec2)
{
    std::swap(vec1.mElements, vec2.mElements);
}


template<typename T>
Vector2<T>& Vector2<T>::operator=(Vector2<T> other)
{
    swap(*this, other);
    return *this;
}

template<typename T>
const Vector2<T>& Vector2<T>::translate(const Vector2<T>& vec)
{
    setX(getX()+vec.getX());
    setY(getY()+vec.getY());

    return *this;
}

template<typename T>
float Vector2<T>::getLength() const
{
    T len = std::sqrt(getX()*getX() + getY()*getY());
    return static_cast<float>(len);
}

template<>
inline float Vector2<int>::getLength() const
{
    float fX = getX();
    float fY = getY();

    float len = std::sqrt(fX*fX + fY*fY);
    return len;
}

template<typename T>
float Vector2<T>::distanceTo(const Vector2<T>& v2) const
{
    Vector2<T> tmp = (*this) - v2;
    return tmp.getLength();
}

template<typename T>
const Vector2<T>& Vector2<T>::normalize()
{
    static_assert(std::is_same<T, double>::value || std::is_same<T, float>::value, "only floating point vectors can be normalized");
    float len = getLength();
    (*this)[0] /= len;
    (*this)[1] /= len;

    return *this;
}

template<>
const Vector2<int>& Vector2<int>::normalize() = delete;

template<>
inline bool Vector2<float>::operator==(const Vector2<float>& vec2) const
{
    float abs0Diff = std::abs((*this)[0] - vec2[0]);
    float abs1Diff = std::abs((*this)[1] - vec2[1]);

    return (abs0Diff < EPSILON) && (abs1Diff < EPSILON);
}

template<>
inline bool Vector2<double>::operator==(const Vector2<double>& vec2) const
{
    double abs0Diff = std::abs((*this)[0] - vec2[0]);
    double abs1Diff = std::abs((*this)[1] - vec2[1]);

    return (abs0Diff < static_cast<const double>(EPSILON)) && (abs1Diff < static_cast<const double>(EPSILON));
}

template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& vec2) const
{
    return (*this)[0] == vec2[0] && (*this)[1] == vec2[1];
}

template<typename T>
bool Vector2<T>::operator!=(const Vector2<T>& vec2) const
{
    return !(*this == vec2);
}

template<typename T>
bool Vector2<T>::operator<(const Vector2<T>& vec2) const
{
    return getLength() < vec2.getLength();
}

template<typename T>
bool Vector2<T>::operator>(const Vector2<T>& vec2) const
{
    return getLength() > vec2.getLength();
}

template<typename T>
bool Vector2<T>::operator<=(const Vector2<T>& vec2) const
{
    return  (*this) < vec2 || (*this) == vec2;
}

template<typename T>
bool Vector2<T>::operator>=(const Vector2<T>& vec2) const
{
    return (*this) > vec2 || (*this) == vec2;
}

template<typename T>
const Vector2<T>& Vector2<T>::operator*=(float scalar)
{
    (*this)[0] *= scalar;
    (*this)[1] *= scalar;

    return *this;
}

template<>
inline const Vector2<double>& Vector2<double>::operator*=(float scalar)
{
    double scalarD = static_cast<double>(scalar);

    (*this)[0] *= scalarD;
    (*this)[1] *= scalarD;

    return *this;
}

template<typename T>
const Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& vec2)
{
    return this->translate(vec2);
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& vec2) const
{
    Vector2<T> tmp(*this);
    return tmp.translate(vec2);
}

template<typename T>
const Vector2<T>& Vector2<T>::operator -=(const Vector2<T>& vec2)
{
    (*this)[0] -= vec2[0];
    (*this)[1] -= vec2[1];
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& vec2) const
{
    Vector2<T> tmp = *this;
    tmp -= vec2;
    return tmp;
}

template<typename T>
const T& Vector2<T>::operator[](size_t i) const
{
    return mElements[i];
}

template<typename T>
T& Vector2<T>::operator[](size_t i)
{
    return mElements[i];
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& v)
{
    os << "x: " << v.getX() << ", y: " << v.getY();
    return os;
}

template <typename T>
Vector2<T> operator*(float scalar, const Vector2<T>& v)
{
    return Vector2<T>(v[0] * scalar, v[1] * scalar);
}

template<typename T>
Vector2<T> operator*(const Vector2<T>& v, float scalar)
{
    return scalar * v;
}
}

#endif /* VECTOR2_H */
