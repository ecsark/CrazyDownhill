
// # ifdef __linux__
// #  include <GL/glut.h>
// # elif __MACH__
// #  include <GLUT/glut.h>
// # else
// #  error "Operating system not supported"
// # endif
#include "glheader.hpp"
#include "Window.hpp"

int main(int ac, char *av[])
{
  srand(1);
  glutInit(&ac, av);
  Window &w = Window::Instance();

  glutDisplayFunc(Window::displayCallbackTramp);
  glutReshapeFunc(Window::reshapeCallbackTramp);
  glutIdleFunc(Window::idleCallbackTramp);
  glutKeyboardFunc(Window::manageKeyTramp);
  glutSpecialFunc(Window::manageKeySpecTramp);
  glutMouseFunc(Window::manageMouseTramp);
  glutMotionFunc(Window::manageMouseMotionTramp);
  
  w.show();
  return 0;
}
