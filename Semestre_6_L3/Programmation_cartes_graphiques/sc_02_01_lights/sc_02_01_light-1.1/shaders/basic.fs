/*!\file basic.fs
 *
 * \brief fragment shader basique qui applique une couleur.
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date January 20 2017
 */
/* Version GLSL 3.30 */
#version 330
in vec4 mp;
in vec4 mn;
/* sortie du frament shader : une couleur */
out vec4 fragColor;

vec3 Lp = vec3(0.0, 0.0, 2.1);

uniform float temps;

void main(void) {
  Lp.x += 1.0 * sin(temps);
  vec3 Ld = normalize(mp.xyz - Lp);
  float intensiteDeLumiereDiffuse = clamp(dot(normalize(mn.xyz), -Ld), 0.0, 1.0);
  vec4 color = intensiteDeLumiereDiffuse * vec4(1.0);
  /* la couleur de sortie est le vsoColor linéairement interpolé au
     fragment (voir attribut flat pour désactiver l'interpolation). */
  fragColor = color;
}
