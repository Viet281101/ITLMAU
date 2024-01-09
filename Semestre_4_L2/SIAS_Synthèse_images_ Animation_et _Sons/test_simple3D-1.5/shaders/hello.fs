#version 330
out vec4 fragColor;
in float il;
in vec2 vsoTexCoord;
uniform vec4 couleur;
uniform int use_texture;
uniform sampler2D tex;

void main() {
  if(use_texture != 0)
    fragColor = il * couleur * texture(tex, vsoTexCoord);
  else
    fragColor = il * couleur;
}
