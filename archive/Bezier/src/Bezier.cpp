//
//  Bezier.cpp
//  Bezier
//
//  Created by Edward Cheng on 11/12/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#include "Bezier.h"
#include <cmath>

Bezier::Bezier(int evaluation) :eval(evaluation) {
    coordinates = new float*[evaluation+1];
    normals = new float*[evaluation+1];
    for (int i=0; i<=eval; ++i) {
        coordinates[i] = new float[3];
        normals[i] = new float[3];
    }
}

void Bezier::normalize(float *norm) {
    float sum = sqrt(norm[0]*norm[0] + norm[1]*norm[1] + norm[2]*norm[2]);
    norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;
}

//control points should be up to down, meaning y should be monotonically decreasing
void Bezier::evaluate() {
    double a = 1.0;
    double b = 1.0 - a;
    for(int i = 0; i <= eval; i++) {
        float delta = (float)1.0/eval;
        coordinates[i][0] = ctrl[0][0]*a*a*a + ctrl[1][0]*3*a*a*b + ctrl[2][0]*3*a*b*b + ctrl[3][0]*b*b*b;
        coordinates[i][1] = ctrl[0][1]*a*a*a + ctrl[1][1]*3*a*a*b + ctrl[2][1]*3*a*b*b + ctrl[3][1]*b*b*b;
        coordinates[i][2] = ctrl[0][2]*a*a*a + ctrl[1][2]*3*a*a*b + ctrl[2][2]*3*a*b*b + ctrl[3][2]*b*b*b;
        //TODO: deal with cases when z!=0
        normals[i][0] = 3*delta*((ctrl[0][1]-ctrl[1][1])*a*a + 2*(ctrl[1][1]-ctrl[2][1])*a*b + (ctrl[2][1]-ctrl[3][1])*b*b);
        normals[i][1] = -3*delta*((ctrl[0][0]-ctrl[1][0])*a*a + 2*(ctrl[1][0]-ctrl[2][0])*a*b + (ctrl[2][0]-ctrl[3][0])*b*b);
        
        normals[i][2] = -3*delta*((ctrl[0][2]-ctrl[1][2])*a*a + 2*(ctrl[1][2]-ctrl[2][2])*a*b + (ctrl[2][2]-ctrl[3][2])*b*b);
        normalize(normals[i]);
        a -= (float)1.0/eval;
        b = 1.0 - a;
    }
}
