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

class Terrain : public Geode
{

protected:

  std::vector<Vertex3> _pts;
  std::vector<Vertex3> _normalMap;
  // std::vector<Vertex3> p_pts;
  // std::vector<Vertex3> p_normalMap;
  // std::vector<unsigned> p_indices;
  
  
  int _sizeX;
  int _sizeY;
  int _nbVertex;


public:
  Terrain(int sizeX, int sizeY, int factor):
    _sizeX(sizeX),
    _sizeY(sizeY)
  {
    _nbVertex = (int)pow(2, factor) + 1;

    initTerrain();
    initBuffers();
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
