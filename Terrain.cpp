
#include "Terrain.hpp"

bool Terrain::isInMap(int x, int y)
{
  return (x < _nbVertex && x >= 0 && y < _nbVertex && y >= 0);
}

float Terrain::averageSquare(int x, int y, int size)
{
  float n = 0;
  float sum = 0;

  if (isInMap(x - size, y - size))
    {
      sum += _pts[INDEX(x - size, y - size)][1];
      n++;
    }
  if (isInMap(x - size, y + size))
    {
      sum += _pts[INDEX(x - size, y + size)][1];
      n++;
    }
  if (isInMap(x + size, y - size))
    {
      sum += _pts[INDEX(x + size, y - size)][1];
      n++;
    }
  if (isInMap(x + size, y + size))
    {
      sum += _pts[INDEX(x + size, y + size)][1];
      n++;
    }
  return n != 0 ? sum / n : 0;
}

float Terrain::averageDiamon(int x, int y, int size)
{
  float n = 0;
  float sum = 0;

  if (isInMap(x, y - size))
    {
      sum += _pts[INDEX(x, y - size)][1];
      n++;
    }
  if (isInMap(x, y + size))
    {
      sum += _pts[INDEX(x, y + size)][1];
      n++;
    }
  if (isInMap(x - size, y))
    {
      sum += _pts[INDEX(x - size, y)][1];
      n++;
    }
  if (isInMap(x + size, y))
    {
      sum += _pts[INDEX(x + size, y)][1];
      n++;
    }
  return n != 0 ? sum / n : 0;
}

void Terrain::square(int x1, int x2, int y1, int y2,
		     int stepX, int stepY, int randMod)
{
  int i; 
  int j;
  int startY = (y1 + stepY / 2);
  int startX = (x1 + stepX / 2);
  int size = stepX / 2;
  float average;

  for (i = startY; i < y2; i += stepY)
    for (j = startX; j < x2; j += stepX)
      {
	average = averageSquare(j, i, size);
	_pts[INDEX(j, i)][1] = average + (((float)((float)(rand() % (randMod * 2)) - randMod)) / 10000.f);
      }
    
}

void Terrain::diamons(int x1, int x2, int y1, int y2,
		      int stepX, int randMod)
{
  int i; 
  int j;
  int startY = y1;
  int startX = (x1 + stepX / 2);
  int size = stepX / 2;
  float average;
  bool line = true;

  for (i = startY; i < y2; i += (line ?  size : size))
    {
      for ((line ? j = startX : j = x1); j < x2; j += size + size)
	{
	  if (line)
	    average = averageDiamon(j, i, size);
	  else
	    average = averageDiamon(j, i, size);
	  _pts[INDEX(j, i)][1] = average + (((float)((float)(rand() % (randMod * 2)) - randMod)) / 10000.f);
	}
      line = !line;
    }
}

void Terrain::diamondSquare(int x1, int x2, int y1, int y2)
{
  int sizeX = x2 - x1;
  int sizeY = y2 - y1;
  int randMod = 1000000;

  while (sizeX > 1 && sizeY > 1)
    {
      square(x1, x2, y1, y2, sizeX, sizeY, randMod);
      diamons(x1, x2, y1, y2, sizeX, randMod);
      sizeX /= 2;
      sizeY /= 2;
      randMod /= 2;
    }
}

void Terrain::initNormalMap(int max)
{
  int i = 0;
  int j;
  Vector3 n;

  // FIXME : check what is the normal of the edge
  for (; i < max - 1; ++i)
    for (j = 0; j < max - 1; ++j)
      {
	n = (_pts[INDEX(j, i+1)] - _pts[INDEX(j, i)]).cross(_pts[INDEX(j + 1, i)] - _pts[INDEX(j, i)]);
	n.normalize();
	_normalMap[INDEX(j, i)] = n;
      }
}

void Terrain::initTerrain(int seed)
{
  srand(seed);

  _normalMap.resize(_nbVertex * _nbVertex);
  _pts.resize(_nbVertex * _nbVertex);
  _pts.front()[0] = 0;
  _pts.front()[1] = 0;
  _pts.front()[2] = 0;

  _pts.back()[0] = _nbVertex;
  _pts.back()[1] = 0;
  _pts.back()[2] = _nbVertex;
  int i = 0;
  int j;
  for (; i < _nbVertex; ++i)
    for(j = 0; j < _nbVertex; ++j)
      {
	_pts[i * _nbVertex + j][0] = j;
	_pts[i * _nbVertex + j][1] = 0;
	_pts[i * _nbVertex + j][2] = i;
      }
  int modRand = _nbVertex * 10000;
  _pts[0][1] = ((float)(rand() % modRand)) / 10000.f;
  _pts[_nbVertex * _nbVertex - 1][1] = ((float)(rand() % modRand)) / 10000.f;
  _pts[(_nbVertex - 1) * _nbVertex ][1] = ((float)(rand() % modRand)) / 10000.f;
  _pts[_nbVertex - 1][1] = ((float)(rand() % modRand)) / 10000.f;
  // ppMap();
  diamondSquare(0, _nbVertex, 0, _nbVertex);
  initNormalMap(_nbVertex);
}

void Terrain::draw()
{
  int x = 0;
  int y = 0;

  _shader.Use();
  // glBegin(GL_POINTS);
  glBegin(GL_QUADS);
  // glDrawArrays(GL_TRIANGLES, 0, 3);

  for (; y < _nbVertex - 1; ++y)
    {
      for (x = 0; x < _nbVertex - 1; ++x)
	{
	  glColor3f(1, 1, 1);
	  glNormal3f(_normalMap[INDEX(x, y)][0],
		     _normalMap[INDEX(x, y)][1],
		     _normalMap[INDEX(x, y)][2]);
	  glVertex3f(_pts[INDEX(x, y)][0],
		     _pts[INDEX(x, y)][1],
		     _pts[INDEX(x, y)][2]);


	  glNormal3f(_normalMap[INDEX(x + 1, y)][0],
		     _normalMap[INDEX(x + 1, y)][1],
		     _normalMap[INDEX(x + 1, y)][2]);
	  glVertex3f(_pts[INDEX(x + 1, y)][0],
		     _pts[INDEX(x + 1, y)][1],
		     _pts[INDEX(x + 1, y)][2]);


	  glNormal3f(_normalMap[INDEX(x + 1, y + 1)][0],
		     _normalMap[INDEX(x + 1, y + 1)][1],
		     _normalMap[INDEX(x + 1, y + 1)][2]);
	  glVertex3f(_pts[INDEX(x + 1, y + 1)][0],
		     _pts[INDEX(x + 1, y + 1)][1],
		     _pts[INDEX(x + 1, y + 1)][2]);


	  glNormal3f(_normalMap[INDEX(x, y + 1)][0],
		     _normalMap[INDEX(x, y + 1)][1],
		     _normalMap[INDEX(x, y + 1)][2]);
	  glVertex3f(_pts[INDEX(x, y + 1)][0],
		     _pts[INDEX(x, y + 1)][1],
		     _pts[INDEX(x, y + 1)][2]);
	}
    }
  glEnd();
  _shader.UnUse();
}


void Terrain::ppMap(void)
{
  int i = 0;
  int j;

  for (; i < _nbVertex; ++i)
    {
      for (j = 0; j < _nbVertex; ++j)
	std::cout << _pts[INDEX(j, i)][1] << "\t|";
      std::cout << std::endl;
    }
  std::cout << "======================================================" << std::endl;

}
