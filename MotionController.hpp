//
//  MotionController.hpp
//  Downhill
//
//  Created by Edward Cheng on 12/11/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#ifndef __Downhill__MotionController__
#define __Downhill__MotionController__

#include "Node.hpp"
#include "Kernel.cpp"
#include "TerrainPhysics.hpp"

class MotionController {
private:
  Kernel* kernel;
  TerrainPhysics* tp;
  Vector3 prevloc;
  int itv = 5;
  int maxitr = 1000;
  int i = 0;
public:
  MotionController(TerrainPhysics* tp);
  void next();
  void setKernel(Kernel* kernel);
};

#endif /* defined(__Downhill__MotionController__) */
