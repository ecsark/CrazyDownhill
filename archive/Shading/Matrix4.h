#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector4.h"
#include "Vector3.h"
#include <OpenGL/gl.h>

class Matrix4
{
  protected:
    float m[4][4];   // matrix elements

  public:
    Matrix4();        // constructor
    Matrix4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
    Matrix4(float[4][4]);
    Matrix4(Matrix4&);
    //void operator = (Matrix4&);

    void toGLfloatArray(GLfloat* arr);   //column major

    float get(int,int);
    float* getPointer();  // return pointer to matrix elements

    void multiply(Matrix4&);
    Vector4 multiply(Vector4&);
    Vector4 multiplyl(Vector4&);

    Matrix4 operator * (Matrix4&);
    Vector4 operator * (Vector4&);

    void identity();  // create identity matrix

    void rotateX(float);
    void rotateY(float);
    void rotateZ(float);
    void rotateBy(float angle, float x, float y, float z); //by an arbitrary axis

    void scale(float, float, float);
    void scale(Vector3&);

    void translate(float, float, float);
    void translate(Vector3&);

    void transpose(void);

    bool invert(void);

    friend std::ostream& operator << (std::ostream&, const Matrix4&);
};

#endif
