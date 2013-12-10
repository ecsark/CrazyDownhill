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
  void loadShaders(const std::string &vertex, const std::string &frag) {
    _shader.LoadShaders(vertex.c_str(), frag.c_str());
    // _shader.LoadFromFile(GL_VERTEX_SHADER, vertex);
    // _shader.LoadFromFile(GL_FRAGMENT_SHADER, frag);
  }

  virtual void initBuffers(void)
  {
    glGenBuffers(1, &_VBODT);
    glBindBuffer(GL_ARRAY_BUFFER, _VBODT);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BVertex) * data.size(), &(data[0].x), GL_DYNAMIC_DRAW);
    
    glGenBuffers(1, &_VBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*_indices.size(), &_indices[0], GL_DYNAMIC_DRAW);
  }

  void loadMesh(int nVertices, float *vertices, float *normals,
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
      }
    for (i = 0; i < nIndices; ++i)
      _indices[i] = indices[i];
  }

  virtual void draw() {
    _shader.Use();
    glBindBuffer(GL_ARRAY_BUFFER, _VBODT);
    std::cout << "program : " << _shader.GetProgram() << std::endl;

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
  
    std::cout << "used VBODT " << _VBODT << std::endl;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBOID);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, NULL);
    glutSolidSphere(10,10,10);
    _shader.UnUse();
  }
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
