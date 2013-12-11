
#ifndef SKYBOX_HPP_
# define SKYBOX_HPP_

# include <vector>
# include "glheader.hpp"
# include "BmpLoader.hpp"

class Skybox
{
  BmpLoader _loader;
  std::vector<unsigned int> _texture;
  unsigned int _width;
  unsigned int _height;

public:
  Skybox():
    _width(0),
    _height(0)
  {
  }
  virtual ~Skybox();

  void loadTexture(const std::string &path);
};

#endif
