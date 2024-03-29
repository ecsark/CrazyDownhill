#version 120

attribute vec3 vertexPosition;
attribute vec3 norm;
attribute vec2 textCoord;

varying vec3 outNorm;
varying vec3 texCoord;
varying vec3 lightDir;
varying vec3 vpos;

uniform mat4 vertexPosition_modelspace;
uniform mat4x4 MVP;

void main(){

  lightDir = normalize(vec3(gl_LightSource[0].position));
  outNorm = normalize(gl_NormalMatrix * norm);

  gl_FrontColor = gl_Color;
  vpos = vertexPosition;
  gl_Position =  gl_ModelViewProjectionMatrix * vec4(vertexPosition, 1.0);
  // gl_Position = vec4(1, 1, 1, 1.0);
  // gl_Position =  gl_Vertex * gl_ModelViewProjectionMatrix;
  // gl_Position = gl_ModelViewProjectionMatrix * vec4(1,1,1,1);
}
