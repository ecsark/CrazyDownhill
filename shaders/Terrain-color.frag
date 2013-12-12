#version 120

uniform mat4x4 MVP;
varying vec3 outNorm, lightDir, vpos;

float rand(vec2 n)
{
  return 0.5 + 0.5 * 
    fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}

void main()
{
  gl_FragColor = gl_LightSource[0].diffuse * max(dot(outNorm, normalize(lightDir)),0.0) *gl_FrontMaterial.diffuse;

  vec4 color;
  color = vec4(0,0,0,1);
  if (vpos[1] + mod(rand(vpos.xz), 30) < 60)
    color = mix(vec4(0.2,0.3,0,1), vec4(0.30,0.10,0.04,1), vpos[1] / 60.f);
  else
    color = mix(vec4(0.30,0.10,0.04,1), vec4(1,1,1,1), (vpos[1] - 60.f) / 150.f);
  gl_FragColor *= color;
  gl_FragColor += 0.1;
}
