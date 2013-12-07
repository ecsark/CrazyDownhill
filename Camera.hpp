#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# ifdef __linux__
#  include <GL/glut.h>
# elif __MACH__
#  include <GLUT/glut.h>
# else
#  error "Operating system not supported"
# endif

// # include "Vector3.hpp"
# include "Matrices.hpp"

class Camera
{

private:

  Vector3 _e; // center of projection
  Vector3 _d; // look at point
  Vector3 _up; // up vector

  Matrix4 _c;

public:

  Camera(float ex, float ey, float ez,
	 float dx, float dy, float dz,
	 float upx, float upy, float upz):
    _e(ex, ey, ez),
    _d(dx, dy, dz),
    _up(upx, upy, upz)
  {
    calibrate();
  }

  ~Camera() {}

  void calibrate()
  {
    Vector3 vz(_e - _d);
    vz.normalize();
    Vector3 vx;
    // vx.crossProduct(_up, vz);
    vx = _up.cross(vz);
    vx.normalize();
    Vector3 vy;
    // vy.crossProduct(vz, vx);
    vy = vz.cross(vx);
    _c.set(vx[0], vx[1], vx[2], 0,
	   vy[0], vy[1], vy[2], 0,
	   vz[0], vz[1], vz[2], 0,
	   0, 0, 0, 1.f);
    Matrix4 m2(1,0,0,-_e[0],
	       0,1,0,-_e[1],
	       0,0,1,-_e[2],
	       0,0,0,1);
    _c.transpose();
    m2.transpose();
    _c = _c * m2;
  }


  float getPosX(void) const {return _e[0];}
  float getPosY(void) const {return _e[1];}
  float getPosZ(void) const {return _e[2];}
  Matrix4 &getMatrix(void) {return _c;}

  void setPos(float x, float y, float z)
  {
    _e.set(x, y, z);
    calibrate();
  }

  void mulMatrix(const Matrix4 &m)
  {
    _c = _c * m;
  }

  void transposeMatrix(void)
  {
    _c.transpose();
  }

  const float *getGLMatrix(void)
  {
    return _c.get();
    return _c.getTranspose();
  }

  void move(const Vector3 &v)
  {
    move(v[0], v[1], v[2]);
  }
  
  void move(float x, float y, float z)
  {
    _e.set(_e[0] + x, _e[1] + y, _e[2] + z);
  }
};

#endif
