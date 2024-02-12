#version 330
in vec2 tcoord;
out vec4 fragColor;

uniform sampler2D tex;
uniform int use_tex;
uniform int use_white;

void main() {
  if (use_tex == 1) {
    vec4 c = texture(tex, tcoord);
    if(length(c.rgb) > 0.01)
      fragColor = c;
    else
      discard;
  }
  else if (use_white == 1) {
    fragColor = vec4(1.0, 1.0, 1.0, 1.0);
  }
  else {
    fragColor = vec4(0.0, 0.0, 0.0, 0.0);
  }
}
