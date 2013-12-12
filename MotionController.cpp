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
  Vector3 newloc = tp->nextR();
  Vector3 s = newloc - prevloc;
  kernel->move(s[0], s[1], s[2]);
  prevloc = newloc;
}

void MotionController::setKernel(Kernel* kernel){
  assert(kernel);
  this->kernel = kernel;
}