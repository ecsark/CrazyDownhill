

#include <sys/time.h>
#include "Window.hpp"
#include "ParticleSystem.hpp"

double read_timer(void)
{
  static bool initialized = false;
  static timeval start;
  struct timeval end;
  if( !initialized )
  {
    gettimeofday( &start, NULL );
    initialized = true;
  }
  gettimeofday( &end, NULL );
  return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
  return 0;
}

void Window::createScene(void)
{
  _skybox.loadSkybox();

  Group *world = new Group;
  _scene = world;
  Terrain *te = new Terrain(100, 100, 8, 1);
  te->loadShaders("shaders/vertex-shader.txt", "shaders/Terrain-color.frag");
  // te->loadShaders("shaders/terrain-toon.vert", "shaders/terrain-toon.frag");
  //t->loadShaders("shaders/directional.vert", "shaders/directional.frag");
  // Terrain *te2 = new Terrain(100, 100, 7);
  // te2->loadShaders("shaders/vertex-shader.txt", "shaders/frag-shader.txt");
  // world->attachNode(te);
  // world->attachNode(te2);
 

  Transformation *trans = new Transformation;
  trans->kernel.zoom(5);
  ParticleSystem *ps = new ParticleSystem;
  ps->loadShaders("shaders/particle-shader.vert", "shaders/particle-shader.frag");
  world->attachNode(trans);
  trans->attachNode(ps);
  Transformation *ttrans = new Transformation();
  ttrans->attachNode(te);
  world->attachNode(ttrans);
  ttrans->kernel.zoom(5);

  int nVerts;
  float *vertices;
  float *normals;
  float *texcoords;
  int nIndices;
  int *indices;

  ObjReader::readObj("models/Cube.obj", nVerts, &vertices, &normals, &texcoords, nIndices, &indices);

  Transformation *t = new Transformation;
  world->attachNode(t);
  Car *car = new Car;
  car->loadCabin(nVerts, vertices, normals, texcoords, nIndices, indices,
		 "shaders/vertex-shader.txt", "shaders/frag-shader.txt");
  ObjReader::readObj("models/Tube.obj", nVerts, &vertices, &normals, &texcoords, nIndices, &indices);
  car->addWheel(Car::Element::WHEEL_FRONTLEFT, nVerts, vertices, normals, texcoords, nIndices, indices,
		"shaders/vertex-shader.txt", "shaders/frag-shader.txt");
  car->addWheel(Car::Element::WHEEL_FRONTRIGHT, nVerts, vertices, normals, texcoords, nIndices, indices,
  		"shaders/vertex-shader.txt", "shaders/frag-shader.txt");
  car->addWheel(Car::Element::WHEEL_BACKLEFT, nVerts, vertices, normals, texcoords, nIndices, indices,
  		"shaders/vertex-shader.txt", "shaders/frag-shader.txt");
  car->addWheel(Car::Element::WHEEL_BACKRIGHT, nVerts, vertices, normals, texcoords, nIndices, indices,
  		"shaders/vertex-shader.txt", "shaders/frag-shader.txt");
  //t->kernel.move(0,18,0); // moved to controller
  t->attachNode(car);
  t->kernel.rotateY_pre(90);
  //t->kernel.zoom(0.5);
  // FIXME : delete allocated array from objreader
  
  TerrainPhysics *tp = new TerrainPhysics(te);
  tp->setTerrainKernel(&ttrans->kernel);
  tp->setSpeed(5, 3, 5);
  MotionController *mc = new MotionController(tp);
  t->setMotionController(mc);
  

  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
      
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {80.0};
  float position[]  = {0, 10, 0, 0.0};	// lightsource position
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
    
    
  //glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void Window::idleCallback(void)
{
  this->displayCallback();
}

void Window::idleCallbackTramp(void)
{
  Window &w = Window::Instance();
  w.idleCallback();
}


void Window::reshapeCallback(int w, int h)
{
  _width = w;
  _height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 10000.0);
  //glTranslatef(-100,-100,-100);
  //gluLookAt(-300, 300, 100, -100, 150, -100, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
}

void Window::reshapeCallbackTramp(int w, int h)
{
  Window &win = Window::Instance();
  win.reshapeCallback(w, h);
}

void Window::displayCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // gluLookAt(_camera.getPosX(), _camera.getPosY(), _camera.getPosZ(),
  // 	    0.f,0.f,0.f, 0.f,1.f,0.f);
  Matrix4 m;
  m.identity();
  float start = read_timer();
  glLoadMatrixf(_camera.getGLMatrix());
  
  //scene
  _skybox.draw();
  if (_scene != NULL)
    {
      _scene->update();
      _scene->draw();
    }
  // _scene->draw(_camera.getMatrix());
  glFlush();
  glutSwapBuffers();
  float end = read_timer();
#ifndef __MACH__
  std::cout << 1.f / (end - start) << " fps" << "\b\b\b\r" << std::flush;
#endif
}

void Window::displayCallbackTramp(void)
{
  Window &win = Window::Instance();
  win.displayCallback();
}

void Window::manageKeyTramp(unsigned char c, int x, int y)
{
  Window &w = Window::Instance();
  w.manageKey(c, x, y);
}

void Window::manageKey(unsigned char c, int x, int y)
{
  float speed = 10;
  (void)x;
  (void)y;
  if (c == 27)
  exit(0);
  // deprecated
  else if (c == 'l')
    _camera.setPos(_camera.getPosX()+20, _camera.getPosY()+180, _camera.getPosZ()+180);
  else if (c == 'a')
    _camera.setPos(_camera.getPosX() - speed, _camera.getPosY(), _camera.getPosZ());
  else if (c == 'd')
    _camera.setPos(_camera.getPosX() + speed, _camera.getPosY(), _camera.getPosZ());
  else if (c == 'w')
    _camera.setPos(_camera.getPosX(), _camera.getPosY() + speed, _camera.getPosZ());
  else if (c == 's')
    _camera.setPos(_camera.getPosX(), _camera.getPosY() - speed, _camera.getPosZ());
  else if (c == 'q')
    _camera.setPos(_camera.getPosX(), _camera.getPosY(), _camera.getPosZ() + speed);
  else if (c == 'e')
    _camera.setPos(_camera.getPosX(), _camera.getPosY(), _camera.getPosZ() - speed);
  else if (c == 'f')
    glutFullScreen();
  else if (c == 'm')
  {
  }
  else if (c == 'b')
  {
  }
  else if (c == 'f')
  {
    if (!_fullScreen)
      glutFullScreen();
    else
      {
	glutReshapeWindow(_width, _height);
	glutPositionWindow(0,0);
      }
    _fullScreen = !_fullScreen;
  }
  else if (c == 't')
  {
    _terrainToon = !_terrainToon;
    // toggle toon on terrain
  }
  else if (c == 'g')
  {
    // regenerate the terrain
  }
}

void Window::manageKeySpecTramp(int c, int x, int y)
{
  Window &w = Window::Instance();
  w.manageKeySpec(c, x, y);
}

void Window::manageKeySpec(int c, int x, int y)
{
  (void)x;
  (void)y;
  (void)c;
}


void Window::manageMouseTramp(int button, int state, int x, int y)
{
  Window &w = Window::Instance();
  w.manageMouse(button, state, x, y);
}

void Window::manageMouse(int button, int state, unsigned x, unsigned y)
{
  (void)x;
  (void)y;
  (void)button;
  (void)state;
}

void Window::manageMouseMotionTramp(int x, int y)
{
  Window &w = Window::Instance();
  w.manageMouseMotion(x, y);
}

void Window::manageMouseMotion(unsigned x, unsigned y)
{
  (void)x;
  (void)y;
}
