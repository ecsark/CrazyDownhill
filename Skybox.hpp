
#ifndef SKYBOX_HPP_
# define SKYBOX_HPP_

# include <vector>
# include "glheader.hpp"
# include "BmpLoader.hpp"
# include "GLSLShader.hpp"

struct texture
{
  std::vector<unsigned int> data;
  unsigned int width;
  unsigned int height;
};

class Skybox
{
  BmpLoader _loader;
  std::vector<struct texture> _textures;
  // std::vector<unsigned int> _texture;
  // unsigned int _width;
  // unsigned int _height;
  // GLuint _VBO;
  // GLuint _VAO;
  GLuint _indices;
  GLuint _vertices;
  GLuint _TEXID;
  GLSLShader _shader;
  
  enum Face
    {
      POSX = 0,
      NEGX,
      POSY,
      NEGY,
      POSZ,
      NEGZ,
      END_FACE
    };

public:
  Skybox() {}
  virtual ~Skybox(){}

  void initBuffer(void);
  void loadTexture(const std::string &path, enum Face face);
  void loadSkybox(void);
  void draw(void);
};

#endif
