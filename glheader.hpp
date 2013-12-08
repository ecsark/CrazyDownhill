
#ifndef GLHEADER_HPP_
# define GLHEADER_HPP_

# ifdef __linux__
#  ifndef __GLEW_H__
#   include <GL/glew.h>
#  endif
#  include <GL/gl.h>
#  include <GL/glut.h>
# elif __MACH__
#  ifndef __GLEW_H__
#  endif
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# else
#  error "Operating system not supported"
# endif

#endif
