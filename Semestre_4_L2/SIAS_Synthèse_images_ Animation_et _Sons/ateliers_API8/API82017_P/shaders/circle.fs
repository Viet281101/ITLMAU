#version 330

uniform int time;
uniform int coef;
uniform int resx;
uniform int resy;

in vec2 vsoTexCoord;
out vec4 FragColor;

vec2 res = vec2(resx, resy);
vec3 b = vec3(0.05, 0.08, 0.005);

void 
main() 
{
	vec2 c = gl_FragCoord.xy / res.xy - 0.5;
	c.x *= res.x / res.y;	    
	float time = -time*-24.+length(c * 30);
	float r = 0.2 * (1.0 + cos(coef + time)) * pow(cos ((time * coef * 2) - atan(c.x, c.y) * 10.0), 4.0);
	float s = length(c * 1.5) -  (r * 0.2);
	FragColor = vec4(b / pow(s,5), 0);
}
