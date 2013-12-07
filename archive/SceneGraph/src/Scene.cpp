//
//  main.cpp
//  SceneGraph
//
//  Created by Edward Cheng on 11/6/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <vector>
#include <algorithm>
#include "Robot.h"
#include "Kernel.cpp"
#include "Transformation.cpp"
#include "Frustum.h"

using namespace std;

static int window_width = 512, window_height = 512;

enum DISP {WALKING, ARMY} disp = WALKING;

Kernel camKernel;

int mousex, mousey;
int space = 20;

//view frustum
double FOVY=60, ASPECT=1, ZNEAR=10,ZFAR=1000;
double frustum[24];
Vector3 norm[6], ppoint[6];
int frameCount = 0;
float fps = 0;
int currentTime = 0, previousTime = 0;
bool culling = false;
//Frustum frust;

Robot robot;
Robot army[900];
RobotAnimator animator(&robot);


void getFrustum();

void specialKeyCallback(int key, int x, int y)
{
    Camera cam;
    
    switch(key)
    {
        case GLUT_KEY_F1:
            disp = WALKING;
            cam.setCenter(0, 15, 50);
            cam.setLookAtPoint(0, 0, 0);
            cam.setUpVector(0, 1, 0);
            camKernel.setMatrix(cam.getCameraMatrix());
            break;
        case GLUT_KEY_F2:
            disp = ARMY;
            cam.setCenter(120, 50, 150);
            cam.setLookAtPoint(0, 0, 0);
            //cam.setCenter(0, 0, 1);
            //cam.setLookAtPoint(0, 0, 0);
            cam.setUpVector(0, 1, 0);
            camKernel.setMatrix(cam.getCameraMatrix());
            getFrustum();
            break;
    }
}


bool inFrustum(Vector3 center, double radius) {
    for (int i=0; i<6; ++i) {
        if ((center-ppoint[i]).dot(norm[i]) > radius)
            return false;
    }
    return true;
}


void getFrustum()
{
    const double an = FOVY / 2 * (3.141592653589/180.0);
    const double si = sin(an);
    const double co = cos(an);
    norm[0] = Vector3(0, co, -si);  ppoint[0] = Vector3(0,0,0);
    norm[1] = Vector3(0, -co, -si);  ppoint[1] = Vector3(0,0,0);
    norm[2] = Vector3(-co, 0, -si*ASPECT); ppoint[2] = Vector3(0,0,0);
    norm[3] = Vector3(co, 0, -si*ASPECT); ppoint[3] = Vector3(0,0,0);
    norm[4] = Vector3(0,0,-1); ppoint[4] = Vector3(0,0,-ZFAR);
    norm[5] = Vector3(0,0,1); ppoint[5] = Vector3(0,0,-ZNEAR);
    
    Matrix4 matt;
    matt = camKernel.getMatrix();
    Matrix4 mat;
    mat = camKernel.getMatrix();
    mat.invert();
    mat.transpose();
    for (int i=0; i<6; ++i) {
        norm[i] = mat.multiply3(norm[i]);
        norm[i].toNormalized();
        ppoint[i] = matt.multiply3(ppoint[i]);
    }

}


void walkingRobot() {
    animator.walk();
    robot.draw();
}

bool viewChanged = false;
bool cullingChanged = false;

void robotArmyOld() {
    
    for (int i=0; i<900; ++i) {
        army[i].position((i%30-15)*space,0,(i/30-15)*space);
        army[i].draw();
    }
    if (viewChanged || cullingChanged) {
        //cout<<count<<endl;
        viewChanged = false;
        cullingChanged = false;
    }
}


void robotArmy() {
    int count=0;
    
    
    for (int i=0; i<900; ++i) {
        army[i].position((i%30-15)*space,0,(i/30-15)*space);
        
        if (!culling) {
            army[i].draw();
            ++count;
        }
        else if (inFrustum(army[i].getCenter(), army[i].getRadius())) {
            army[i].draw();
            ++count;
        }
        
    }
    if (viewChanged || cullingChanged) {
        //cout<<count<<endl;
        viewChanged = false;
        cullingChanged = false;
    }
}

void calculateFPS()
{
    frameCount++;
    
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    int timeInterval = currentTime - previousTime;
    
    if(timeInterval > 1000)
    {
        fps = frameCount / (timeInterval / 1000.0f);
        previousTime = currentTime;
        frameCount = 0;
        std::cout<<fps<<endl;
    }
}


void keyCallback(unsigned char key, int, int)
{
    if (key == 27)
        exit(0);
    else if (key == 'c') {
        culling ^= true;
        cullingChanged = true;
    }
}


void reshapeCallback(int new_width, int new_height)
{
    window_width  = new_width;
    window_height = new_height;
    glViewport(0, 0, window_width, window_height);  // set new viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, new_width, new_height);
    gluPerspective(FOVY, ASPECT, ZNEAR, ZFAR);
}


void displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    Matrix4 camat;
    camat = camKernel.getMatrix();
    camat.invert();
    camat.transpose();
    glLoadMatrixd(camat.getPointer());
    glPushMatrix();

    switch (disp) {
        case WALKING:
            walkingRobot();
            break;
        case ARMY:
            //robotArmyOld();
            robotArmy();
            break;
        default:
            break;
    }
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    
}

void idleCallback()
{
    displayCallback();
    calculateFPS();
}

void mouseClickCallback(int button, int state, int x, int y) {
    mousex = x; mousey = y;
}



void mouseMoveCallback(int x, int y) {
    camKernel.trackballRotation(window_width, window_height, mousex, mousey, x, y);
    //camKernel.mouseZoom(window_width, window_height, mousex, mousey, x, y);
    mousex = x; mousey = y;
    getFrustum();
    viewChanged = true;
}


int main(int argc, char** argv)
{
    
    glutInit(&argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(window_width, window_height);      // set initial window size
    glutCreateWindow("OpenGL Cube for CSE167 Project 5");    	      // open window and set window title
    
    glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
    glClearColor(0.3,0.3,0.3,1);   	      // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);             	      // set shading to smooth
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_NORMALIZE);
    
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    
    //double specular[]  = {1.0, 1.0, 1.0, 1.0};
    //double shininess[] = {100.0};
    float position[]  = {5.0, 10.0, 5.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
        glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutIdleFunc(idleCallback);
    
    
        // Install callback functions:
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutIdleFunc(idleCallback);
    
    // Bind keyboard shortcut
    glutKeyboardFunc(keyCallback);
    glutMouseFunc(mouseClickCallback);
    glutMotionFunc(mouseMoveCallback);
    glutSpecialFunc(specialKeyCallback);
    
    specialKeyCallback(GLUT_KEY_F1,0,0);
    getFrustum();

    glutMainLoop();
    
    return 0;
}

