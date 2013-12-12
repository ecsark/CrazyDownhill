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

struct BVertex
{
  float x, y, z;        //Vertex
  float nx, ny, nz;     //Normal
  float s0, t0;         //Texcoord0
};

class Node {
public:
    double xmin=DMAX,xmax=DMIN,ymin=DMAX,ymax=DMIN,zmin=DMAX,zmax=DMIN;
    virtual Vector3 getCenter();
    virtual double getRadius();
    virtual void draw() = 0;
  virtual void update() {}
    virtual ~Node(){}
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
    
    
};


class Transformation: public Group {
public:
    Kernel kernel;
    virtual void draw();
    void attachNodeR(Node*, double x, double y, double z);
    void attachNodeR(Transformation*);
};


class Geode: public Node {
protected:
  
  GLSLShader _shader;
  std::vector<BVertex> data;
  std::vector<unsigned> _indices;

  GLuint _VBODT;
  GLuint _VBOID;


public:
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
