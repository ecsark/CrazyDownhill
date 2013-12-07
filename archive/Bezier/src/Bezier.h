//
//  Bezier.h
//  Bezier
//
//  Created by Edward Cheng on 11/12/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#ifndef __Bezier__Bezier__
#define __Bezier__Bezier__

class Bezier {
public:
    float ctrl[4][3];
    int eval;
    float **coordinates;
    float **normals;
    
    Bezier(int evaluation=25);
    void evaluate();

private:
    void normalize(float *norm);
};

#endif /* defined(__Bezier__Bezier__) */
