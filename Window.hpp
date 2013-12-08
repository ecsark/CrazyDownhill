
#ifndef WINDOW_HPP_
# define WINDOW_HPP_

# ifdef __linux__
#  include <GL/glut.h>
# elif __MACH__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# else
#  error "Operating system not supported"
# endif

# include <vector>
# include "Singleton.hpp"
# include "Camera.hpp"
# include "Node.hpp"
// # include "MatrixTransform.hpp"
// # include "Sphere.hpp"
// # include "Cube.hpp"
// # include "Group.hpp"
// # include "Guy.hpp"
// # include "Terrain.hpp"

class Window : public Singleton<Window>
{
private:

  int _width;
  int _height;
  // Node *_scene;
  Camera _camera;


public:
  Window() :
    // _scene(NULL),
    _camera(0.f,0.f, 20.f, 500.f,0.f,-20.f, 0.f,1.f,0.f)
  {
    _width = 500;
    _height = 500;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(_width, _height);
    glutCreateWindow("CSE 167");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);

    // createScene();
  }

  virtual ~Window(){}


  // void createScene(void)
  // {
  //   int i;
  //   int j;
  //   int max = 100;

  //   Group *world = new Group("World");
  //   _scene = world;
  //   Terrain *t = new Terrain("Ground", 100, 100, 8);
  //   _scene->addNode(t);
  //   // Guy *g;

  //   // for (i = -(max / 2) - 1; i < max / 2; ++i)
  //   //   {
  //   // 	for (j = -(max / 2) - 1; j < max /2 ; ++j)
  //   // 	  {
  //   // 	    g = new Guy("Guy");
  //   // 	    g->translate(i * 4, 0, j  * 4);
  //   // 	    world->addNode(g);
  //   // 	  }
  //   //   }
    
  // }


  static void idleCallbackTramp(void);
  static void reshapeCallbackTramp(int, int);
  static void displayCallbackTramp(void);
  static void manageKeyTramp(unsigned char c, int x, int y);
  static void manageKeySpecTramp(int c, int x, int y);
  static void manageMouseTramp(int button, int state, int x, int y);
  static void manageMouseMotionTramp(int x, int y);

  void idleCallback(void);
  void reshapeCallback(int, int);
  void displayCallback(void);
  void manageKey(unsigned char c, int x, int y);
  void manageKeySpec(int c, int x, int y);
  void manageMouse(int button, int state, unsigned x, unsigned y);
  void manageMouseMotion(unsigned x, unsigned y);

  void show()
  {
    glutMainLoop();
  }
};

#endif
