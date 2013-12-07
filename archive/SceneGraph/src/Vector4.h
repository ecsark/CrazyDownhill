#ifndef VECTOR4_H_INCLUDED
#define VECTOR4_H_INCLUDED

#include <iostream>
#include "Vector3.h"

class Vector4
{
    protected:
        double c[4];

    public:
        Vector4();
        Vector4(double, double, double);
        Vector4(double, double, double, double);
        Vector4(const Vector4&);
        Vector4(Vector3&);

        void setCoordinates(double, double, double, double);
        double* getCoordinates(void);

        void setCoordinate(int dim, double value);
        const double getCoordinate(int dim);
        double& operator [] (int dim);

        void add(const Vector4&);
        Vector4 operator + (const Vector4&);

        void sub(const Vector4&);
        Vector4 operator - (const Vector4&);

        void toDehomogenized(void);
        Vector4 getDehomogenized(void);

        friend std::ostream& operator << (std::ostream&, const Vector4&);

};

#endif // VECTOR4_H_INCLUDED
