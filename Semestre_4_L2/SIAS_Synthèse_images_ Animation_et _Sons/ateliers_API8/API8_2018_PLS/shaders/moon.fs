#version 330

uniform float temps;
in  vec2 vsoTexCoord;
out vec4 fragColor;

vec2 resolution = vec2(1000, 1000);

	#define LAYERS 200
	#define DEPTH .1
	#define WIDTH .8
	#define SPEED 1.5

void main()
{
  float time = temps / 10;
	const mat3 p = mat3(13.323122,23.5112,21.71123,21.1212,28.7312,11.9312,21.8112,14.7212,61.3934);
	vec2 uv = resolution.xy + vec2(1.,resolution.y / resolution.x) * gl_FragCoord.xy / resolution.xy;
	vec3 acc = vec3(0.0);
	float dof = 5. * sin(time*.1);
	for (int i = 0;i<LAYERS;i++)
	{
		float fi = float(i);
		vec2 q = uv*(1.+fi * DEPTH);
		q += vec2(q.y*(WIDTH * mod(fi * 7.238917,1.)-WIDTH*.5), SPEED * time/(1.+fi * DEPTH*.03));
		vec3 n = vec3(floor(q),31.189 + fi);
		vec3 m = floor(n)*.00001 + fract(n);
		vec3 mp = (31415.9 + m)/fract(p * m);
		vec3 r = fract(mp);
		vec2 s = abs(mod(q,1.)-.5+.9 * r.xy-.45);
		s += .01 * abs(2.*fract(10. * q.yx)-1.);
		float d = .6 * max(s.x-s.y,s.x + s.y) + max(s.x,s.y)-.01;
		float edge = .05+.05 * min(.5 * abs(fi-5.-dof), 1.);
		acc += vec3(smoothstep(edge,-edge,d)*(r.x / (1. + .02 * fi * DEPTH)));
	}
	/* La lune ressemble à un soleil... On va dire que c'est pas grave */
	vec2 moonp = vec2(0.5,0.8);
	float moon = smoothstep(0.95,0.956,1. - length(uv-moonp));
	vec2 moonp2 = moonp + vec2(0.015, 0);
	moon -= smoothstep(0.93,0.956,1. - length(uv-moonp2));
	moon = clamp(moon, 0., 1.);
	moon += 0.3 * smoothstep(0.80,0.956,1. - length(uv-moonp));

	fragColor = vec4(vec3(acc + moon),1.0);
}
