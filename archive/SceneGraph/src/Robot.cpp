//
//  Robot.cpp
//  SceneGraph
//
//  Created by Edward Cheng on 11/7/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#include "Robot.h"

//Robot::Robot(double x, double y, double z) {
Robot::Robot() {
    Sphere *_head = new Sphere(5,50,50);
    Cubiod *_body = new Cubiod(10,10,15);
    Cubiod *_larm1 = new Cubiod(3,3,UARMLEN);
    Cubiod *_larm2 = new Cubiod(3,3,LARMLEN);
    Cubiod *_rarm1 = new Cubiod(3,3,UARMLEN);
    Cubiod *_rarm2 = new Cubiod(3,3,LARMLEN);
    Cubiod *_lleg1 = new Cubiod(4,4,ULEGLEN);
    Cubiod *_lleg2 = new Cubiod(4,4,LLEGLEN);
    Cubiod *_rleg1 = new Cubiod(4,4,ULEGLEN);
    Cubiod *_rleg2 = new Cubiod(4,4,LLEGLEN);
    /*
    head.kernel.move(0, 10, 0);
    body.kernel.move(0, 2, 0);
    larm1.kernel.move(-7, 4,0);
    larm2.kernel.move(-7, -1.5, 0);
    rarm1.kernel.move(7, 4,0);
    rarm2.kernel.move(7, -1.5, 0);
    lleg1.kernel.move(-3, -8, 0);
    lleg2.kernel.move(-3, -13, 0);
    rleg1.kernel.move(3, -8, 0);
    rleg2.kernel.move(3, -13, 0);
    
    head.attachNodeR(_head);
    body.attachNodeR(_body);
    larm1.attachNodeR(_larm1);
    larm2.attachNodeR(_larm2);
    rarm1.attachNodeR(_rarm1);
    rarm2.attachNodeR(_rarm2);
    lleg1.attachNodeR(_lleg1);
    lleg2.attachNodeR(_lleg2);
    rleg1.attachNodeR(_rleg1);
    rleg2.attachNodeR(_rleg2);*/
    
    head.attachNodeR(_head, 0, 10, 0);
    body.attachNodeR(_body, 0, 2, 0);
    larm1.attachNodeR(_larm1, -7, 4,0);
    larm2.attachNodeR(_larm2, -7, -1.5, 0);
    rarm1.attachNodeR(_rarm1, 7, 4,0);
    rarm2.attachNodeR(_rarm2, 7, -1.5, 0);
    lleg1.attachNodeR(_lleg1, -3, -8, 0);
    lleg2.attachNodeR(_lleg2, -3, -13, 0);
    rleg1.attachNodeR(_rleg1, 3, -8, 0);
    rleg2.attachNodeR(_rleg2, 3, -13, 0);
    
    
    larm.attachNodeR(&larm1);
    larm.attachNodeR(&larm2);
    rarm.attachNodeR(&rarm1);
    rarm.attachNodeR(&rarm2);
    lleg.attachNodeR(&lleg1);
    lleg.attachNodeR(&lleg2);
    rleg.attachNodeR(&rleg1);
    rleg.attachNodeR(&rleg2);
    
    
    attachNodeR(&head);
    attachNodeR(&body);
    attachNodeR(&larm);
    attachNodeR(&rarm);
    attachNodeR(&lleg);
    attachNodeR(&rleg);
}


void Robot::position(double x, double y, double z) {
    kernel.reset();
    kernel.move(x, y, z);
    xmin += x; xmax += x;
    ymin += y; ymax += y;
    zmin += z; zmax += z;
}


void RobotAnimator::setRobot(Robot * robot) {
    this->robot = robot;
}


void RobotAnimator::walk() {
    if (direction) {
        if (counter<UARMSTOP)
            robot->larm.kernel.rotateXFixed(UARMSPEED,0,(UARMLEN+LARMLEN)/2,0);
        if (counter>LARMSTART)
            robot->larm2.kernel.rotateXFixed(LARMSPEED,0,LARMLEN/2,0);
        if (120-counter<UARMSTOP)
            robot->rarm.kernel.rotateXFixed(-UARMSPEED,0,(UARMLEN+LARMLEN)/2,0);
        if (120-counter>LARMSTART)
            robot->rarm2.kernel.rotateXFixed(-LARMSPEED,0,LARMLEN/2,0);
        if (counter<ULEGSTOP)
            robot->lleg.kernel.rotateXFixed(-ULEGSPEED,0,-2,0);
        if (counter>LLEGSTART)
            robot->lleg2.kernel.rotateXFixed(-ULEGSPEED,0,LLEGLEN/2,0);
        if (120-counter<ULEGSTOP)
            robot->rleg.kernel.rotateXFixed(ULEGSPEED,0,-2,0);
        if (120-counter>LLEGSTART)
            robot->rleg2.kernel.rotateXFixed(ULEGSPEED,0,LLEGLEN/2,0);
        robot->head.kernel.move(HEADSPEED, 0, 0);
        counter --;
    } else {
        if (counter<UARMSTOP)
            robot->larm.kernel.rotateXFixed(-UARMSPEED,0,(UARMLEN+LARMLEN)/2,0);
        if (counter>LARMSTART)
            robot->larm2.kernel.rotateXFixed(-LARMSPEED,0,LARMLEN/2,0);
        if (120-counter<UARMSTOP)
            robot->rarm.kernel.rotateXFixed(UARMSPEED,0,(UARMLEN+LARMLEN)/2,0);
        if (120-counter>LARMSTART)
            robot->rarm2.kernel.rotateXFixed(LARMSPEED,0,LARMLEN/2,0);
        if (counter<ULEGSTOP)
            robot->lleg.kernel.rotateXFixed(ULEGSPEED,0,-2,0);
        if (counter>LLEGSTART)
            robot->lleg2.kernel.rotateXFixed(ULEGSPEED,0,LLEGLEN/2,0);
        if (120-counter<ULEGSTOP)
            robot->rleg.kernel.rotateXFixed(-ULEGSPEED,0,-2,0);
        if (120-counter>LLEGSTART)
            robot->rleg2.kernel.rotateXFixed(-ULEGSPEED,0,LLEGLEN/2,0);
        robot->head.kernel.move(-HEADSPEED, 0, 0);
        counter ++;
    }
    
    if(counter==120 || counter==0)
        direction ^= true;
}