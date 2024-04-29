#version 330

uniform int time;
uniform int coef;

in vec2 vsoTexCoord;
out vec4 FragColor;

void 
main() 
{
float t = time / 1000;
  
	float c1 = 1.0;
	float c2 = 1.0;
	float c3 = 1.0;
	
	c1 = sin( vsoTexCoord.x * cos(t / 100) * 15.0  * coef / 100) + 
	      cos(vsoTexCoord.y * cos(t / 1000) * 100.0) + 
	      cos( vsoTexCoord.y * sin(t / 100) * 50.0 );
	
	c2 = c1 * 0.25;
	c3 = cos(c1) * c1 * t;

	FragColor = vec4(vec3 (c1, c2, c3), 1.0);
}


