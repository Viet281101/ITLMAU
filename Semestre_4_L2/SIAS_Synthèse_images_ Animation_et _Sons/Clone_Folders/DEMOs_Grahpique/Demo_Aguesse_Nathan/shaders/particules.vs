#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out float il;
uniform mat4 proj, model, view;
uniform vec3 ld;
uniform int use_Ld;

void main() {
  vec4 mpos = model * vec4(pos, 1.0);
  gl_Position = proj * view * mpos;
  if (use_Ld == 1) {
    vec3 Ld = normalize(ld);
    vec3 n = normalize(transpose(inverse(view)) * vec4(normal, 0.0)).xyz;
    il = abs(dot(n, -Ld));
  }
}
