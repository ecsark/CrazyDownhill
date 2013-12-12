
// # ifdef __linux__
// #  include <GL/glut.h>
// # elif __MACH__
// #  include <GLUT/glut.h>
// # else
// #  error "Operating system not supported"
// # endif
#include "glheader.hpp"
#include "Window.hpp"

//test
#include "TerrainPhysics.hpp"

void test(Window* w) {
  Terrain te(300, 300, 8, 3.0);
  TerrainPhysics tp(&te);
  
  tp.setSpeed(1, 1, 1);
  Kernel k;
  k.zoom(3);
  tp.setTerrainKernel(&k);
  int nz, nx;
  cout<<tp.next(2, 8, nz, nx)<<endl;
  cout<<nz<<","<<nx<<endl;
  cout<<"======"<<endl;
  for (int i=0; i<5; ++i) {
    cout<<tp.nextR()<<endl;
  }
}

int main(int ac, char *av[])
{
  srand(1);
  glutInit(&ac, av);
  Window &w = Window::Instance();
  //test(&w);

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
