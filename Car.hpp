
#ifndef CAR_HPP_
# define CAR_HPP_

# include "glheader.hpp"
# include "Node.hpp"

class Wheel : public Geode
{
private:

public:

  Wheel() {}
  virtual ~Wheel(){}
};

class Cabin : public Geode
{
private:

public:

  Cabin() {}
  virtual ~Cabin () {}
  
  // void loadCabin(int nVertices, float *vertices, float *normals,
  // 		      float *texcoords, int nIndices, int *indices);
};

class Car : public Group
{
private:

public:

  enum Element
    {
      CABIN = 0,
      WHEEL_FRONTLEFT,
      WHEEL_FRONTRIGHT,
      WHEEL_BACKLEFT,
      WHEEL_BACKRIGHT,
      END_ELEMENT
    };

  Car(){
    nodeList.resize(Element::END_ELEMENT);
  }
  virtual ~Car() {}

  void loadCabin(int nVertices, float *vertices, float *normals,
		 float *texcoords, int nIndices, int *indices,
		 const std::string &vertShader, const std::string &fragShader);
  void addWheel(enum Element wheelNumber, int nVertices, float *vertices,
		float *normals, float *texcoords, int nIndices,
		int *indices, const std::string &vertShader, const std::string &fragShader);
};

#endif
