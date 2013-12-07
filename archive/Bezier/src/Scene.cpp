//
//  Bezier
//
//  Created by Edward Cheng on 11/11/13.
//  Copyright (c) 2013 Edward Cheng. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <vector>
#include <cmath>
#include "Bezier.h"
#include "SOIL.h"
#include "Kernel.cpp"
using namespace std;

#define EVALNUM 30
#define SENSITIVITY 1

static int window_width = 512, window_height = 512;
int mousex, mousey;
int STEPS = 360;
bool mousedown;
bool textureOn = true;
bool editing = true;
bool continuity = false;
vector<Bezier> segments;

Kernel trackerball;



void loadTexture()
{
    GLuint texture[1];     // storage for one texture
    int twidth, theight;   // texture width/height [pixels]
    
    // Load image file
    unsigned char* image = SOIL_load_image("logo.jpg", &twidth, &theight, 0, SOIL_LOAD_RGB);
    
    if (image==NULL) return;
 
    // Create ID for texture
    glGenTextures(1, &texture[0]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Set this texture to be the one we are working with
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    
    // Make sure no bytes are padded:
    
    // Select GL_MODULATE to mix texture with quad color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable( GL_TEXTURE_2D );
}


void addCurve() {
    //see where are most bottom curve located
    float maxy = -99999;
    for (int i=0; i<segments.size(); ++i)
        for (int j=0; j<4; ++j)
            maxy = segments[i].ctrl[j][1]>maxy ? segments[i].ctrl[j][1] : maxy;
    if (maxy==-99999)   maxy = 0;
    Bezier b;
    b.ctrl[0][0] = 0.5; b.ctrl[1][0] = 2; b.ctrl[2][0] = 2; b.ctrl[3][0] = 2.5;
    b.ctrl[0][1] = maxy + 5; b.ctrl[1][1] = maxy + 3.5; b.ctrl[2][1] = maxy + 2.5; b.ctrl[3][1] = maxy + 1.5;
    b.ctrl[0][2] = b.ctrl[1][2] = b.ctrl[2][2] = b.ctrl[3][2] = 0;
    b.evaluate();
    segments.push_back(b);
}


void processHandle(int segid, int ctrlid) {
    if (ctrlid == 2 && segid<segments.size()) {
        float dx = segments[segid].ctrl[3][0] - segments[segid].ctrl[2][0];
        float dy = segments[segid].ctrl[3][1] - segments[segid].ctrl[2][1];
        float dmag = sqrt(dx*dx + dy*dy);
        float nx =  segments[segid+1].ctrl[1][0] - segments[segid+1].ctrl[0][0];
        float ny = segments[segid+1].ctrl[1][1] - segments[segid+1].ctrl[0][1];
        float nmag = sqrt(nx*nx + ny*ny);
        segments[segid+1].ctrl[1][0] = segments[segid+1].ctrl[0][0] + dx/dmag * nmag;
        segments[segid+1].ctrl[1][1] = segments[segid+1].ctrl[0][1] + dy/dmag * nmag;
        memcpy(segments[segid+1].ctrl[0], segments[segid].ctrl[3], 3*sizeof(float));
        segments[segid+1].evaluate();
    }
    else if (ctrlid == 1 && segid>0) {
        float dx = segments[segid].ctrl[0][0] - segments[segid].ctrl[1][0];
        float dy = segments[segid].ctrl[0][1] - segments[segid].ctrl[1][1];
        float dmag = sqrt(dx*dx + dy*dy);
        float nx =  segments[segid-1].ctrl[2][0] - segments[segid-1].ctrl[3][0];
        float ny = segments[segid-1].ctrl[2][1] - segments[segid-1].ctrl[3][1];
        float nmag = sqrt(nx*nx + ny*ny);
        segments[segid-1].ctrl[2][0] = segments[segid-1].ctrl[3][0] + dx/dmag * nmag;
        segments[segid-1].ctrl[2][1] = segments[segid-1].ctrl[3][1] + dy/dmag * nmag;
        memcpy(segments[segid-1].ctrl[3], segments[segid].ctrl[0], 3*sizeof(float));
        segments[segid-1].evaluate();
    }
    else if (ctrlid == 0 && segid>0) {
        memcpy(segments[segid-1].ctrl[3], segments[segid].ctrl[0], 3*sizeof(float));
        segments[segid-1].evaluate();
    }
    else if (ctrlid == 3 && segid<segments.size()) {
        memcpy(segments[segid+1].ctrl[0], segments[segid].ctrl[3], 3*sizeof(float));
        segments[segid+1].evaluate();
    }
}


void popCurve() {
    if (segments.size()>2) {
        segments.pop_back();
    }
}


void drawControlPoints() {
    //draw points
    glPointSize(8.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < segments.size(); ++i)
        for (int j=0; j<4; ++j) {
            if (j==0 || j==3)
                glColor3f(0.2, 0.8, 1);
            else
                glColor3f(1, 1, 0);
            glVertex3fv(segments[i].ctrl[j]);
        }
    glEnd();
    
    //draw lines
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0,1,0);
    for (int i=0; i<segments.size(); ++i) {
        for (int j=0; j<3; ++j) {
            glVertex3fv(segments[i].ctrl[j]);
            glVertex3fv(segments[i].ctrl[j+1]);
        }
    }
    glEnd();
}


void rotateY(float* in, float* out, float deg) {
    deg = deg * M_PI / 180;
    float c = cos(deg), s = sin(deg);
    out[0] = in[0]*c + in[2]*s;
    out[1] = in[1];
    out[2] = -in[0]*s + in[2]*c;
}

void drawSurface(int steps) {
    //texture params
    int segsum = 0;
    for (int i=0; i<segments.size(); ++i)
        segsum += segments[i].eval;
    double ttheight = 1.0/(segsum);
    double ttwidth = 1.0/steps;
    
    glBegin(GL_QUADS);
    int segcount = 0;
    
    float current1[3], current2[3], current1norm[3], current2norm[3];
    float next1[3], next2[3], next1norm[3], next2norm[3];
    
    for (int i=0; i<segments.size(); ++i) {
        for (int j = 0; j<segments[i].eval; ++j) {
            memcpy(current1, segments[i].coordinates[j], 3*sizeof(float));
            memcpy(current2, segments[i].coordinates[j+1], 3*sizeof(float));
            memcpy(current1norm, segments[i].normals[j], 3*sizeof(float));
            memcpy(current2norm, segments[i].normals[j+1], 3*sizeof(float));
            for (int k=0; k<=steps; ++k) {
                rotateY(current1, next1, 360.0/steps);
                rotateY(current2, next2, 360.0/steps);
                rotateY(current1norm, next1norm, 360.0/steps);
                rotateY(current2norm, next2norm, 360.0/steps);
                glNormal3fv(current1norm);
                glTexCoord2f(k*ttwidth, (segcount+j)*ttheight);
                glVertex3fv(current1);
                glNormal3fv(next1norm);
                glTexCoord2f((k+1)*ttwidth, (segcount+j)*ttheight);
                glVertex3fv(next1);
                glNormal3fv(next2norm);
                glTexCoord2f((k+1)*ttwidth, (segcount+j+1)*ttheight);
                glVertex3fv(next2);
                glNormal3fv(current2norm);
                glTexCoord2f(k*ttwidth, (segcount+j+1)*ttheight);
                glVertex3fv(current2);
                memcpy(current1, next1, 3*sizeof(float));
                memcpy(current2, next2, 3*sizeof(float));
                memcpy(current1norm, next1norm, 3*sizeof(float));
                memcpy(current2norm, next2norm, 3*sizeof(float));
            }
        }
        segcount += segments[i].eval;
    }
    glEnd();
}

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    Matrix4 camat;
    camat = trackerball.getMatrix();
    camat.invert();
    camat.transpose();
    glLoadMatrixd(camat.getPointer());
    
    glEnable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    drawSurface(STEPS);
    if (editing) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 0);
        glLineWidth(3.0);
        glBegin(GL_LINES);
        glVertex3f(0, -50, 0);
        glVertex3f(0, 50, 0);
        glEnd();
        glClear(GL_DEPTH_BUFFER_BIT);
        glColor3f(0, 1, 0);
        drawControlPoints();
    }
    
    glFlush();
    glutSwapBuffers();
    
}

void idleCallback() {
    displayCallback();
}

void specialKeyCallback(int key, int x, int y)
{}


void keyCallback(unsigned char key, int, int)
{
    if (key == 27)
        exit(0);
    else if (key == 't') {
        textureOn ^= true;
        if (textureOn) glEnable(GL_TEXTURE_2D);
        else glDisable(GL_TEXTURE_2D);
    }
    else if (key == 'r') {
        editing ^= true;
        if (editing)
            trackerball.reset();
    }
    else if (key == 'a' && editing)
        addCurve();
    else if (key == 'd' && editing)
        popCurve();
    else if (key == 'c' && editing) {
        continuity ^= true;
        if (continuity) {
            processHandle(0, 2);
        }
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
    glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
    glTranslatef(0, 0, -20);
}



void mouseClickCallback(int button, int state, int x, int y) {
    mousex = x; mousey = y;
    if (state == GLUT_DOWN)
        mousedown = true;
    else if (state == GLUT_UP)
        mousedown = false;
}

void mouseMoveCallback(int x, int y) {
    if (!mousedown)
        return;
    if (editing) {
        if (x<window_width/2)
            return;
        
        GLdouble projection[16];
        GLdouble modelview[16];
        GLint viewport[4];
        
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetIntegerv( GL_VIEWPORT, viewport);
        
        double nx, ny, nz;
        //z has to be zero!
        gluUnProject(x, viewport[3]-y, 0, modelview, projection, viewport, &nx, &ny, &nz);
        
        nx *= 2; ny *= 2;
        
        for (int i=0; i<segments.size(); ++i) {
            bool curveChanged = false;
            for (int j=0; j<4; ++j) {
                double xx = segments[i].ctrl[j][0];
                double yy = segments[i].ctrl[j][1];
                double distsq = (xx-nx)*(xx-nx) + (yy-ny)*(yy-ny);
                if (distsq < SENSITIVITY) {
                    segments[i].ctrl[j][0] = nx;
                    segments[i].ctrl[j][1] = ny;
                    curveChanged = true;
                    if (continuity) {
                        if ((i==0&&j>=2)||(i==1&&j<=1)) {
                            if (j==3 || j==0) {
                                segments[0].ctrl[2][0] += nx-xx; segments[0].ctrl[2][1] += ny-yy;
                                segments[1].ctrl[1][0] += nx-xx; segments[1].ctrl[1][1] += ny-yy;
                                segments[0].evaluate(); segments[1].evaluate();
                            }
                            processHandle(i, j);
                        }
                    }
                    break;
                }
            }
            if (curveChanged) {
                segments[i].evaluate();
                
                break;
            }
        }
    }
    else {
        trackerball.trackballRotation(window_width, window_height, mousex, mousey, x, y);
        mousex = x; mousey = y;
    }
}


int main(int argc, char** argv)
{
    
    glutInit(&argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(window_width, window_height);      // set initial window size
    glutCreateWindow("OpenGL Cube for CSE167 Project 6");    	      // open window and set window title
    
    glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
    glDepthFunc(GL_LEQUAL);    // configure depth testing
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearColor(0.5,0.5,0.5,1);   	      // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);             	      // set shading to smooth
    glEnable(GL_NORMALIZE);
    
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    
    float specular[]  = {1.0, 1.0, 1.0, 1.0};
    float shininess[] = {100.0};
    float position[]  = {-15.0, 10.0, 25.0, 0.0};	// lightsource position
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    // Generate light source:
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
    
    Bezier curve1;
    curve1.ctrl[0][0] = 3; curve1.ctrl[0][1] = 12; curve1.ctrl[0][2] = 0;
    curve1.ctrl[1][0] = 2; curve1.ctrl[1][1] = 10; curve1.ctrl[1][2] = 0;
    curve1.ctrl[2][0] = 3; curve1.ctrl[2][1] = 5; curve1.ctrl[2][2] = 0;
    curve1.ctrl[3][0] = 5; curve1.ctrl[3][1] = 2; curve1.ctrl[3][2] = 0;
    curve1.evaluate();
    segments.push_back(curve1);
    Bezier curve2;
    curve2.ctrl[0][0] = 5; curve2.ctrl[0][1] = 2; curve2.ctrl[0][2] = 0;
    curve2.ctrl[1][0] = 3; curve2.ctrl[1][1] = -2; curve2.ctrl[1][2] = 0;
    curve2.ctrl[2][0] = 4; curve2.ctrl[2][1] = -8; curve2.ctrl[2][2] = 0;
    curve2.ctrl[3][0] = 5; curve2.ctrl[3][1] = -12; curve2.ctrl[3][2] = 0;
    curve2.evaluate();
    segments.push_back(curve2);
    loadTexture();
    
    glutMainLoop();
    
    return 0;
}

