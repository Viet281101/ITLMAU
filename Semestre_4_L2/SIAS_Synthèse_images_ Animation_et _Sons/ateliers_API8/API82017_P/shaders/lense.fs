#version 330

uniform int time;
uniform int coef;
uniform int resx;
uniform int resy;

in vec2 vsoTexCoord;
out vec4 FragColor;

vec2 res = vec2(resx, resy);

void 
main() 
{

	vec2 position = (gl_FragCoord.xy * 2 -  res) / min(res.x, res.y);
	vec3 destColor = vec3(0.0002, 0.06 , 0.005 );
	float f = 0.0;
	
	for(float i = 0.0; i < 111.0; i++){
		
		float u = 4 * -sin(0.01 * coef + i );
		float d = 4 * -cos(0.1 * coef + i ) * mod(coef / 0.5, 1);
		f += 0.2 / abs(length (1.5 * position * f - vec2(d, u)) - (0.0003 * mod(coef * 5, 10000)));

	FragColor = vec4(vec3(destColor * f), 1.0);
  }
}
