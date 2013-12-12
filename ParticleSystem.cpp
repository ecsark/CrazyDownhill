
#include "ParticleSystem.hpp"

void particle::update(void)
{
  Vel.y -= (float)(rand() % 100) / 100.f;
  pos += Vel ;
  // pos.x += (float)(rand() % 1000) / 1000.f - 0.5;
  // pos.y += (float)(rand() % 1000) / 1000.f - 0.5;
  // pos.z += (float)(rand() % 1000) / 1000.f - 0.5;
  // Vel.x -= Vel.x > 0 ? 0.01 : 0;
  // Vel.y -= Vel.y > 0 ? 0.01 : 0;
  // Vel.z -= Vel.z > 0 ? 0.01 : 0;
  // pos.y += (rand() % 5) - 5.5;
}

void ParticleSystem::initIndiceTable(void)
{
  unsigned i = 0;
  for (; i < data.size(); ++i)
      _indices[i] = i;
}

bool ParticleSystem::isParticleInBox(particle &p)
{
  return !(p.pos.x < 0 || p.pos.x > _size || p.pos.y < 0 || p.pos.y > _size || p.pos.z < 0 || p.pos.z > _size);
}

void ParticleSystem::checkParticles(void)
{
  ParticleList::iterator it = _particles.begin();
  ParticleList::iterator end = _particles.end();
  
  for (; it != end; ++it)
    {
      if (!isParticleInBox(*it))
	it = _particles.erase(it);
    }
}

void ParticleSystem::emitParticles(void)
{
  while (_particles.size() < _nbParticles)
    {
	particle p;
	p.Vel = Vector3(1,1,1);
	p.pos.x = rand() % _size;
	p.pos.y = rand() % _size;
	p.pos.z = rand() % _size;
	p.size = _sizeParticle;
	p.Vel.x = 0;
	p.Vel.y = -(rand() % 2);
	p.Vel.z = 0;
	_particles.push_back(p);
    }
}

void ParticleSystem::update(void)
{
  unsigned i = 0;
  
  checkParticles();
  emitParticles();

  ParticleList::iterator it = _particles.begin();
  ParticleList::iterator end = _particles.end();
  for (; it != end; ++it)
    {
      (*it).update();
      data[i].x = (*it).pos.x;
      data[i].y = (*it).pos.y;
      data[i].z = (*it).pos.z;
      ++i;

      data[i].x = (*it).pos.x;
      data[i].y = (*it).pos.y - (*it).size;
      data[i].z = (*it).pos.z;
      ++i;

      data[i].x = (*it).pos.x + (*it).size / 2.f;
      data[i].y = (*it).pos.y - (*it).size / 2.f;
      data[i].z = (*it).pos.z;

      data[i].nx = (*it).pos.x;
      data[i].ny = (*it).pos.y;
      data[i].nz = (*it).pos.z;
      ++i;
    }
  initIndiceTable();
  initBuffers();
}

