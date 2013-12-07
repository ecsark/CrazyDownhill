//
//  Frustum.h
//  SceneGraph
//
//  Created by Edward Cheng on 11/8/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#ifndef __SceneGraph__Frustum__
#define __SceneGraph__Frustum__

#include "Vector3.h"

class Frustum
{
private:
    
	enum {
		TOP = 0,
		BOTTOM,
		LEFT,
		RIGHT,
		NEARP,
		FARP
	};
    
    
public:
    
	Vector3 normal[6], point[6];
    double d[6];
    
    
	Vector3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
	float nearD, farD, ratio, angle,tang;
	float nw,nh,fw,fh;
    
	Frustum();
	~Frustum();
    
	void setCamInternals(float angle, float ratio, float nearD, float farD);
	void setCamDef(Vector3 &p, Vector3 &l, Vector3 &u);
    
    void setPlane(Vector3 &v1, Vector3 &v2, Vector3 &v3, int planeID);
    
    bool inFrustum(Vector3 &p, double radius);

private:
    double distance(Vector3 &p, int planeID);
};

#endif /* defined(__SceneGraph__Frustum__) */
