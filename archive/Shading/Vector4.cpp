#include "Vector4.h"
#include <cmath>
#include <cassert>

Vector4::Vector4()
{
    c[0] = c[1] = c[2] = c[3] = 0;
}

Vector4::Vector4(float c0, float c1, float c2)
{
    c[0] = c0;
    c[1] = c1;
    c[2] = c2;
    c[3] = 1;
}

Vector4::Vector4(float c0, float c1, float c2, float c3)
{
    c[0] = c0;
    c[1] = c1;
    c[2] = c2;
    c[3] = c3;
}

Vector4::Vector4(const Vector4& another)
{
    c[0] = another.c[0];
    c[1] = another.c[1];
    c[2] = another.c[2];
    c[3] = another.c[3];
}

Vector4::Vector4(Vector3& another)
{
    c[0] = another[0];
    c[1] = another[1];
    c[2] = another[2];
    c[3] = 1;
}

void Vector4::setCoordinates(float c0, float c1, float c2, float c3)
{
    c[0] = c0;
    c[1] = c1;
    c[2] = c2;
    c[3] = c3;
}

float* Vector4::getCoordinates(void)
{
    return c;
}

void Vector4::setCoordinate(int dim, float value)
{
    assert(dim>=0 && dim<=3);
    c[dim] = value;
}


const float Vector4::getCoordinate(int dim)
{
    assert(dim>=0 && dim<=3);
    return c[dim];
}

float& Vector4::operator [] (int dim)
{
    assert(dim>=0 && dim<=3);
    float &k = c[dim];
    return k;
}

void Vector4::add(const Vector4& another)
{
    c[0] += another.c[0];
    c[1] += another.c[1];
    c[2] += another.c[2];
    c[3] += another.c[3];
}

void Vector4::sub(const Vector4& another)
{
    c[0] -= another.c[0];
    c[1] -= another.c[1];
    c[2] -= another.c[2];
    c[3] -= another.c[3];
}

Vector4 Vector4::operator + (const Vector4& another)
{
    Vector4 new_vec(*this);
    new_vec.add(another);
    return new_vec;
}

Vector4 Vector4::operator - (const Vector4& another)
{
    Vector4 new_vec(*this);
    new_vec.sub(another);
    return new_vec;
}

void Vector4::toDehomogenized(void)
{
    assert(c[3]!=0);
    for(int i=0; i<3; ++i)
        c[i] /= c[3];
    c[3] = 1;
}

Vector4 Vector4::getDehomogenized(void)
{
    Vector4 new_vec(*this);
    new_vec.toDehomogenized();
    return new_vec;
}

std::ostream& operator << (std::ostream& out, const Vector4& vec)
{
    out<<"("<<vec.c[0]<<","<<vec.c[1]<<","<<vec.c[2]<<","<<vec.c[3]<<")";
    return out;
}
