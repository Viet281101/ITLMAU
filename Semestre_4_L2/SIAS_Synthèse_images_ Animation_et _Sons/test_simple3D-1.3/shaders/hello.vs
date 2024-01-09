#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 proj;
uniform mat4 model;
uniform mat4 view;

out float il; /* intensité de lumière calculée par sommet */

const vec3 Ld = vec3(0.0, -0.707, -0.707); /* lumière directionnelle */

void main() {
  vec3 n = (transpose(inverse(model)) * vec4(normal, 0.0)).xyz;
  il = clamp(dot(n, -Ld), 0.0, 1.0);
  gl_Position = proj * view * model * vec4(pos, 1.0);
}
