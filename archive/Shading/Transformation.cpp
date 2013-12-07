#include "Matrix4.h"
#include <cassert>
#include <cstring>

class Viewport
{
protected:
    Matrix4 mat;

public:
    void setScreen(float x0, float x1, float y0, float y1)
    {
        assert(x0<x1 && y0<y1);
        float arr[] = {(x1-x0)/2,0,0,(x0+x1)/2,
                        0,(y1-y0)/2,0,(y0+y1)/2,
                        0,0,0.5,0.5,
                        0,0,0,1
                       };
        memcpy(mat.getPointer(),arr,16*sizeof(float));
    }

    void setScreen(float width, float height)
    {
        setScreen(0,width,0,height);
    }

    Matrix4 getMatrix()
    {
        return mat;
    }
};



class Camera
{
protected:
    Vector3 e;  //center of projection
    Vector3 d;  //look at point
    Vector3 up; //up vector
    Matrix4 C;  //camera matrix
public:
    Camera() {setDefault();}

    Matrix4 getCameraMatrix(void)
    {
        Vector3 z = e - d;
        z.toNormalized();
        Vector3 x = up * z;
        x.toNormalized();
        Vector3 y = z * x;
        Matrix4 k (x[0],y[0],z[0],e[0],
                   x[1],y[1],z[1],e[1],
                   x[2],y[2],z[2],e[2],
                   0,0,0,1);
        return k;
    }

    Matrix4 getCameraMatrixInverted(void)
    {
        Vector3 z = e - d;
        z.toNormalized();
        Vector3 x = up * z;
        x.toNormalized();
        Vector3 y = z * x;
        Matrix4 T_1(1,0,0,-e[0],
                    0,1,0,-e[1],
                    0,0,1,-e[2],
                    0,0,0,1);
        Matrix4 R_1(x[0],x[1],x[2],0,
                    y[0],y[1],y[2],0,
                    z[0],z[1],z[2],0,
                    0,0,0,1);
        Matrix4 k;
        k = R_1 * T_1;
        return k;
    }

    void setDefault() {
        setCenter(0,0,0);
        setLookAtPoint(0,0,-1);
        setUpVector(0,1,0);
    }

    void setCenter(float x, float y, float z)
    {
        e[0] = x;
        e[1] = y;
        e[2] = z;
    }


    void setLookAtPoint(float x, float y, float z)
    {
        d[0] = x;
        d[1] = y;
        d[2] = z;
    }


    void setUpVector(float x, float y, float z)
    {
        up[0] = x;
        up[1] = y;
        up[2] = z;
    }



};


class Projection
{
protected:
    Matrix4 mat;

public:
    void setFrustum(float left, float right,
                    float bottom, float top,
                    float near, float far) {
        float m[16];
        m[1] = m[3] = m[4] = m[7] = 0;
        m[8] = m[9] = m[12] = m[13] = m[15] = 0;
        m[14] = -1;
        m[0] = 2*near/(right-left);
        m[2] = (right+left)/(right-left);
        m[5] = 2*near/(top-bottom);
        m[6] = (top+bottom)/(top-bottom);
        m[10] = -(far+near)/(far-near);
        m[11] = -2*far*near/(far-near);
        memcpy(mat.getPointer(),m,16*sizeof(float));
    }

    Matrix4 getMatrix() {
        return mat;
    }
};
