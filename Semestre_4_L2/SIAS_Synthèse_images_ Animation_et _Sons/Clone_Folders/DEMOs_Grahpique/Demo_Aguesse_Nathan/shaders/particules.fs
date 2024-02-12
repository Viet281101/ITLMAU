#version 330
out vec4 fragColor;

in float il;

uniform vec4 color;
uniform int use_Ld;

void main() {
  if (use_Ld == 1) {
    fragColor = (color * il * 0.9) + (color * 0.1);
  }
  else
    fragColor = color;
}
