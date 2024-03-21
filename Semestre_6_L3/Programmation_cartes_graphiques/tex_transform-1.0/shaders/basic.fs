#version 330
in  vec2 vsoTexCoord;
/* sortie du frament shader : une couleur */
out vec4 fragColor;

uniform sampler2D tex;

void main(void) {
  fragColor = 0.999 * texture(tex, vsoTexCoord);
}
