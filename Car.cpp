
#include "Car.hpp"

void Car::loadCabin(int nVertices, float *vertices, float *normals,
		    float *texcoords, int nIndices, int *indices,
		    const std::string &vertShader, const std::string &fragShader)
{
  Cabin *element = new Cabin;
  nodeList[Element::CABIN] = element;
  // element = dynamic_cast<Geode*>(nodeList[Element::CABIN]);
  if (element)
    {
      element->loadMesh(nVertices, vertices, normals,
			texcoords, nIndices, indices);
      element->loadShaders(vertShader, fragShader);
      element->initBuffers();
    }
}

void Car::addWheel(enum Element wheelNumber, int nVertices, float *vertices,
		   float *normals, float *texcoords, int nIndices,
		   int *indices, const std::string &vertShader,
		   const std::string &fragShader)
{
  if (wheelNumber == Element::CABIN || wheelNumber >= Element::END_ELEMENT)
    return;
  Wheel *element = new Wheel;
  nodeList[wheelNumber] = element;
  // element = dynamic_cast<Geode*>(nodeList[wheelNumber]);
  if (element) 
    {
      element->loadMesh(nVertices, vertices, normals,
			texcoords, nIndices, indices);
      element->loadShaders(vertShader, fragShader);
      element->initBuffers();
    }
}
