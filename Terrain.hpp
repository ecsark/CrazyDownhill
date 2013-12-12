#ifndef TERRAIN_HPP_
# define TERRAIN_HPP_

# include "glheader.hpp"
# include <string>
# include <vector>
# include <math.h>
# include "Node.hpp"

#define INDEX(x, y) ((((y) * _nbVertex) + (x)))

class Geode;

class Terrain : public Geode
{
  friend class TerrainPhysics;
protected:

  std::vector<Vector3> _pts;
  std::vector<Vector3> _normalMap;
  // std::vector<Vertex3> p_pts;
  // std::vector<Vertex3> p_normalMap;
  // std::vector<unsigned> p_indices;
  
  
  int _sizeX;
  int _sizeY;
  int _nbVertex;
  float _smoothFactor;

public:
  Terrain(int sizeX, int sizeY, int factor, float smoothFactor = 1.f):
  _sizeX(sizeX),
  _sizeY(sizeY),
  _smoothFactor(smoothFactor)
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
  // virtual void draw();
  void ppMap(void);
  void generate();
  
};

#endif
