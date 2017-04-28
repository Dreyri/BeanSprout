#include "math/vector2.h"
#include "math/matrix4.h"

namespace BS
{
template<typename T>
Vector2<T>::Vector2(const Vector2<T>& other)
{
    mElements[0] = other.mElements[0];
    mElements[1] = other.mElements[1];
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

template<>
float Vector2<int>::getLength() const
{
    float fX = getX();
    float fY = getY();

    float len = std::sqrt(fX*fX + fY*fY);
    return len;
}

template<typename T>
float Vector2<T>::getLength() const
{
    static_assert(std::is_same<float, T>::value || std::is_same<double, T>::value, "getLength() only works on floating point numbers");
    T len = std::sqrt(getX()*getX() + getY()*getY());
    return static_cast<float>(len);
}

template<typename T>
const Vector2<T>& normalize()
{
    static_assert(std::is_same<float, T>::value || std::is_same<double, T>::value, "normalize() only works on floating point numbers");
    //TODO
}

template<>
bool Vector2<float>::operator==(const Vector2<float>& vec2) const
{
    float abs0Diff = std::abs((*this)[0] - vec2[0]);
    float abs1Diff = std::abs((*this)[1] - vec2[1]);

    return (abs0Diff < EPSILON) && (abs1Diff < EPSILON);
}

template<>
bool Vector2<double>::operator==(const Vector2<double>& vec2) const
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
const Vector2<double>& Vector2<double>::operator*=(float scalar)
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
Vector2<T> Vector2<T>::operator+(const Vector2<T>& vec2)
{
    Vector2<T> tmp(*this);
    return tmp.translate(vec2);
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
void swap(Vector2<T> vec1, Vector2<T> vec2)
{
    std::swap(vec1.mElements, vec2.mElements);
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

extern template class Vector2<int>;
extern template class Vector2<float>;
extern template class Vector2<double>;
}
