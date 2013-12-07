#include "Vector3.h"
#include <cmath>
#include <cassert>

Vector3::Vector3()
{
    //c[0] = c[1] = c[2] = 0;
}

Vector3::Vector3(double c0, double c1, double c2)
{
    c[0] = c0;
    c[1] = c1;
    c[2] = c2;
}

Vector3::Vector3(const Vector3& another)
{
    c[0] = another.c[0];
    c[1] = another.c[1];
    c[2] = another.c[2];
}

void Vector3::set(Vector3 & another) {
    c[0] = another.c[0];
    c[1] = another.c[1];
    c[2] = another.c[2];
}

/*
Vector3::Vector3(const Vector4& vec4)
{
    assert(vec4.getCoordinate(3)!=0);
    this->c[0] = vec4.getCoordinate(0)/vec4.getCoordinate(3);
    this->c[1] = vec4.getCoordinate(1)/vec4.getCoordinate(3);
    this->c[2] = vec4.getCoordinate(2)/vec4.getCoordinate(3);
}
*/

void Vector3::setCoordinates(double c0, double c1, double c2)
{
    c[0] = c0;
    c[1] = c1;
    c[2] = c2;
}

double* Vector3::getCoordinates(void)
{
    return c;
}

void Vector3::setCoordinate(int dim, double value)
{
    assert(dim>=0 && dim<=2);
    c[dim] = value;
}


double Vector3::getCoordinate(int dim)
{
    assert(dim>=0 && dim<=2);
    return c[dim];
}

double& Vector3::operator [] (int dim)
{
    assert(dim>=0 && dim<=2);
    double &k = c[dim];
    return k;
}

void Vector3::add(const Vector3& another)
{
    c[0] += another.c[0];
    c[1] += another.c[1];
    c[2] += another.c[2];
}

void Vector3::sub(const Vector3& another)
{
    c[0] -= another.c[0];
    c[1] -= another.c[1];
    c[2] -= another.c[2];
}

Vector3 Vector3::operator + (const Vector3& another)
{
    Vector3 new_vec(c[0]+another.c[0],c[1]+another.c[1],c[2]+another.c[2]);
    return new_vec;
}

Vector3 Vector3::operator - (const Vector3& another)
{
    Vector3 new_vec(c[0]-another.c[0],c[1]-another.c[1],c[2]-another.c[2]);
    return new_vec;
}

void Vector3::neg(void)
{
    c[0] = -c[0];
    c[1] = -c[1];
    c[2] = -c[2];
}

Vector3 Vector3::operator - (void)
{
    Vector3 new_vec(-c[0],-c[1],-c[2]);
    return new_vec;
}

void Vector3::divide(double val)
{
    c[0] /= val;
    c[1] /= val;
    c[2] /= val;
}

Vector3 Vector3::operator / (double val)
{
    Vector3 new_vec(c[0]/val,c[1]/val,c[2]/val);
    return new_vec;
}

void Vector3::scale(double scl)
{
    c[0] *= scl;
}

Vector3 Vector3::operator*(double scl)
{
    Vector3 new_vec(c[0]*scl,c[1]*scl,c[2]*scl);
    return new_vec;
}

double Vector3::dot(const Vector3& another)
{
    double res = 0;
    res += this->c[0]*another.c[0];
    res += this->c[1]*another.c[1];
    res += this->c[2]*another.c[2];
    return res;
}

void Vector3::cross(const Vector3& another)
{
    double n0,n1,n2;
    n0 = c[1]*another.c[2] - c[2]*another.c[1];
    n1 = -c[0]*another.c[2] + c[2]*another.c[0];
    n2 = c[0]*another.c[1] - c[1]*another.c[0];
    c[0] = n0;
    c[1] = n1;
    c[2] = n2;
}

Vector3 Vector3::operator *(const Vector3& another)
{
    double n0,n1,n2;
    n0 = c[1]*another.c[2] - c[2]*another.c[1];
    n1 = -c[0]*another.c[2] + c[2]*another.c[0];
    n2 = c[0]*another.c[1] - c[1]*another.c[0];
    Vector3 new_vec(n0,n1,n2);
    return new_vec;
}

double Vector3::getMagnitude(void)
{
    double sum = c[0]*c[0] + c[1]*c[1] + c[2]*c[2];
    return sqrt(sum);
}

void Vector3::toNormalized(void)
{
    double mag = this->getMagnitude();
    for(int i=0; i<3; ++i)
        c[i] /= mag;
}

Vector3 Vector3::getNormalized(void)
{
    Vector3 new_vec(*this);
    new_vec.toNormalized();
    return new_vec;
}

double Vector3::deg_cosine(Vector3& another)
{
    double d = dot(another);
    d /= sqrt(magsq()*another.magsq());
    return d;
}

double Vector3::magsq ()
{
    double sum = 0;
    for(int i=0; i<3; ++i)
        sum += c[i]*c[i];
    return sum;
}

double Vector3::distsq(Vector3& another)
{
    double sum = 0;
    for (int i=0; i<3; ++i)
        sum += (c[i]-another[i])*(c[i]-another[i]);
    return sum;
}

bool Vector3::operator == (const Vector3& another)
{
    for(int i=0; i<3; ++i)
        if(std::abs(c[i]-another.c[i])>0.000001)
            return false;
    return true;
}

std::ostream& operator << (std::ostream& out, const Vector3& vec)
{
    out<<"("<<vec.c[0]<<","<<vec.c[1]<<","<<vec.c[2]<<")";
    return out;
}
