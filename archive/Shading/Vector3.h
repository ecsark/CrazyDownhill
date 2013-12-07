#ifndef VECTOR3_H_INCLUDED
#define VECTOR3_H_INCLUDED

#include <iostream>
//#include "Vector4.h"

/*
 * RVO/NRVO should be turned on
 */

class Vector3
{
    protected:
        float c[3];

    public:
        Vector3();
        Vector3(float, float, float);
        Vector3(const Vector3&);
        //Vector3(const Vector4& vec4);

        void setCoordinates(float, float, float);
        float* getCoordinates(void);

        void setCoordinate(int dim, float value);
        float getCoordinate(int dim);
        float& operator [] (int dim);

        void add(const Vector3&);
        Vector3 operator + (const Vector3&);

        void sub(const Vector3&);
        Vector3 operator - (const Vector3&);

        void neg(void);
        Vector3 operator - (void);

        void scale(float);
        Vector3 operator * (float);

        float dot(const Vector3&);

        void cross(const Vector3&);
        Vector3 operator * (const Vector3&);

        void divide(float);
        Vector3 operator / (float);

        float getMagnitude(void);

        void toNormalized(void);
        Vector3 getNormalized(void);

        float deg_cosine(Vector3& another);
        float magsq ();
        float distsq(Vector3& another);
        bool operator == (const Vector3& another);

        friend std::ostream& operator << (std::ostream&, const Vector3&);

};


#endif // VECTOR3_H_INCLUDED
