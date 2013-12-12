#version 120

varying vec2 texcoords;
uniform samplerCube Cubetexture;
// out vec4 frag_colour;

void main () {
  gl_FragColor = vec4(1,1,1,1);// texture(texturecube_texture, texcoords);
}
