#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "Matrices.hpp"
#include <cmath>

class Kernel
{
protected:
    Matrix4 matrix;
    Matrix4 transformation;

public:
    Kernel() {
        reset();
    }

    void reset() {
        transformation.identity();
        matrix.identity();
    }

    Matrix4 getMatrix() {
        Matrix4 mat;
        mat = matrix * transformation;
        return mat;
    }
    
    void setMatrix(const Matrix4& mat) {
        matrix = mat;
        transformation.identity();
    }

    void spin(double deg) {
        Matrix4 t;
        t.rotateY(deg);
        transformation = t * transformation;
    }

    void rotateX(double deg) {
        Matrix4 t;
        t.rotateX(deg);
        transformation = t * transformation;
    }
    
    void revolveY(double deg) {
        Matrix4 t;
        t.rotateY(deg);
        matrix = t*matrix;
    }
    
    void rotateBy(double angle, double x, double y, double z) {
        Matrix4 r;
        r.rotate(angle, x, y, z);
        transformation = r * transformation;
    }
    
    void rotateXFixed(double deg, double x, double y, double z) {
        Matrix4 mat, tam;
        mat.translate(-x,-y,-z);
        tam.rotateX(deg);
        mat = tam * mat;
        tam.translate(x, y, z);
        mat = tam * mat;
        //matrix = matrix * mat;
        transformation = mat * transformation;
    }
    
    
    /** Rotates the matrix according to a fictitious trackball, placed in
     the middle of the given window.
     The trackball is approximated by a Gaussian curve.
     The trackball coordinate system is: x=right, y=up, z=to viewer<BR>
     The origin of the mouse coordinates zero (0,0) is considered to be top left.
     @param width, height  window size in pixels
     @param fromX, fromY   mouse starting position in pixels
     @param toX, toY       mouse end position in pixels
     */
    void trackballRotation(int width, int height, int fromX, int fromY, int toX, int toY) {
    
        if (fromX==toX && fromY==toY)
            return;
        
        const double TRACKBALL_SIZE = 1.3f;              // virtual trackball size (empirical value)
        Vector3 v1, v2;                                 // mouse drag positions in normalized 3D space
        
        // Compute mouse coordinates in window and normalized to -1..1
        // ((0,0)=window center, (-1,-1) = bottom left, (1,1) = top right)
        double halfWidth   = (double)width  / 2.0f;
        double halfHeight  = (double)height / 2.0f;
        double smallSize   = (halfWidth < halfHeight) ? halfWidth : halfHeight;
        v1[0] = ((double)fromX - halfWidth)  / smallSize;
        v1[1] = ((double)(height-fromY) - halfHeight) / smallSize;
        v2[0] = ((double)toX   - halfWidth)  / smallSize;
        v2[1] = ((double)(height-toY)   - halfHeight) / smallSize;
        
        // Compute z-coordinates on Gaussian trackball:
        double d = sqrtf(v1[0] * v1[0] + v1[1] * v1[1]); //distance
        v1[2]   = expf(-TRACKBALL_SIZE * d * d);
        d = sqrtf(v2[0] * v2[0] + v2[1] * v2[1]);
        v2[2] = expf(-TRACKBALL_SIZE * d * d);
        
        // Compute rotational angle:
        double angle = acos(v1.deg_cosine(v2));                          // angle = angle between v1 and v2
        
        // Compute rotational axis:
        v2.cross(v1);                                  // v2 = v2 x v1 (cross product)
        
        // Convert axis coordinates (v2) from WCS to OCS:
        Matrix4 mInv(transformation);
        mInv.transpose();                             // invert orthogonal matrix mInv
        Vector4 V4(v2);
        Vector4 V5;
        V5 = mInv.multiplyl(V4);                             // v2 = v2 x mInv (matrix multiplication)
        
        Vector3 V6(V5[0],V5[1],V5[2]);
        V6.normalize();// normalize v2 before rotation
        
        Matrix4 r;
        // Perform acutal model view matrix modification:
        r.rotate(angle, V6[0], V6[1], V6[2]);      // rotate model view matrix
        transformation = r * transformation;
    }

    
    void mouseZoom(int width, int height, int fromX, int fromY, int toX, int toY) {
      (void) width;
        if (fromX != toX) {
            double s = (double)(toY-fromY)/height;
            zoom(1-s);
        }
    }
    
    void zoom(double scale) {
        Matrix4 mat;
        mat.scale(scale,scale,scale);
        matrix = matrix * mat;
    }

    void move(double x, double y, double z) {
        Matrix4 mat;
        mat.translate(x,y,z);
        matrix = mat * matrix;
    }
};

#endif
