#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector4.h"
#include "Vector3.h"
#include <OpenGL/gl.h>

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements

  public:
    Matrix4();        // constructor
    Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    Matrix4(double[4][4]);
    Matrix4(Matrix4&);
    //void operator = (Matrix4&);

    void toGLdoubleArray(GLdouble* arr);   //column major

    double get(int,int);
    double* getPointer();  // return pointer to matrix elements

    void multiply(Matrix4&);
    Vector4 multiply(Vector4&);
    Vector3 multiply3(Vector3&);
    Vector4 multiplyl(Vector4&);

    Matrix4 operator * (Matrix4&);
    Vector4 operator * (Vector4&);

    void identity();  // create identity matrix

    void rotateX(double);
    void rotateY(double);
    void rotateZ(double);
    void rotateBy(double angle, double x, double y, double z); //by an arbitrary axis

    void scale(double, double, double);
    void scale(Vector3&);

    void translate(double, double, double);
    void translate(Vector3&);

    void transpose(void);
    Matrix4 getTranspose(void);

    bool invert(void);

    friend std::ostream& operator << (std::ostream&, const Matrix4&);
};

#endif
