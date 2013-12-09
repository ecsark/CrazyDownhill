#ifndef TERRAIN_HPP_
# define TERRAIN_HPP_

# include "glheader.hpp"
# include <string>
# include <vector>
# include <math.h>
# include "Node.hpp"

#define INDEX(x, y) ((((y) * _nbVertex) + (x)))

typedef struct
{
  float x, y, z;
} Vertex3;

  // static const GLfloat g_vertex_buffer_data[] = {
  //   -1.0f, -1.0f, 0.0f,
  //   1.0f, -1.0f, 0.0f,
  //   0.0f,  1.0f, 0.0f,
  // };

struct BVertex
{
  float x, y, z;        //Vertex
  float nx, ny, nz;     //Normal
  float s0, t0;         //Texcoord0
};

class Terrain : public Geode
{

protected:

  std::vector<Vertex3> _pts;
  std::vector<Vertex3> _normalMap;
  std::vector<unsigned> _indices;
  std::vector<Vertex3> p_pts;
  std::vector<Vertex3> p_normalMap;
  std::vector<unsigned> p_indices;
  
  std::vector<BVertex> data;
  
  int _sizeX;
  int _sizeY;
  int _nbVertex;

  GLuint _VBODT;
  GLuint _VBOID;

public:
  Terrain(int sizeX, int sizeY, int factor):
    _sizeX(sizeX),
    _sizeY(sizeY)
  {
    _nbVertex = (int)pow(2, factor) + 1;

    initTerrain();
    glGenBuffers(1, &_VBODT);
    glBindBuffer(GL_ARRAY_BUFFER, _VBODT);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BVertex) * _pts.size(), &data[0].x, GL_STATIC_DRAW);
    
    glGenBuffers(1, &_VBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*_indices.size(), &_indices[0], GL_STATIC_DRAW);
    
  }

  virtual ~Terrain();

  void initIndiceTable(void);
  bool isInMap(int x, int y);
  float averageSquare(int x, int y, int size);
  float averageDiamon(int x, int y, int size);
  void square(int x1, int x2, int y1, int y2,
	      int stepX, int stepY, int randMod);
  void diamons(int x1, int x2, int y1, int y2, int stepX, int randMod);
  void diamondSquare(int x1, int x2, int y1, int y2);
  void initNormalMap(int max);
  void initTerrain(int seed = 0);
  virtual void draw();
  void ppMap(void);
  void generate();
  
};

#endif
