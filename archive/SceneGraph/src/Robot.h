//
//  Robot.h
//  SceneGraph
//
//  Created by Edward Cheng on 11/7/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#ifndef __SceneGraph__Robot__
#define __SceneGraph__Robot__

#include "Node.h"

static const double UARMLEN = 6, LARMLEN = 6,
        ULEGLEN = 6, LLEGLEN = 8;

class Robot: public Transformation {
    friend class RobotAnimator;
private:
    Transformation head, body,larm, rarm, lleg, rleg,
        larm1, larm2, rarm1, rarm2,
        lleg1, lleg2, rleg1, rleg2;
public:
    //Robot(double x, double y, double z);
    Robot();
    void position (double x, double y, double z);
};


static const int UARMSTOP = 70, LARMSTART = 70;
static const double UARMSPEED = 0.01f, LARMSPEED = 0.020f;
static const int ULEGSTOP = 90, LLEGSTART = 70;
static const double ULEGSPEED = 0.012f, LLEGSPEED = 0.025f;
static const double HEADSPEED = 0.006f;

class RobotAnimator {
private:
    Robot* robot;
    int counter = 60;
    bool direction = true;
    
public:
    RobotAnimator(){}
    RobotAnimator(Robot* r): robot(r){}
    void setRobot(Robot*);
    void walk();
};

#endif /* defined(__SceneGraph__Robot__) */
