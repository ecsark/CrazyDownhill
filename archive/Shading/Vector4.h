#ifndef VECTOR4_H_INCLUDED
#define VECTOR4_H_INCLUDED

#include <iostream>
#include "Vector3.h"

class Vector4
{
    protected:
        float c[4];

    public:
        Vector4();
        Vector4(float, float, float);
        Vector4(float, float, float, float);
        Vector4(const Vector4&);
        Vector4(Vector3&);

        void setCoordinates(float, float, float, float);
        float* getCoordinates(void);

        void setCoordinate(int dim, float value);
        const float getCoordinate(int dim);
        float& operator [] (int dim);

        void add(const Vector4&);
        Vector4 operator + (const Vector4&);

        void sub(const Vector4&);
        Vector4 operator - (const Vector4&);

        void toDehomogenized(void);
        Vector4 getDehomogenized(void);

        friend std::ostream& operator << (std::ostream&, const Vector4&);

};

#endif // VECTOR4_H_INCLUDED
