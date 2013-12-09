
#ifndef WINDOW_HPP_
# define WINDOW_HPP_


# include "glheader.hpp"
# include <vector>
# include "Singleton.hpp"
# include "Camera.hpp"
# include "Node.hpp"
# include "Terrain.hpp"


class Window : public Singleton<Window>
{
private:

  int _width;
  int _height;
  Node *_scene;
  Camera _camera;


public:
  Window() :
    _scene(NULL),
    _camera(0.f,0.f, 20.f, 500.f,0.f,-20.f, 0.f,1.f,0.f)
  {
    _width = 500;
    _height = 500;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(_width, _height);
    glutCreateWindow("CSE 167");

    GLenum res = glewInit();
    /*if (res != GLEW_OK)
      std::cout << "Glew error" << std::endl;
*/
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);

    createScene();
  }

  virtual ~Window(){}


  void createScene(void)
  {
    Group *world = new Group;
    _scene = world;
    Terrain *t = new Terrain(100, 100, 8);
    t->loadShaders("shaders/vertex-shader.txt", "shaders/frag-shader.txt");
    world->attachNode(t);
      glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
      
      float specular[]  = {1.0, 1.0, 1.0, 1.0};
      float shininess[] = {80.0};
      float position[]  = {0, 10, 0, 0.0};	// lightsource position
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
      glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      
      // Generate light source:
      glLightfv(GL_LIGHT0, GL_POSITION, position);
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);

  }


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
