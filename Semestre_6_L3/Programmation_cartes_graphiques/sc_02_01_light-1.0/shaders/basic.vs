/*!\file basic.vs
 *
 * \brief vertex shader basique
  */

/* Version GLSL 3.30 */
#version 330

layout (location = 0) in vec3 vsiPosition;
layout (location = 1) in vec3 vsiNormal;
layout (location = 2) in vec2 vsiTexCoord;

/* une sortie du vertex shader vers le fragment shader (voir basic.fs, in vec2 vsoColor) */
out vec4 vsoColor;

uniform mat4 projectionMatrix, viewMatrix, modelMatrix;

uniform float temps;

vec3 Lp = vec3(0.5, 2.0, 2.0);

void main(void) {
  Lp.z += cos(temps);
  /* gl_Position, nom réservé produisant un sommet GL */
  /* l'entrée vsiPosition est complétée en vecteur 4D (x, y, z, w) où
   * w = 1.0 ; elle est multipliée à gauche par une matrice de
   * modélisation puis vue puis projection (lire de droite à gauche à
   * partir du sommet) */
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vsiPosition, 1.0);
  /* la couleur en sortie du vertex shader vers le fragment shader, vsoColor est un vecteur 4D (w = 1) alors que la couleur reçu est 3D */

  vec3 Ld = normalize(vsiPosition - Lp);
  float intensiteDeLumiereDiffuse = clamp(dot(vsiNormal, -Ld), 0.0, 1.0);
  vsoColor = intensiteDeLumiereDiffuse * vec4(1.0);
}
