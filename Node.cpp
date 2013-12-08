//
//  Node.cpp
//  SceneGraph
//
//  Created by Edward Cheng on 11/6/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

# ifdef __linux__
#  include <GL/gl.h>
#  include <GL/glut.h>
# elif __MACH__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# else
#  error "Operating system not supported"
# endif
#include <cassert>
#include "Node.h"

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

void Group::detachNode(Node* node) {
    assert(node);
    // FIXME : reimplement function
    // nodeList.erase(std::remove(nodeList.begin(), nodeList.end(), node), nodeList.end());
}

void Group::deleteNode(Node* node) {
    detachNode(node);
    delete node;
}


void Transformation::draw() {
    glPushMatrix();
    glMultMatrixf(kernel.getMatrix().getTranspose());
    Group::draw();
    glPopMatrix();
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

