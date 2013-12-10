
#include "Car.hpp"

void Car::loadCabin(int nVertices, float *vertices, float *normals,
		    float *texcoords, int nIndices, int *indices)
{
  Geode *element;
  element = dynamic_cast<Geode*>(nodeList[Element::CABIN]);
  if (element) 
    element->loadMesh(nVertices, vertices, normals,
		      texcoords, nIndices, indices);
}

void Car::addWheel(enum Element wheelNumber, int nVertices, float *vertices,
		   float *normals, float *texcoords, int nIndices,
		   int *indices)
{
  if (wheelNumber == Element::CABIN || wheelNumber >= Element::END_ELEMENT)
    return;
  Geode *element;
  element = dynamic_cast<Geode*>(nodeList[wheelNumber]);
  if (element) 
    element->loadMesh(nVertices, vertices, normals,
		      texcoords, nIndices, indices);
}
