#version 330

uniform int time;

in vec2 vsoTexCoord;
out vec4 FragColor;

void main(void) {  
  float g = mod(vsoTexCoord.y + time, cos(vsoTexCoord.x * time * 100.0));
  FragColor = vec4(0.0, g, 0.0, 0.0);
}




