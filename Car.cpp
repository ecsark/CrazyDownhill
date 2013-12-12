
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
  Transformation *t = new Transformation;
  t->attachNode(element);
  nodeList[wheelNumber] = t;
  // element = dynamic_cast<Geode*>(nodeList[wheelNumber]);
  element->loadMesh(nVertices, vertices, normals,
		    texcoords, nIndices, indices);
  element->loadShaders(vertShader, fragShader);
  element->initBuffers();

  if (wheelNumber == Element::WHEEL_FRONTLEFT)
    {
      t->kernel.rotateX_pre(180);
      t->kernel.move(0,-25,15);
    }
  else if (wheelNumber == Element::WHEEL_FRONTRIGHT)
    t->kernel.move(0,0,-5);
  if (wheelNumber == Element::WHEEL_BACKLEFT)
    {
      t->kernel.rotateX_pre(180);
      t->kernel.move(40,-25,15);
    }
  else if (wheelNumber == Element::WHEEL_BACKRIGHT)
    t->kernel.move(40,0,-5);
}
