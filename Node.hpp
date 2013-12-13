//
//  Node.h
//  SceneGraph
//
//  Created by Edward Cheng on 11/6/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#ifndef __SceneGraph__Node__
#define __SceneGraph__Node__

#include <vector>
#include "GLSLShader.hpp"
#include "Kernel.cpp"
#include "Vectors.hpp"

#define DMIN -999999999999
#define DMAX 999999999999

// forward declaration
class MotionController;

struct BVertex
{
  float x, y, z;        //Vertex
  float nx, ny, nz;     //Normal
  float s0, t0;         //Texcoord0
};

class Node {
protected:

  std::string _name;

public:

  Node(const std::string &str = ""):
    _name(str)
  {}
    double xmin=DMAX,xmax=DMIN,ymin=DMAX,ymax=DMIN,zmin=DMAX,zmax=DMIN;
    virtual Vector3 getCenter();
    virtual double getRadius();
    virtual void draw() = 0;
  virtual void update() {}
    virtual ~Node(){}
  virtual Node *getNode(const std::string &name)
  {
    if (_name == name)
      return this;
    return NULL;
  }
};

class Group: public Node {
protected:
    
    std::vector<Node*> nodeList;
public:
    virtual void draw();
    virtual ~Group();
    void attachNode(Node*); //deprecated
     //x,y,z as center
    void detachNode(Node*);
    void deleteNode(Node*); //which will free the node as well
  virtual void update();
  virtual Node *getNode(const std::string &name)
  {
    if (_name == name)
      return this;
    unsigned i;
    Node *node;
    for (i = 0; i < nodeList.size(); ++i)
      if ((node = nodeList[i]->getNode(name)))
	return node;
    return NULL;
  }
    
    
};


class Transformation: public Group {
public:
  MotionController *mc = 0;
  Kernel kernel;
  virtual void draw();
  void attachNodeR(Node*, double x, double y, double z);
  void attachNodeR(Transformation*);
  void setMotionController(MotionController *mc);
};


class Geode: public Node {
protected:
  
  GLSLShader _shader;
  std::vector<BVertex> data;
  std::vector<unsigned> _indices;
  bool _isTerrain;
  bool _isTerrainToon;
  GLuint _VBODT;
  GLuint _VBOID;


public:
  Geode(const std::string &name="", bool isTerrain = false, bool isTerrainToon = false):
    Node(name),
    _isTerrain(isTerrain),
    _isTerrainToon(isTerrainToon)
  {
  }
  
  void loadShaders(const std::string &vertex, const std::string &frag);
  virtual void initBuffers(void);
  void loadMesh(int nVertices, float *vertices, float *normals,
		float *texcoords, int nIndices, int *indices);
  virtual void draw();
};


class Sphere: public Geode {
private:
    double _radius;
    int _slices, _stacks;
public:
    Sphere(double radius, int slices, int stacks);
    virtual void draw();
};

class Cube: public Geode {
private:
    double _size;
public:
    Cube(double size);
    virtual void draw();
};

class Cubiod: public Geode {
private:
    double _length, _width, _height;
    // double _radius = -1;
public:
    Cubiod(double length, double width, double height);
    virtual void draw();
};

 #endif /* defined(__SceneGraph__Node__) */
