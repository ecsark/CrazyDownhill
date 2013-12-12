//
//  MotionController.cpp
//  Downhill
//
//  Created by Edward Cheng on 12/11/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#include <cassert>
#include "MotionController.hpp"

MotionController::MotionController(TerrainPhysics* tp) {
  assert(tp);
  this->tp = tp;
  prevloc.set(0, 0, 0); //TODO: change to car's transformation
}


Matrix4 makeTransformMat(Vector3 &s, Vector3 &n) {
  s.normalize();
  n.normalize();
  n = n - (n.dot(s) * s);
  Vector3 fx = n.cross(s);
  fx.normalize();
  Matrix4 mat;
  mat.setColumn(0, fx);
  mat.setColumn(1, n);
  mat.setColumn(2, s);
  static float last[4] = {0,0,0,1};
  mat.setColumn(3, last);
  mat.setRow(3, last);
  // lift the car along normal direction
  mat.setColumn(3, n*18);
  return mat;
}

int k=0;

void MotionController::next() {
  if (i != itv) {
    i++;
    return;
  } else {
    i = 0;
  }
  if (k<100) k++;
  else return;
  assert(kernel);
  Vector3 norm;
  Vector3 newloc = tp->nextR(norm);
  Vector3 s = newloc - prevloc;
  kernel->move(s[0], s[1], s[2]);
  prevloc = newloc;
  // notice it is the norm of acc, not speed!
  Matrix4 balance = makeTransformMat(s, norm);
  kernel->setTransformation(balance);
  
}

void MotionController::setKernel(Kernel* kernel){
  assert(kernel);
  this->kernel = kernel;
}