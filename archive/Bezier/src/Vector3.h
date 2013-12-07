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
        double c[3];

    public:
        Vector3();
        Vector3(double, double, double);
        Vector3(const Vector3&);
        //Vector3(const Vector4& vec4);
    
    void set(Vector3 &);

        void setCoordinates(double, double, double);
        double* getCoordinates(void);

        void setCoordinate(int dim, double value);
        double getCoordinate(int dim);
        double& operator [] (int dim);

        void add(const Vector3&);
        Vector3 operator + (const Vector3&);

        void sub(const Vector3&);
        Vector3 operator - (const Vector3&);

        void neg(void);
        Vector3 operator - (void);

        void scale(double);
        Vector3 operator * (double);

        double dot(const Vector3&);

        void cross(const Vector3&);
        Vector3 operator * (const Vector3&);

        void divide(double);
        Vector3 operator / (double);

        double getMagnitude(void);

        void toNormalized(void);
        Vector3 getNormalized(void);

        double deg_cosine(Vector3& another);
        double magsq ();
        double distsq(Vector3& another);
        bool operator == (const Vector3& another);

        friend std::ostream& operator << (std::ostream&, const Vector3&);

};


#endif // VECTOR3_H_INCLUDED
