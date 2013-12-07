varying vec4 diffuse,ambientGlobal, ambient, ecPos;
varying vec3 normal,halfVector;
varying float dist;


void main()
{
    vec3 n,halfV,viewV,lightDir;
    float NdotL,NdotHV;
    vec4 color = ambientGlobal;
    float att, dist,spotEffect;
    
    /* a fragment shader can't write a verying variable, hence we need
     a new variable to store the normalized interpolated normal */
    n = normalize(normal);
    
    // Compute the ligt direction
    lightDir = vec3(gl_LightSource[2].position-ecPos);
    
    /* compute the distance to the light source to a varying variable*/
    dist = length(lightDir);
    
    /* compute the dot product between normal and ldir */
    NdotL = max(dot(n,normalize(lightDir)),0.0);
    
    if (NdotL > 0.0) {
        
        spotEffect = dot(normalize(gl_LightSource[2].spotDirection), normalize(-lightDir));
        if (spotEffect > gl_LightSource[2].spotCosCutoff) {
            spotEffect = pow(spotEffect, gl_LightSource[2].spotExponent);
            att = spotEffect / (gl_LightSource[2].constantAttenuation +
                                gl_LightSource[2].linearAttenuation * dist +
                                gl_LightSource[2].quadraticAttenuation * dist * dist);
            vec4 tmp = vec4(0,1,0,1);
            color += att * (diffuse * NdotL + ambient);
            //color += att * (tmp * NdotL + ambient);
            
            halfV = normalize(halfVector);
            NdotHV = max(dot(n,halfV),0.0);
            color += att * gl_FrontMaterial.specular * gl_LightSource[2].specular * pow(NdotHV,gl_FrontMaterial.shininess);
            
        }
    }
    
    gl_FragColor = color;
}