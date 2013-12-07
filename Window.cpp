
#include <sys/time.h>
#include "Window.hpp"

double read_timer( )
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
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(-100,-100,-100);
  glMatrixMode(GL_MODELVIEW);
}
//----------------------------------------------------------------------------
// Callback method called when window is resized.
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
  // if (_scene != NULL)
  //   _scene->draw(_camera.getMatrix());
  glFlush();  
  glutSwapBuffers();
  float end = read_timer();
  std::cout << 1.f / (end - start) << " fps" << "\b\b\b\r" << std::flush;

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
  (void)x;
  (void)y;
  if (c == 'l')
    _camera.setPos(300, 500, 1550);
  else if (c == 'a')
    _camera.setPos(_camera.getPosX() - 0.5, _camera.getPosY(), _camera.getPosZ());
  else if (c == 'd')
    _camera.setPos(_camera.getPosX() + 0.5, _camera.getPosY(), _camera.getPosZ());
  else if (c == 'w')
    _camera.setPos(_camera.getPosX(), _camera.getPosY() + 0.5, _camera.getPosZ());
  else if (c == 's')
    _camera.setPos(_camera.getPosX(), _camera.getPosY() - 0.5, _camera.getPosZ());
  else if (c == 'q')
    _camera.setPos(_camera.getPosX(), _camera.getPosY(), _camera.getPosZ() + 0.5);
  else if (c == 'e')
    _camera.setPos(_camera.getPosX(), _camera.getPosY(), _camera.getPosZ() - 0.5);
  else if (c == 'm')
    {
    }
  else if (c == 'b')
    {
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
