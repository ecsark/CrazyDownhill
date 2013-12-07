#include <iostream>
#include <math.h>
#include <glew.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <vector>
#include <algorithm>
#include "Transformation.cpp"
#include "Kernel.cpp"
#include "model/models.cpp"
#include "model/cube.cpp"
#include "shader.h"

using namespace std;

static int window_width = 512, window_height = 512;

Kernel model_kernel;
Model* model;
Cube* cube;
Model *dragon, *bunny, *sandal;

Kernel light_kernel[3];
Kernel* m_kernel = &model_kernel;
static int light_name[3] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2};
GLfloat light_position[4] = {0,0,10,1};
GLfloat light_position2[4] = {0,0,10,0};

GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 0.8,0.8,0.8,0.8 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 80.0 };
GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};

Shader* shader[3];

static bool fScreen = false;
static bool freeRotation = true;
static bool effectOn = false;

bool light_on[3];

int mousex, mousey;
int mousekey;

enum DISP {CUBE=1, DRAGON, BUNNY, SANDAL} disp;


void positionLight() {
    glPushMatrix();
    
    for(int i=0; i<3; ++i) {
        if (light_on[i]) {
            glLoadMatrixf(light_kernel[i].getMatrix().getPointer());
            if (i==0)
                glLightfv (light_name[i], GL_POSITION, light_position2);
            else
                glLightfv (light_name[i], GL_POSITION, light_position);
        }
    }
    glPopMatrix();
}

void drawModel(Model* m)
{
    glMatrixMode(GL_MODELVIEW);
    if(fScreen) {
        Matrix4 mat;
        mat = m->scaling * m->translation;
        mat.transpose();
        Matrix4 cmat;
        cmat = model_kernel.getMatrix();
        mat = mat*cmat;
        glLoadMatrixf(mat.getPointer());
    }
    else
        glLoadMatrixf(model_kernel.getMatrix().getPointer());
    positionLight();
    glBegin(GL_TRIANGLES);
    for(int i=0; i<m->nVerts*3; i+=3) {
        float r = abs(m->vertices[i])/m->mmax[0];
        float g = abs(m->vertices[i+1])/m->mmax[1];
        float b = abs(m->vertices[i+2])/m->mmax[2];
        r = 1-(r-1)*(r-1);
        g = 1-(g-1)*(g-1);
        b = 1-(b-1)*(b-1);
        //float r = 0.2, g = 0.2, b = 0.9;
        glColor3f(r*0.99,b*0.99,g*0.99);
        glNormal3f(m->normals[i], m->normals[i+1], m->normals[i+2]);
        glVertex3f(m->vertices[i],m->vertices[i+1],m->vertices[i+2]);
    }
    glEnd();
}


void drawCube() {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(model_kernel.getMatrix().getPointer());
    positionLight();
    glColor3f(0.5, 0.5, 0.5);
    glutSolidCube(6);
}


void specialKeyCallback(int key, int x, int y)
{

    switch(key)
    {
    case GLUT_KEY_F1:
            disp = CUBE; model = NULL;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, no_mat);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);
            break;
    case GLUT_KEY_F2:
            disp = DRAGON; model = dragon; break;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, no_mat);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);
    case GLUT_KEY_F3: disp = BUNNY; model = bunny;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);
            break;
    case GLUT_KEY_F4: disp = SANDAL; model = sandal;
            glTranslatef (3.75, 3.0, 0.0);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, no_mat);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
            break;
    default: return;
    }
    model_kernel.reset();
}



void keyCallback(unsigned char key, int, int)
{
    if (key == 27)
        exit(0);
    else if (key == 'f')
        fScreen ^= true;
    else if (key == 'r')
        freeRotation ^= true;
    else if (key=='e') {
        effectOn ^= true;
        for (int i=0; i<3; ++i) {
            if(light_on[i] && effectOn)
                shader[i]->bind();
            else if(light_on[i] && !effectOn)
                shader[i]->unbind();
        }
    }
    else if (key=='1' || key== '2' || key=='3') {
        int lidx = key-'1';
        if (light_on[lidx]) {
            glDisable(light_name[lidx]);
            if(effectOn)
                shader[lidx]->unbind();
        }
        else {
            glEnable(light_name[lidx]);
            if(effectOn)
                shader[lidx]->bind();
        }
        light_on[lidx] ^= true;
    }
    if (key=='!')
        m_kernel = &light_kernel[0];
    else if (key=='@')
        m_kernel = &light_kernel[1];
    else if (key=='#')
        m_kernel = &light_kernel[2];
    else if (key=='m')
        m_kernel = &model_kernel;
}

void mouseClickCallback(int button, int state, int x, int y) {
    mousex = x; mousey = y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        mousekey = GLUT_LEFT_BUTTON;
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        mousekey = GLUT_RIGHT_BUTTON;
}



void mouseMoveCallback(int x, int y) {
    //if (mousekey == GLUT_LEFT_BUTTON)
    if (freeRotation)
        m_kernel->trackballRotation(window_width, window_height, mousex, mousey, x, y);
    //else if (mousekey == GLUT_RIGHT_BUTTON)
    else
        m_kernel->mouseZoom(window_width, window_height, mousex, mousey, x, y);
    mousex = x; mousey = y;
    if (m_kernel != &model_kernel) {
        positionLight();
    }
}


// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
    window_width  = new_width;
    window_height = new_height;
    glViewport(0, 0, window_width, window_height);  // set new viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
    glTranslatef(0, 0, -20);
}



void displayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch(disp) {
    case CUBE: drawCube();break;
    case DRAGON:
    case SANDAL:
    case BUNNY:
        assert(model);
        drawModel(model);
        break;
    
    default:return;
    }

    glFlush();
    glutSwapBuffers();
}

void idleCallback()
{
    displayCallback();  // call display routine to re-draw cube
}


int main(int argc, char** argv)
{
    
    glutInit(&argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with float buffering, RGB colors, and depth buffering
    glutInitWindowSize(window_width, window_height);      // set initial window size
    glutCreateWindow("OpenGL Cube for CSE167 Project 4");    	      // open window and set window title
    
    glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
    glClearColor(0,0,0,1);   	      // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);             	      // set shading to smooth
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_NORMALIZE);
    
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    /*
    // Generate material properties:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
     */
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    
    glEnable(GL_LIGHTING);
    
    for (int i=0; i<3; ++i) {
        glEnable(light_name[i]);
        light_on[i] = light_on[1] = light_on[2] = true;
    }
    //glEnable(GL_LIGHT0);
    
    GLfloat light_ambient[] = { 0, 0, 0, 1.0 };
    GLfloat light_color1[] = { 1,0,0,1};
    GLfloat light_color2[] = { 0,1,0,1};
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color1);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_color2);
    float spot_direction[3] = {0,0,-1};
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 12);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2);
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spot_direction);
    
    
    // Install callback functions:
    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutIdleFunc(idleCallback);
    
    // Bind keyboard shortcut
    glutKeyboardFunc(keyCallback);
    glutSpecialFunc(specialKeyCallback);
    glutMouseFunc(mouseClickCallback);
    glutMotionFunc(mouseMoveCallback);
    
    // Initialize cube matrix:
    disp = CUBE;
    cube = new Cube();
    bunny = new Model("model/bunny.obj");
    sandal = new Model("model/sandal.obj");
    dragon = new Model("model/dragon.obj");
    
    model = NULL;
    
    
    glewInit();
    
    shader[0] = new Shader("shaders/directional.vert","shaders/directional.frag");
    shader[1] = new Shader("shaders/point.vert","shaders/point.frag");
    shader[2] = new Shader("shaders/spotlight.vert","shaders/spotlight.frag");
    
    //setShaders();
    //initGL();
    
    glutMainLoop();
    return 0;
}
