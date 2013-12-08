
#include "Terrain.hpp"

// void Terrain::initIndiceTable()
// {
// }

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
      sum += _pts[INDEX(x - size, y - size)].y;
      n++;
    }
  if (isInMap(x - size, y + size))
    {
      sum += _pts[INDEX(x - size, y + size)].y;
      n++;
    }
  if (isInMap(x + size, y - size))
    {
      sum += _pts[INDEX(x + size, y - size)].y;
      n++;
    }
  if (isInMap(x + size, y + size))
    {
      sum += _pts[INDEX(x + size, y + size)].y;
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
      sum += _pts[INDEX(x, y - size)].y;
      n++;
    }
  if (isInMap(x, y + size))
    {
      sum += _pts[INDEX(x, y + size)].y;
      n++;
    }
  if (isInMap(x - size, y))
    {
      sum += _pts[INDEX(x - size, y)].y;
      n++;
    }
  if (isInMap(x + size, y))
    {
      sum += _pts[INDEX(x + size, y)].y;
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
	_pts[INDEX(j, i)].y = average + (((float)((float)(rand() % (randMod * 2)) - randMod)) / 10000.f);
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
	  _pts[INDEX(j, i)].y = average + (((float)((float)(rand() % (randMod * 2)) - randMod)) / 10000.f);
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
  Vector3 tmp1;
  Vector3 tmp;

  // FIXME : check what is the normal of the edge
  for (; i < max - 1; ++i)
    for (j = 0; j < max - 1; ++j)
      {
	tmp.set(_pts[INDEX(j, i)].x, _pts[INDEX(j, i)].y, _pts[INDEX(j, i)].z);
	tmp1.set(_pts[INDEX(j, i+1)].x, _pts[INDEX(j, i+1)].y, _pts[INDEX(j, i+1)].z);
	n = tmp1 - tmp;
	tmp1.set(_pts[INDEX(j + 1, i)].x, _pts[INDEX(j + 1, i)].y, _pts[INDEX(j + 1, i)].z);
	n = n.cross(tmp1 - tmp);
	// n = (_pts[INDEX(j, i+1)] - _pts[INDEX(j, i)]).cross(_pts[INDEX(j + 1, i)] - _pts[INDEX(j, i)]);
	n.normalize();
	_normalMap[INDEX(j, i)].x = n[0];
	_normalMap[INDEX(j, i)].y = n[1];
	_normalMap[INDEX(j, i)].z = n[2];
      }
}

void Terrain::initTerrain(int seed)
{
  srand(seed);

  _normalMap.resize(_nbVertex * _nbVertex);
  _pts.resize(_nbVertex * _nbVertex);
  _pts.front().x = 0;
  _pts.front().y = 0;
  _pts.front().z = 0;

  _pts.back().x = _nbVertex;
  _pts.back().y = 0;
  _pts.back().z = _nbVertex;
  int i = 0;
  int j;
  for (; i < _nbVertex; ++i)
    for(j = 0; j < _nbVertex; ++j)
      {
	_pts[i * _nbVertex + j].x = j;
	_pts[i * _nbVertex + j].y = 0;
	_pts[i * _nbVertex + j].z = i;
      }
  int modRand = _nbVertex * 10000;
  _pts[0].y = ((float)(rand() % modRand)) / 10000.f;
  _pts[_nbVertex * _nbVertex - 1].y = ((float)(rand() % modRand)) / 10000.f;
  _pts[(_nbVertex - 1) * _nbVertex ].y = ((float)(rand() % modRand)) / 10000.f;
  _pts[_nbVertex - 1].y = ((float)(rand() % modRand)) / 10000.f;
  // ppMap();
  diamondSquare(0, _nbVertex, 0, _nbVertex);
  initNormalMap(_nbVertex);

  // _pts.resize(3);
  // _pts[0].x = -1.0f;
  // _pts[0].y =  -1.0f;
  // _pts[0].z = 0;

  // _pts[1].x = 1.0f;
  // _pts[1].y = -1.0f;
  // _pts[1].z = 0;

  // _pts[2].x = 0;
  // _pts[2].y = 1;
  // _pts[2].z = 0;

}

void Terrain::draw()
{
  // int x = 0;
  // int y = 0;

  _shader.Use();

  GLuint vertexID = glGetAttribLocation(_shader.GetProgram(), "vertexPosition");
  glEnableVertexAttribArray(vertexID);

  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glVertexAttribPointer(_shader["vertexPosition"], 3, GL_FLOAT, GL_FALSE, 0, 0);
  glDrawArrays(GL_POINTS, 0, _pts.size());
  // glBegin(GL_POINTS);
  // for (; y < _nbVertex - 1 && 0; ++y)
  //   {
  //     for (x = 0; x < _nbVertex - 1; ++x)
  // 	{
  // 	  glColor3f(1, 1, 1);
  // 	  glNormal3f(_normalMap[INDEX(x, y)].x,
  // 		     _normalMap[INDEX(x, y)].y,
  // 		     _normalMap[INDEX(x, y)].z);
  // 	  glVertex3f(_pts[INDEX(x, y)].x,
  // 		     _pts[INDEX(x, y)].y,
  // 		     _pts[INDEX(x, y)].z);


  // 	  glNormal3f(_normalMap[INDEX(x + 1, y)].x,
  // 		     _normalMap[INDEX(x + 1, y)].y,
  // 		     _normalMap[INDEX(x + 1, y)].z);
  // 	  glVertex3f(_pts[INDEX(x + 1, y)].x,
  // 		     _pts[INDEX(x + 1, y)].y,
  // 		     _pts[INDEX(x + 1, y)].z);


  // 	  glNormal3f(_normalMap[INDEX(x + 1, y + 1)].x,
  // 		     _normalMap[INDEX(x + 1, y + 1)].y,
  // 		     _normalMap[INDEX(x + 1, y + 1)].z);
  // 	  glVertex3f(_pts[INDEX(x + 1, y + 1)].x,
  // 		     _pts[INDEX(x + 1, y + 1)].y,
  // 		     _pts[INDEX(x + 1, y + 1)].z);


  // 	  glNormal3f(_normalMap[INDEX(x, y + 1)].x,
  // 		     _normalMap[INDEX(x, y + 1)].y,
  // 		     _normalMap[INDEX(x, y + 1)].z);
  // 	  glVertex3f(_pts[INDEX(x, y + 1)].x,
  // 		     _pts[INDEX(x, y + 1)].y,
  // 		     _pts[INDEX(x, y + 1)].z);
  // 	}
  //   }
  // glEnd();
  _shader.UnUse();
}


void Terrain::ppMap(void)
{
  int i = 0;
  int j;

  for (; i < _nbVertex; ++i)
    {
      for (j = 0; j < _nbVertex; ++j)
	std::cout << _pts[INDEX(j, i)].y << "\t|";
      std::cout << std::endl;
    }
  std::cout << "======================================================" << std::endl;

}
