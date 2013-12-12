#ifndef PARTICLESYSTEM_HPP_
# define PARTICLESYSTEM_HPP_

# include <list>
# include "glheader.hpp"
# include "Node.hpp"
# include "Vectors.hpp"

typedef struct
{
  Vector3 pos;
  Vector3 Vel; //Velocity of the particle
  int age; //Current age of the particle
  int color;
  int size;

  virtual void update(void);
} particle;

class ParticleSystem : public Geode// alias emitter
{
private:

  typedef std::list<particle> ParticleList;
  unsigned _nbParticles;
  ParticleList _particles;
  int _lifeSpan; //Age after which the particle dies
  int _k;
  unsigned _size;
  unsigned _sizeParticle;

public:

  ParticleSystem(unsigned nbParticles = 3600, unsigned lifeSpan = 10000, unsigned sizeBox = 1000,
		 unsigned sizeParticle = 2):
    _nbParticles(nbParticles),
    _lifeSpan(lifeSpan),
    _size(sizeBox),
    _sizeParticle(sizeParticle)
  {
    data.resize(_nbParticles * 3);
    _indices.resize(_nbParticles * 3);
  }

  virtual void update(void);
  void initIndiceTable(void);
  void emitParticles(void);
  void checkParticles(void);
  bool isParticleInBox(particle &p);
};

#endif
