//
//  TerrainPhysics.cpp
//  Downhill
//
//  Created by Edward Cheng on 12/11/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#include "TerrainPhysics.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

#define MAG(a,b) sqrt((a)*(a)+(b)*(b))

// gravity
static Vector3 g(0.0f, -1.0f, 0.0f);

TerrainPhysics::TerrainPhysics(Terrain *terrain) {
  assert(terrain);
  this->tr = terrain;
  this->_nbVertex = tr->_nbVertex;
  this->setSpeed(1, 1, 1);
}
/*
Vector4 TerrainPhysics::getCurrentPosition(Transformation *transformation) {
  Vector4 pos(0,0,0,1);
  Vector4 cur = transformation->kernel * pos;
  return cur;
}
*/

// TODO: boundary check
Vector3 TerrainPhysics::getAcceleration(int idz, int idx) {
  Vector3 n = tr->_normalMap[INDEX(idz,idx)];
  return g - (n.dot(g))*n;
}

// input: current index / generated new index
Vector3 TerrainPhysics::next(int idz, int idx, int &nz, int &nx, Vector3 &norm) {
  
  Vector3 a = getAcceleration(idz, idx);
  speed = speed + a;
  nz = idz+speed.z+0.4; nx = idx+speed.x+0.4;
  if (nz >= _nbVertex || nx >= _nbVertex
      || nz <= 0 || nx <= 0) {
    // stop the car!
    nz = idz; nx = idx;
  }
  //debug
  //std::cout<<a<<endl;
  norm = tr->_normalMap[INDEX(nz,nx)];
  return tr->_pts[INDEX(nz, nx)];
}

Vector3 TerrainPhysics::nextR(int idz, int idx, int &nz, int &nx, Vector3 &norm) {
  assert(trTrans);
  Vector4 v = trTrans->getMatrix()*next(idz, idx, nz, nx, norm);
  Vector4 n = trTrans->getNormMatrix()*norm;
  n.normalize();
  Vector3 v3(v[0],v[1],v[2]);
  norm.set(n[0],n[1],n[2]);
  //debug
  std::cout<<idz<<","<<idx<<"->"<<nz<<","<<nx<<endl;
  
  //std::cout<<v3.dot(tr->_normalMap[INDEX(idz,idx)])<<endl;
  return v3;
}

Vector3 TerrainPhysics::nextR(Vector3 &norm) {
  prez = curz; prex = curx;
  return nextR(prez, prex, curz, curx, norm);
}

Vector3 TerrainPhysics::getSpeed() {
  return speed;
}

void TerrainPhysics::setSpeed(float x, float y, float z) {
  speed.set(x, y, z);
}

void TerrainPhysics::setTerrain2WorldRatio(float ratio) {
  r_t2w = ratio;
}

void TerrainPhysics::setCar2WorldRatio(float ratio) {
  r_c2w = ratio;
}

void TerrainPhysics::setTerrain2WorldPosition(Vector3 position) {
  p_t2w = position;
}

void TerrainPhysics::setCar2WorldPosition(Vector3 position) {
  p_c2w = position;
}

void TerrainPhysics::setTerrainKernel(Kernel* transKernel) {
  assert(transKernel);
  trTrans = transKernel;
}