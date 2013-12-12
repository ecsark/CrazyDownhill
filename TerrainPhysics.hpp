//
//  TerrainPhysics.hpp
//  Downhill
//
//  Created by Edward Cheng on 12/11/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#ifndef __Downhill__TerrainPhysics__
#define __Downhill__TerrainPhysics__

#include "Vectors.hpp"
#include "Kernel.cpp"
#include "Terrain.hpp"

class TerrainPhysics{
private:
  Terrain *tr;
  int _nbVertex;
  float r_t2w = 1, r_c2w = 1;
  Vector3 p_t2w, p_c2w;
  int curz = 2, curx = 2, prez, prex;
protected:
  Vector3 speed;
  Kernel *trTrans;
public:
  TerrainPhysics(Terrain *);
  // speed relative to terrain index
  Vector3 getAcceleration(int idz, int idx);
  Vector3 next(int idz, int idx, int &nz, int &nx);
  // return world coordinate (only se after trTrans set)
  Vector3 nextR(int idz, int idx, int &nz, int &nx);
  // auto drive
  Vector3 nextR();
  Vector3 getSpeed(); //TODO: move to protected
  void setSpeed(float x, float y, float z);
  void setTerrain2WorldRatio(float ratio);
  void setCar2WorldRatio(float ratio);
  void setTerrain2WorldPosition(Vector3 position);
  void setCar2WorldPosition(Vector3 position);
  void setTerrainKernel(Kernel* transKernel);
};


#endif /* defined(__Downhill__TerrainPhysics__) */
