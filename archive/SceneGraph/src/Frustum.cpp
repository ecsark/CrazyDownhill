//
//  Frustum.cpp
//  SceneGraph
//
//  Created by Edward Cheng on 11/8/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#include "Frustum.h"
#include <math.h>

#include <GLUT/glut.h>

#define ANG2RAD 3.14159265358979323846/180.0



Frustum::Frustum() {}

Frustum::~Frustum() {}

void Frustum::setCamInternals(float angle, float ratio, float nearD, float farD) {
    
	this->ratio = ratio;
	this->angle = angle;
	this->nearD = nearD;
	this->farD = farD;
    
	tang = (float)tan(angle* ANG2RAD * 0.5) ;
	nh = nearD * tang;
	nw = nh * ratio;
	fh = farD  * tang;
	fw = fh * ratio;
    
    
}


void Frustum::setCamDef(Vector3 &p, Vector3 &l, Vector3 &u) {
    
	Vector3 dir,nc,fc,X,Y,Z;
    
	Z = p - l;
	Z.toNormalized();
    
	X = u * Z;
	X.toNormalized();
    
	Y = Z * X;
    
	nc = p - Z * nearD;
	fc = p - Z * farD;
    
	ntl = nc + Y * nh - X * nw;
	ntr = nc + Y * nh + X * nw;
	nbl = nc - Y * nh - X * nw;
	nbr = nc - Y * nh + X * nw;
    
	ftl = fc + Y * fh - X * fw;
	ftr = fc + Y * fh + X * fw;
	fbl = fc - Y * fh - X * fw;
	fbr = fc - Y * fh + X * fw;
    
    setPlane(ntr,ntl,ftl,0);
    setPlane(nbl,nbr,fbr,1);
    setPlane(ntl,nbl,fbl,2);
    setPlane(nbr,ntr,fbr,3);
    setPlane(ntl,ntr,nbr,4);
    setPlane(ftr,ftl,fbl,5);
}


void Frustum::setPlane(Vector3 &v1, Vector3 &v2, Vector3 &v3, int ID) {
    
	Vector3 aux1, aux2;
	aux1 = v1 - v2;
	aux2 = v3 - v2;
    
    Vector3 aux = aux2 * aux1;
	normal[ID].set(aux);
    
	normal[ID].toNormalized();
	point[ID].set(v2);
	d[ID] = -(normal[ID].dot(point[ID]));
}

double Frustum::distance(Vector3 &p, int ID) {
    return (d[ID] + normal[ID].dot(p));
}

bool Frustum::inFrustum(Vector3 &p, double radius) {
    for(int i=0; i < 6; i++) {
		if (distance(p,i) < -radius) {
            return false;
        }
	}
    return true;
}