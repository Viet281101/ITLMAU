#version 330

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

layout (location = 0) in vec3 vsiPosition;
layout (location = 1) in vec3 vsiNormal;
layout (location = 2) in vec2 vsiTexCoord;

out vec2 vsoTexCoord;
out vec3 vsoNormal;

void main(void) {
  vsoTexCoord = vsiTexCoord * 300;
  vsoNormal = (transpose(inverse(modelMatrix))  * vec4(vsiNormal, 0.0)).xyz;
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vsiPosition, 1.0);
}
