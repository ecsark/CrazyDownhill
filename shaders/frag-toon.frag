#version 120

uniform mat4x4 MVP;
uniform vec3 EyePos;
varying vec3 outNorm, lightDir, vpos;

void main()
{
  float intensity;
  intensity = dot(lightDir,normalize(outNorm));
  float factor;
  
  if (intensity > 0.80)
    factor = 1;
  else if (intensity > 0.5)
    factor = 0.5;
  else if (intensity > 0.25)
    factor = 0.2;
  else
    factor = 0.1;
  gl_FragColor = gl_Color * gl_LightSource[0].diffuse * factor *gl_FrontMaterial.diffuse;
  if (dot(EyePos, outNorm) < 0.1)
    gl_FragColor *= 0;
}
