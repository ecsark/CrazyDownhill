
#ifndef WINDOW_HPP_
# define WINDOW_HPP_


# include "glheader.hpp"
# include <vector>
# include "Singleton.hpp"
# include "Camera.hpp"
# include "Node.hpp"
# include "Terrain.hpp"
# include "objreader.h"
# include "Car.hpp"
# include "TerrainPhysics.hpp"
# include "MotionController.hpp"
# include "Skybox.hpp"
# include "Skybox.hpp"

class Window : public Singleton<Window>
{
private:

  int _width;
  int _height;
  Node *_scene;
  Camera _camera;
  Skybox _skybox;
  bool _fullScreen;
  bool _terrainToon;

public:
  Window() :
    _scene(NULL),
    //_camera(0.f,0.f, 20.f, 500.f,0.f,-20.f, 0.f,1.f,0.f)
    _camera(300.f,400.f, 2800.f, 50.f,0.f,250.f, 0.f,1.f,0.f),
    _terrainToon(false)
  {
    _width = 800;
    _height = 800;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(_width, _height);
    glutCreateWindow("CSE 167");
    // glutFullScreen();

    GLenum res = glewInit();
    if (res != GLEW_OK)
      std::cout << "Glew error" << std::endl;

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);

    createScene();
  }

  virtual ~Window(){}


  static void idleCallbackTramp(void);
  static void reshapeCallbackTramp(int, int);
  static void displayCallbackTramp(void);
  static void manageKeyTramp(unsigned char c, int x, int y);
  static void manageKeySpecTramp(int c, int x, int y);
  static void manageMouseTramp(int button, int state, int x, int y);
  static void manageMouseMotionTramp(int x, int y);

  void createScene(void);
  void idleCallback(void);
  void reshapeCallback(int, int);
  void displayCallback(void);
  void manageKey(unsigned char c, int x, int y);
  void manageKeySpec(int c, int x, int y);
  void manageMouse(int button, int state, unsigned x, unsigned y);
  void manageMouseMotion(unsigned x, unsigned y);
  Camera &getCamera(void) {return _camera;};
  bool isTerrainToon(void) const {return _terrainToon;}

  void show()
  {
    glutMainLoop();
  }
};

#endif
