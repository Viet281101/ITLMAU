#version 330

in vec4 mpos;
in vec3 N;

out vec4 fragColor;

uniform vec4  scolor;
uniform vec4  lum0color;
uniform vec4  lum0pos;
uniform mat4  view;
uniform vec3  vpos;
uniform float lum0dmax;

/* dispatch ambient, diffus (le diffus est (1 - ambient)) et spéculaire en dur */
const float ambient_factor = 0.25, specular_factor = 0.4;
/* vitesse d'atténuation, mettre entre 0.5 et 2.0 (1.0 == linéaire) */
const float lum0_attenuation_power = 1.7;

void main() {
  vec3  n   = normalize(N);
  vec3  Ld  = normalize(mpos.xyz - lum0pos.xyz);
  float ild = clamp(dot(n, -Ld), 0.0, 1.0);
  vec3  R   = reflect(Ld, n);
  vec3  Vue = -normalize(vpos - mpos.xyz);
  float ils = pow(clamp(dot(R, -Vue), 0.0, 1.0), 100.0);
  
  vec4 ambient  = ambient_factor               * lum0color * scolor; 
  vec4 diffuse  = (1.0 - ambient_factor) * ild * lum0color * scolor; 
  vec4 specular = specular_factor        * ils * lum0color * vec4(1.0); /* le reflet de la surface est blanc */ 

  float attenuation = 1.0;

  /* ajout de l'atténuation (à commenter si vous n'en voulez pas) */
  float d = length(mpos.xyz - lum0pos.xyz);
  attenuation = pow(max(lum0dmax - d, 0.0) / lum0dmax, lum0_attenuation_power);
  /* fin de l'atténuation */
  
  fragColor = attenuation * (ambient + diffuse + specular);
}
