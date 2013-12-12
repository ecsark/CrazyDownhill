
#include "glheader.hpp"
#include "Skybox.hpp"

union color
{
  unsigned int color;
  unsigned char byte[4];
};

  GLfloat cube_vertices[] = {
    -10.0,  10.0,  10.0,
    -10.0, -10.0,  10.0,
    10.0, -10.0,  10.0,
    10.0,  10.0,  10.0,
    -10.0,  10.0, -10.0,
    -10.0, -10.0, -10.0,
    10.0, -10.0, -10.0,
    10.0,  10.0, -10.0,
  };  GLushort cube_indices[] = {
    0, 1, 2, 3,
    3, 2, 6, 7,
    7, 6, 5, 4,
    4, 5, 1, 0,
    0, 3, 7, 4,
    1, 2, 6, 5,
  };


void Skybox::initBuffer(void)
{
  // float points[] = {
  //   -10.0f,  10.0f, -10.0f,
  //   -10.0f, -10.0f, -10.0f,
  //   10.0f, -10.0f, -10.0f,
  //   10.0f, -10.0f, -10.0f,
  //   10.0f,  10.0f, -10.0f,
  //   -10.0f,  10.0f, -10.0f,
  
  //   -10.0f, -10.0f,  10.0f,
  //   -10.0f, -10.0f, -10.0f,
  //   -10.0f,  10.0f, -10.0f,
  //   -10.0f,  10.0f, -10.0f,
  //   -10.0f,  10.0f,  10.0f,
  //   -10.0f, -10.0f,  10.0f,
  
  //   10.0f, -10.0f, -10.0f,
  //   10.0f, -10.0f,  10.0f,
  //   10.0f,  10.0f,  10.0f,
  //   10.0f,  10.0f,  10.0f,
  //   10.0f,  10.0f, -10.0f,
  //   10.0f, -10.0f, -10.0f,
   
  //   -10.0f, -10.0f,  10.0f,
  //   -10.0f,  10.0f,  10.0f,
  //   10.0f,  10.0f,  10.0f,
  //   10.0f,  10.0f,  10.0f,
  //   10.0f, -10.0f,  10.0f,
  //   -10.0f, -10.0f,  10.0f,
  
  //   -10.0f,  10.0f, -10.0f,
  //   10.0f,  10.0f, -10.0f,
  //   10.0f,  10.0f,  10.0f,
  //   10.0f,  10.0f,  10.0f,
  //   -10.0f,  10.0f,  10.0f,
  //   -10.0f,  10.0f, -10.0f,
  
  //   -10.0f, -10.0f, -10.0f,
  //   -10.0f, -10.0f,  10.0f,
  //   10.0f, -10.0f, -10.0f,
  //   10.0f, -10.0f, -10.0f,
  //   -10.0f, -10.0f,  10.0f,
  //   10.0f, -10.0f,  10.0f
  // };
  
  // glGenBuffers (1, &_VBO);
  // glBindBuffer (GL_ARRAY_BUFFER, _VBO);
  // glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof (float), &points, GL_STATIC_DRAW);

  // glGenVertexArrays (1, &_VAO);
  // glBindVertexArray (_VAO);
 
  // glEnableVertexAttribArray(0);
  // glBindBuffer (GL_ARRAY_BUFFER, _VBO);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
  // _shader.LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");

  // glGenTextures(1, &_TEXID);
  // glBindTexture(GL_TEXTURE_2D, _TEXID);
  // glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(_texture[0]));

  // glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  // glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  // glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // glBindTexture( GL_TEXTURE_2D, 0); // unbind texture
  // GLenum error = glGetError();
  // if( error != GL_NO_ERROR )
  //   printf( "Error loading texture from %p pixels! %s\n", &(_texture[0]), gluErrorString( error ) );

  _shader.LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");
  glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_CUBE_MAP);
  glGenTextures(1, &_TEXID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _TEXID);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, _textures[POSX].width, _textures[POSX].width, 0,
	       GL_RGBA, GL_UNSIGNED_BYTE, &(_textures[POSX].data[0]));
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, _textures[NEGX].width, _textures[NEGX].width, 0,
	       GL_RGBA, GL_UNSIGNED_BYTE, &(_textures[NEGX].data[0]));
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, _textures[POSY].width, _textures[POSY].width, 0,
	       GL_RGBA, GL_UNSIGNED_BYTE, &(_textures[POSY].data[0]));
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, _textures[NEGY].width, _textures[NEGY].width, 0,
	       GL_RGBA, GL_UNSIGNED_BYTE, &(_textures[NEGY].data[0]));
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, _textures[POSZ].width, _textures[POSZ].width, 0,
	       GL_RGBA, GL_UNSIGNED_BYTE, &(_textures[POSZ].data[0]));
  glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, _textures[NEGZ].width, _textures[NEGZ].width, 0,
	       GL_RGBA, GL_UNSIGNED_BYTE, &(_textures[NEGZ].data[0]));

  // GLfloat cube_vertices[] = {
  //   -1.0,  1.0,  1.0,
  //   -1.0, -1.0,  1.0,
  //   1.0, -1.0,  1.0,
  //   1.0,  1.0,  1.0,
  //   -1.0,  1.0, -1.0,
  //   -1.0, -1.0, -1.0,
  //   1.0, -1.0, -1.0,
  //   1.0,  1.0, -1.0,
  // };
  glGenBuffers(1, &_vertices);
  glBindBuffer(GL_ARRAY_BUFFER, _vertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
  //glBindBuffer(GL_ARRAY_BUFFER, 0);
 
  // cube indices for index buffer object
  // GLushort cube_indices[] = {
  //   0, 1, 2, 3,
  //   3, 2, 6, 7,
  //   7, 6, 5, 4,
  //   4, 5, 1, 0,
  //   0, 3, 7, 4,
  //   1, 2, 6, 5,
  // };
  glGenBuffers(1, &_indices);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indices);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Skybox::draw()
{
  // glm::mat4 Projection = glm::perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f); 
  // glm::mat4 View       = glm::mat4(1.0f);
  // glm::mat4 Model      = glm::scale(glm::mat4(1.0f),glm::vec3(50,50,50));
  glBindBuffer(GL_ARRAY_BUFFER, _vertices);
  // GLint PVM    = glGetUniformLocation(_shader.GetProgram(), "PVM");
  GLuint vertex = glGetAttribLocation(_shader.GetProgram(), "vp");
  // std::cout << vertex << std::endl;

  glEnableVertexAttribArray(vertex);
  glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, sizeof(cube_vertices), 0);
  glDrawElements(GL_QUADS, sizeof(cube_indices)/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
  // glEnableClientState(GL_VERTEX_ARRAY);
  // glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  // glDepthMask (GL_FALSE);
  // _shader.Use();
  //  // glUseProgram (_shader.GetProgram());
  // // glActiveTexture (GL_TEXTURE0);
  // glBindTexture (GL_TEXTURE_CUBE_MAP, _TEXID);
  // glBindVertexArray (_VBO);
  // glEnableClientState( GL_VERTEX_ARRAY );
  // // glDrawArrays (GL_TRIANGLES, 0, 36);

  // glDisableClientState( GL_VERTEX_ARRAY );
  // _shader.UnUse();
  // // glUnuseProgram(_shader.GetProgram());
  // glDepthMask (GL_TRUE);
}

void Skybox::loadTexture(const std::string &path, enum Face face)
{
  unsigned int i;
  unsigned int j;
  union color c;
  unsigned char *data = _loader.getBmpData(path);
  struct texture tex;

  if (!data)
    return;
  tex.width = _loader.getWidth();
  tex.height = _loader.getHeight();
  tex.data.resize(tex.width * tex.height);
  for (i = 0; i < tex.height; ++i)
    for (j = 0; j < tex.width; ++j)
      {
	c.byte[0] = data[i * tex.width + j];
	c.byte[1] = data[i * tex.width + j + 1];
	c.byte[2] = data[i * tex.width + j + 2];
	c.byte[3] = data[i * tex.width + j + 3];
	tex.data[(i * tex.width + j)] = c.color;
      }
  _textures[face] = tex;
  _loader.deleteData();
}

void Skybox::loadSkybox(void)
{
  _textures.resize(Face::END_FACE);
  loadTexture("img/frontav9.bmp", POSZ);
  loadTexture("img/leftav9.bmp", NEGX);
  loadTexture("img/rightav9.bmp", POSX);
  loadTexture("img/topav9.bmp", POSY);
  loadTexture("img/backav9.bmp", NEGZ);
  loadTexture("img/backav9.bmp", NEGY);
  initBuffer();
}
