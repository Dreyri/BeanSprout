#ifndef MATRIX4_H
#define MATRIX4_H

namespace BS
{
template<typename T>
class Matrix4
{
private:
    T mElements[16];

public:
    Matrix4()
        : mElements{ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 } {}
    Matrix4(const T& t00, const T& t01, const T& t02, const T& t03,
            const T& t10, const T& t11, const T& t12, const T& t13,
            const T& t20, const T& t21, const T& t22, const T& t23,
            const T& t30, const T& t31, const T& t32, const T& t33)
        : mElements { t00,t01,t02,t03, t10,t11,t12,t13, t20,t21,t22,t23, t30,t31,t32,t33 }
    {}

    const T& operator[](int i) const
    { return mElements[i]; }


public:
    static Matrix4<T> identity()
    {
        return Matrix4();
    }

    static Matrix4<T> ortho(const T& left, const T& right, const T& bottom, const T& top, const T& zNear, const T& zFar)
    {
        return Matrix4(2 / (right - left),0,0,0, 0,2/(top-bottom),0,0, 0,0,-2/(zFar-zNear),0,
                       -(right+left)/(right-left),-(top+bottom)/(top-bottom),-(zFar+zNear)/(zFar-zNear), 1);
    }

};
}

#endif // MATRIX4_H
