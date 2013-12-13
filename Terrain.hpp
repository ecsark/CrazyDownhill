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
  int _seed;
  int _randMod;
  int _factor;

public:
  Terrain(const std::string &name, int sizeX, int sizeY, int factor, float smoothFactor = 1.f, int seed = 3):
    Geode(name, true, false),
  _sizeX(sizeX),
  _sizeY(sizeY),
    _smoothFactor(smoothFactor),
    _seed(seed),
    _factor(factor)
  {
    _nbVertex = (int)pow(2, factor) + 1;
    _randMod = _nbVertex * 10000;
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
  void regenerate(int seed = 0);
  void setSmoothFactor(float f) {_smoothFactor = f;}
  float getSmoothFactor(void) {return _smoothFactor;}
  void setRandmod(float f) {_randMod = f;}
  float getRandmod(void) {return _randMod;}
  void setFactor(int f) {_factor = f; _nbVertex = (int)pow(2, f) + 1; initTerrain(); initBuffers();}
  int getFactor(void) {return _factor;}
};

#endif
