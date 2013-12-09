
#include "Terrain.hpp"

void Terrain::initIndiceTable(void)
{
  
  const unsigned int terrainWidth = _nbVertex;
  const unsigned int terrainHeight = _nbVertex;
  
  // 2 triangles for every quad of the terrain mesh
  const unsigned int numTriangles = ( terrainWidth - 1 ) * ( terrainHeight - 1 ) * 2;
  
  // 3 indices for each triangle in the terrain mesh
  _indices.resize( numTriangles * 3 );
  
  unsigned int index = 0; // Index in the index buffer
  for (unsigned int j = 0; j < (terrainHeight - 1); ++j )
  {
    for (unsigned int i = 0; i < (terrainWidth - 1); ++i )
    {
      int vertexIndex = ( j * terrainWidth ) + i;
      // Top triangle (T0)
      _indices[index++] = vertexIndex;                           // V0
      _indices[index++] = vertexIndex + terrainWidth + 1;        // V3
      _indices[index++] = vertexIndex + 1;                       // V1
      // Bottom triangle (T1)
      _indices[index++] = vertexIndex;                           // V0
      _indices[index++] = vertexIndex + terrainWidth;            // V2
      _indices[index++] = vertexIndex + terrainWidth + 1;        // V3
      
    }
  }
  
  // int i = 0;
  // int j;
  // GL_UNSIGNED_INT indice = 0;
  
  // _indices.resize(_nbVertex * _nbVertex);
  // for (; i < _nbVertex; ++i)
  //   for (j = 0; j < _nbVertex; ++j)
  //     {
  // 	_indices[i] = indice ;
	
  //     }
}

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

Vector3 calcNormal(Vertex3 _a, Vertex3 _b, Vertex3 _c) {
  Vector3 a(_a.x, _a.y, _a.z), b(_b.x, _b.y, _b.z), c(_c.x, _c.y, _c.z);
  Vector3 ab = b-a;
  Vector3 ac = c-a;
  Vector3 p = ab.cross(ac);
  p.normalize();
  return p;
}

void Terrain::initNormalMap(int max)
{
  int i = 1;
  int j;
  Vector3 n;
  Vector3 tmp1;
  Vector3 tmp;
  
  // FIXME : check what is the normal of the edge
  for (; i < max - 1; ++i)
    for (j = 1; j < max - 1; ++j)
    {
      Vector3 n1 = calcNormal(_pts[INDEX(j, i)], _pts[INDEX(j-1, i)], _pts[INDEX(j, i-1)]);
      Vector3 n2 = calcNormal(_pts[INDEX(j, i)], _pts[INDEX(j, i+1)], _pts[INDEX(j-1, i)]);
      Vector3 n3 = calcNormal(_pts[INDEX(j, i)], _pts[INDEX(j+1, i)], _pts[INDEX(j, i+1)]);
      Vector3 n4 = calcNormal(_pts[INDEX(j, i)], _pts[INDEX(j, i-1)], _pts[INDEX(j+1, i)]);
      /*
      tmp.set(_pts[INDEX(j, i)].x, _pts[INDEX(j, i)].y, _pts[INDEX(j, i)].z);
      tmp1.set(_pts[INDEX(j, i+1)].x, _pts[INDEX(j, i+1)].y, _pts[INDEX(j, i+1)].z);
      n = tmp1 - tmp;
      tmp1.set(_pts[INDEX(j + 1, i)].x, _pts[INDEX(j + 1, i)].y, _pts[INDEX(j + 1, i)].z);
      n = n.cross(tmp1 - tmp);
      // n = (_pts[INDEX(j, i+1)] - _pts[INDEX(j, i)]).cross(_pts[INDEX(j + 1, i)] - _pts[INDEX(j, i)]);
      n.normalize();
       */
      _normalMap[INDEX(j, i)].x = (n1.x+n2.x+n3.x+n4.x)/4;
      _normalMap[INDEX(j, i)].y = (n1.y+n2.y+n3.y+n4.y)/4;
      _normalMap[INDEX(j, i)].z = (n1.z+n2.z+n3.z+n4.z)/4;
      Vector3 vec((n1.x+n2.x+n3.x+n4.x)/4, (n1.y+n2.y+n3.y+n4.y)/4, (n1.z+n2.z+n3.z+n4.z)/4);
      vec.normalize();
      _normalMap[INDEX(j, i)].x = vec.x;
      _normalMap[INDEX(j, i)].y = vec.y;
      _normalMap[INDEX(j, i)].z = vec.z;
      
    }
  
  // FIXME: hack
  i = max - 1;
  for (j=0; j<max-1; ++j) {
    _normalMap[INDEX(j, i)].x = 0;
    _normalMap[INDEX(j, i)].y = 0;
    _normalMap[INDEX(j, i)].z = 1;
  }
  j = max - 1;
  for (i=0; i<=max-1; ++i) {
    _normalMap[INDEX(j, i)].x = 0;
    _normalMap[INDEX(j, i)].y = 0;
    _normalMap[INDEX(j, i)].z = 1;
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
  initIndiceTable();
  
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
  _shader.Use();
  
  GLuint vertexID = glGetAttribLocation(_shader.GetProgram(), "vertexPosition");
  glEnableVertexAttribArray(vertexID);
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  glVertexAttribPointer(_shader["vertexPosition"], 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, 3, BUFFER_OFFSET(0));
  
  glDrawElements(GL_TRIANGLES, int(_indices.size()), GL_UNSIGNED_INT, &(_indices[0]));
  
  glDisableClientState(GL_NORMAL_ARRAY);  _shader.UnUse();
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
