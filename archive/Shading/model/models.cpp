#include "objreader.h"
#include "../Matrix4.h"
#include <iostream>
#include <cmath>
using namespace std;


class Model {

public:
    int nVerts;
    double *vertices;
    double *normals;
    double *texcoords;
    int nIndices;
    int *indices;
    double mmin[3] = {9999999,9999999,99999999},
        mmax[3] = {-9999999,-9999999,-99999999};
    Matrix4 translation;
    Matrix4 scaling;
    
    Model(char* fileName) {
        ObjReader::readObj(fileName, nVerts, &vertices,
                           &normals, &texcoords, nIndices, &indices);
        getBoundary();
    }

private:
    void getBoundary() {
        for (int i=0; i<nVerts; ++i) {
            for(int k=0; k<3; ++k) {
                if(vertices[i*3+k]>mmax[k])
                    mmax[k] = vertices[i*3+k];

                if(vertices[i*3+k]<mmin[k])
                    mmin[k] = vertices[i*3+k];
            }
        }

        double cx = (mmin[0]+mmax[0])/2, cy = (mmin[1]+mmax[1])/2, cz = (mmin[2]+mmax[2])/2;
        translation.translate(-cx,-cy,-cz);

        double maxsq = -1;
        for (int i=0; i<nVerts; ++i) {
            double x = vertices[i*3]-cx, y = vertices[i*3+1]-cy, z = vertices[i*3+2]-cz;
            double xz = x*x + z*z;
            double xy = x*x + y*y;
            double yz = y*y + z*z;

            if(xz > maxsq)  maxsq = xz;
            if(xy > maxsq)  maxsq = xy;
            if(yz > maxsq)  maxsq = yz;
        }

        double scale = 10.0/sqrt(maxsq);
        scaling.scale(scale,scale,scale);
    }

};