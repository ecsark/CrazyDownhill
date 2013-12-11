
#include "glheader.hpp"
#include "Skybox.hpp"

union color
{
  unsigned int color;
  unsigned char byte[4];
};

void Skybox::loadTexture(const std::string &path)
{
  unsigned int i;
  unsigned int j;
  union color c;
  unsigned char *data = _loader.getBmpData(path);
  if (!data)
    return;
  _width = _loader.getWidth();
  _height = _loader.getHeight();
  _texture.resize(_width * _height);
  for (i = 0; i < _height; ++i)
    for (j = 0; j < _width; ++j)
      {
	c.byte[0] = data[i * _width + j];
	c.byte[1] = data[i * _width + j + 1];
	c.byte[2] = data[i * _width + j + 2];
	c.byte[3] = data[i * _width + j + 3];
	_texture[(i * _width + j)] = c.color;
      }
}
