//
//  Node.cpp
//  SceneGraph
//
//  Created by Edward Cheng on 11/6/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#include "glheader.hpp"
#include <cassert>
#include "Node.hpp"
#include "MotionController.hpp"

void pushAndLoad() {
    //GLdouble matrix[16];
    //glGetDoublev (GL_MODELVIEW_MATRIX, matrix);
    glPushMatrix();
    //glLoadMatrixd(matrix);
}

Vector3 Node::getCenter() {
    Vector3 vec((xmax+xmin)/2,(ymax+ymin)/2,(zmax+zmin)/2);
    return vec;
}

double Node::getRadius() {
    double xlen = (xmax-xmin)/2, ylen = (ymax-ymin)/2, zlen = (zmax-zmin)/2;
    return sqrt(xlen*xlen+ylen*ylen+zlen*zlen);
}


void Group::draw() {
    for (unsigned i=0; i<nodeList.size(); ++i) {
      if (nodeList[i])
        nodeList[i]->draw();
    }
}

Group::~Group() {
    for (unsigned i=0; i<nodeList.size(); ++i) {
        //delete nodeList[i];
    }
}

//deprecated
void Group::attachNode(Node* node) {
    assert(node);
    nodeList.push_back(node);
}

void Group::detachNode(Node* node) {
    assert(node);
    // FIXME : reimplement function
    // nodeList.erase(std::remove(nodeList.begin(), nodeList.end(), node), nodeList.end());
}

void Group::deleteNode(Node* node) {
    detachNode(node);
    delete node;
}

void Transformation::attachNodeR(Node* node, double x, double y, double z) {
  assert(node);
  kernel.move(x, y, z);
  xmin = node->xmin+x; xmax = node->xmax+x;
  ymin = node->ymin+y; ymax = node->ymax+y;
  zmin = node->zmin+z; zmax = node->zmax+z;
  nodeList.push_back(node);
}

void Transformation::attachNodeR(Transformation * node) {
  assert(node);
  if (node->xmin<xmin)    xmin = node->xmin;
  if (node->xmax>xmax)    xmax = node->xmax;
  if (node->ymin<ymin)    ymin = node->ymin;
  if (node->ymax>ymax)    ymax = node->ymax;
  if (node->zmin<zmin)    zmin = node->zmin;
  if (node->zmax>zmax)    zmax = node->zmax;
  nodeList.push_back(node);
}

void Transformation::setMotionController(MotionController *mc) {
  assert(mc);
  this->mc = mc;
  mc->setKernel(&kernel);
}


void Transformation::draw() {
  glPushMatrix();
  if (mc) {
    mc->next();
  }
  glMultMatrixf(kernel.getMatrix().getTranspose());
  Group::draw();
  glPopMatrix();
}



void Geode::loadShaders(const std::string &vertex, const std::string &frag) {
  _shader.LoadShaders(vertex.c_str(), frag.c_str());
}

void Geode::initBuffers(void)
{
  glGenBuffers(1, &_VBODT);
  glBindBuffer(GL_ARRAY_BUFFER, _VBODT);
  glBufferData(GL_ARRAY_BUFFER, sizeof(BVertex) * data.size(), &(data[0].x), GL_DYNAMIC_DRAW);
    
  glGenBuffers(1, &_VBOID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBOID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*_indices.size(), &_indices[0], GL_DYNAMIC_DRAW);
}

void Geode::loadMesh(int nVertices, float *vertices, float *normals,
		     float *texcoords, int nIndices, int *indices)
{
  int i;

  data.resize(nVertices);
  _indices.resize(nIndices);
  for (i = 0; i < nVertices; ++i)
    {
      BVertex bv;
      bv.x = vertices[i * 3];
      bv.y = vertices[i * 3 + 1];
      bv.z = vertices[i * 3 + 2];

      bv.nx = normals[i * 3];
      bv.ny = normals[i * 3 + 1];
      bv.nz = normals[i * 3 + 2];
	
      //FIXME : Check if it's correct
      if (texcoords)
	{
	  bv.t0 = texcoords[i * 2];
	  bv.s0 = texcoords[i * 2 + 1];
	}
      else
	{
	  bv.t0 = 0;
	  bv.s0 = 0;
	}
      data[i] = bv;
    }
  for (i = 0; i < nIndices; ++i)
    _indices[i] = indices[i];
}

void Geode::draw() {
  _shader.Use();
  glBindBuffer(GL_ARRAY_BUFFER, _VBODT);
  // vertex position
  GLuint vertexID = glGetAttribLocation(_shader.GetProgram(), "vertexPosition");
  glEnableVertexAttribArray(vertexID);
  glVertexAttribPointer(vertexID, 3, GL_FLOAT, GL_FALSE, sizeof(BVertex), BUFFER_OFFSET(0));
  // normal
  GLuint normalID = glGetAttribLocation(_shader.GetProgram(), "norm");
  glEnableVertexAttribArray(normalID);
  glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, sizeof(BVertex), BUFFER_OFFSET(sizeof(float) * 3));
  // texcoord
  GLuint texID = glGetAttribLocation(_shader.GetProgram(), "textCoord");
  glEnableVertexAttribArray(texID);
  glVertexAttribPointer(texID, 2, GL_FLOAT, GL_FALSE, sizeof(BVertex), BUFFER_OFFSET(sizeof(float) * 6));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBOID);
  glDrawElements(GL_TRIANGLES, (int)_indices.size(), GL_UNSIGNED_INT, NULL);
  // glutSolidSphere(1,10,10);
  _shader.UnUse();
}


Sphere::Sphere(double radius, int slices, int stacks) {
    _radius = radius; _slices = slices; _stacks = stacks;
    xmax = ymax = zmax = radius;
    xmin = ymin = zmin = -radius;
}

void Sphere::draw() {
    glutSolidSphere(_radius,_slices,_stacks);
}


Cube::Cube(double size) {
    _size = size;
    xmax = ymax = zmax = size/2;
    xmin = ymin = zmin = -size/2;
}

void Cube::draw() {
    glutSolidCube(_size);
}


Cubiod::Cubiod(double length, double width, double height) {
    _length = length;
    _width = width;
    _height = height;
    xmax = _length/2; xmin = -xmax;
    ymax = _height/2; ymin = -ymax;
    zmax = _width/2; zmin = -zmax;
}

void Cubiod::draw() {
    glPushMatrix();
    Matrix4 mat;
    mat.scale(_length, _height, _width);
    glMultMatrixf(mat.getTranspose());
    glutSolidCube(1);
    glPopMatrix();
}

