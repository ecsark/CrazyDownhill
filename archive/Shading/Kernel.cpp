#include "Matrix4.h"
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

    void spin(float deg) {
        Matrix4 t;
        t.rotateY(deg);
        transformation = t * transformation;
    }

    void revolveY(float deg) {
        Matrix4 t;
        t.rotateY(deg);
        matrix = t*matrix;
    }
    
    void rotateBy(float angle, float x, float y, float z) {
        Matrix4 r;
        r.rotateBy(angle, x, y, z);
        transformation = r * transformation;
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
        
        const float TRACKBALL_SIZE = 1.3f;              // virtual trackball size (empirical value)
        Vector3 v1, v2;                                 // mouse drag positions in normalized 3D space
        
        // Compute mouse coordinates in window and normalized to -1..1
        // ((0,0)=window center, (-1,-1) = bottom left, (1,1) = top right)
        float halfWidth   = (float)width  / 2.0f;
        float halfHeight  = (float)height / 2.0f;
        float smallSize   = (halfWidth < halfHeight) ? halfWidth : halfHeight;
        v1[0] = ((float)fromX - halfWidth)  / smallSize;
        v1[1] = ((float)(height-fromY) - halfHeight) / smallSize;
        v2[0] = ((float)toX   - halfWidth)  / smallSize;
        v2[1] = ((float)(height-toY)   - halfHeight) / smallSize;
        
        // Compute z-coordinates on Gaussian trackball:
        float d = sqrtf(v1[0] * v1[0] + v1[1] * v1[1]); //distance
        v1[2]   = expf(-TRACKBALL_SIZE * d * d);
        d = sqrtf(v2[0] * v2[0] + v2[1] * v2[1]);
        v2[2] = expf(-TRACKBALL_SIZE * d * d);
        
        // Compute rotational angle:
        float angle = acos(v1.deg_cosine(v2));                          // angle = angle between v1 and v2
        
        // Compute rotational axis:
        v2.cross(v1);                                  // v2 = v2 x v1 (cross product)
        
        // Convert axis coordinates (v2) from WCS to OCS:
        Matrix4 mInv(transformation);
        mInv.transpose();                             // invert orthogonal matrix mInv
        Vector4 V4(v2);
        Vector4 V5;
        V5 = mInv.multiplyl(V4);                             // v2 = v2 x mInv (matrix multiplication)
        
        Vector3 V6(V5[0],V5[1],V5[2]);
        V6.toNormalized();// normalize v2 before rotation
        
        Matrix4 r;
        // Perform acutal model view matrix modification:
        r.rotateBy(angle, V6[0], V6[1], V6[2]);      // rotate model view matrix
        transformation = r * transformation;
    }

    
    void mouseZoom(int width, int height, int fromX, int fromY, int toX, int toY) {
        if (fromX != toX) {
            float s = (float)(toY-fromY)/height;
            zoom(1-s);
        }
    }
    
    void zoom(float scale) {
        Matrix4 mat;
        mat.scale(scale,scale,scale);
        matrix = matrix * mat;
    }

    void move(float x, float y, float z) {
        Matrix4 mat;
        mat.translate(x,y,z);
        matrix = mat * matrix;
    }
};
