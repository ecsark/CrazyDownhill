#include <cmath>
#include <cstring>
#include <cassert>
#include "Matrix4.h"

Matrix4::Matrix4()
{
  /*for (int i=0; i<4; ++i)
    for (int j=0; j<4; ++j)
      m[i][j] = 0;]
  */
}

Matrix4::Matrix4(
  float m00, float m01, float m02, float m03,
  float m10, float m11, float m12, float m13,
  float m20, float m21, float m22, float m23,
  float m30, float m31, float m32, float m33 )
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

Matrix4::Matrix4(Matrix4& another)
{
    memcpy(m, another.m, 16*sizeof(float));
}

/*
void Matrix4::operator = (Matrix4& another)
{
    memcpy(m, another.m, 16*sizeof(float));
}*/

//column major
void Matrix4::toGLfloatArray(GLfloat* arr)
{
    for(int i=0; i<4; ++i)
    {
        for(int j=0; j<4; ++j)
            arr[j*4+i] = m[i][j];
    }
}

Matrix4::Matrix4(float arr[4][4])
{
    memcpy(m, arr, 16*sizeof(float));
}

float Matrix4::get(int row, int col)
{
    assert(row>=0 && row<=3);
    assert(col>=0 && col<=3);
    return m[row][col];
}

float* Matrix4::getPointer()
{
  return &m[0][0];
}

void Matrix4::multiply(Matrix4& another)
{
    float new_mat[4][4];
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            float sum = 0;
            for(int k=0; k<4; k++)
            {
                sum += m[i][k] * another.m[k][j];
            }
            new_mat[i][j] = sum;
        }
    }
    memcpy(m,new_mat, 16*sizeof(float));
}

Vector4 Matrix4::multiply(Vector4& vec)
{
    Vector4 new_vec;
    for(int i=0; i<4; i++)
    {
        float sum = 0;
        for(int k=0; k<4; k++)
        {
            sum += m[i][k] * vec[k];
        }
        new_vec[i] = sum;
    }
    return new_vec;
}

Vector4 Matrix4::multiplyl(Vector4& vec)
{
    Vector4 new_vec;
    for(int i=0; i<4; i++)
    {
        float sum = 0;
        for(int k=0; k<4; k++)
        {
            sum += m[k][i] * vec[k];
        }
        new_vec[i] = sum;
    }
    return new_vec;
}

Matrix4 Matrix4::operator * (Matrix4& another)
{
    Matrix4 new_mat(*this);
    new_mat.multiply(another);
    return new_mat;
}

Vector4 Matrix4::operator * (Vector4& vec)
{
    return multiply(vec);
}

void Matrix4::identity()
{
  float ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}

// angle in radians
void Matrix4::rotateX(float angle)
{
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

// angle in radians
void Matrix4::rotateY(float angle)
{
	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = sin(angle);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = -sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

// angle in radians
void Matrix4::rotateZ(float angle)
{
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

// angle in radians
void Matrix4::rotateBy(float angle, float x, float y, float z)
{
    Vector3 v3(x,y,z);
    v3.toNormalized();
    x = v3[0]; y = v3[1]; z = v3[2];
    float c = cos(angle);
    float p = 1 - c;
    float s = sin(angle);
    m[0][0] = x*x*p+c;
	m[0][1] = x*y*p-z*s;
	m[0][2] = x*z*p+y*s;
	m[0][3] = 0;
	m[1][0] = x*y*p+z*s;
	m[1][1] = y*y*p+c;
	m[1][2] = y*z*p-x*s;
	m[1][3] = 0;
	m[2][0] = x*z*p-y*s;
	m[2][1] = y*z*p+x*s;
	m[2][2] = z*z*p+c;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}



void Matrix4::scale(float x, float y, float z)
{
    m[0][0] = x;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = y;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = z;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::scale(Vector3& vec)
{
    scale(vec[0],vec[1],vec[2]);
}

void Matrix4::translate(float x, float y, float z)
{
    m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = x;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = y;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = z;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::translate(Vector3& vec)
{
    translate(vec[0],vec[1],vec[2]);
}

void Matrix4::transpose()
{
    for(int i=0; i<3; ++i)
    {
        for(int j=i+1; j<4; ++j)
        {
            float tmp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = tmp;
        }
    }
}

bool gluInvertMatrix(const float m[16], float invOut[16])
{
    float inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}

bool Matrix4::invert()
{
    float k[16], inv[16];
    for(int i=0;i<4;++i)
        for(int j=0; j<4; ++j)
            k[i*4+j] = m[i][j];

    bool valid = gluInvertMatrix(k,inv);
    if(!valid)
        return false;
    for(int i=0;i<4;++i)
        for(int j=0;j<4;++j)
            m[i][j] = inv[i*4+j];
    return true;
}

std::ostream& operator << (std::ostream& out, const Matrix4& mat)
{
    for(int i=0; i<4; i++)
    {
        out<<mat.m[i][0]<<"\t";
        out<<mat.m[i][1]<<"\t";
        out<<mat.m[i][2]<<"\t";
        out<<mat.m[i][3]<<std::endl;
    }
    return out;
}
