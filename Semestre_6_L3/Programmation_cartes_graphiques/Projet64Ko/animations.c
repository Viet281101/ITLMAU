#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include "animations.h"
#include <assert.h>
#include <stdlib.h>
#include <GL4D/gl4dg.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
static GLuint _quadId = 0;/*!\brief identifiant de la géométrie QUAD GL4Dummies */
void animation_vide(int state) {
	switch(state) {
	case GL4DH_DRAW:
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	default: return;
	}
}
void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
	int vp[4], i;
	GLint tId;
	static GLuint tex[2], pId;
	switch(state) {
	case GL4DH_INIT:
		glGetIntegerv(GL_VIEWPORT, vp);
		glGenTextures(2, tex);
		for(i = 0; i < 2; i++) {
			glBindTexture(GL_TEXTURE_2D, tex[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		}
		pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mix.fs", NULL);
		return;
	case GL4DH_FREE: if(tex[0]) { glDeleteTextures(2, tex); tex[0] = tex[1] = 0; } return;
	case GL4DH_UPDATE_WITH_AUDIO:
		if(a0) a0(state);
		if(a1) a1(state);
		return;
	default:
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
		if(a0) a0(state);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
		if(a1) a1(state);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
		glDisable(GL_DEPTH);
		glUseProgram(pId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex[1]);
		if(et / (GLfloat)t > 1) { fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t); exit(0); }
		glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
		glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
		glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
		gl4dgDraw(_quadId);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		return;
	}
}
void green(int state) {
	static double mp = 0.0;
	switch(state) {
	case GL4DH_INIT:
		return;
	case GL4DH_FREE:
		return;
	case GL4DH_UPDATE_WITH_AUDIO: {
		int l = ahGetAudioStreamLength(), i;
		short * s = (short *)ahGetAudioStream();
		double m = 0.0;
		for(i = 0; i < l / 2; ++i)
		m += fabs(s[i] / (double)(1 << 15));
		mp = m / (l / 2);
		return;
	}
	default:
		glClearColor(0.0f, 5.0f * mp, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	}
}
void blue(int state) {
	switch(state) {
	case GL4DH_INIT:
		return;
	case GL4DH_FREE: gl4dpDeleteScreen(); return;
	case GL4DH_UPDATE_WITH_AUDIO:
		return;
	default:
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	}
}
void run_shaders(GLuint shaderId, GLuint quadId, float* time, float timeScale, Uint32* lastTimePtr) {
	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = (*lastTimePtr > 0) ? (currentTime - *lastTimePtr) / 1000.0f : 0.0f;
	*lastTimePtr = currentTime;
	*time += deltaTime * timeScale;
	glUseProgram(shaderId);
	glUniform1f(glGetUniformLocation(shaderId, "time"), *time);
	int width, height;
	SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &width, &height);
	glUniform2f(glGetUniformLocation(shaderId, "resolution"), (float) width, (float) height);
	gl4dgDraw(quadId);
	glUseProgram(0);
}
void sun_wave(int state) {
	static float time = 0.0;
	static GLuint _pId = 0, _quadId = 0;
	static Uint32 lastTime = 0;
	switch (state) {
	case GL4DH_INIT:
		_pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/sun_wave.fs", NULL);
		_quadId = gl4dgGenQuadf();
		break;
	case GL4DH_FREE: gl4dgDelete(_quadId); gl4duClean(GL4DU_ALL); break;
	case GL4DH_DRAW: run_shaders(_pId, _quadId, &time, 1.0f, &lastTime); break;
	}
}
void strip(int state) {
	static float time = 0.0;
	static GLuint _pId = 0, _quadId = 0;
	static Uint32 lastTime = 0;
	switch (state) {
	case GL4DH_INIT:
		_pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/strip.fs", NULL);
		_quadId = gl4dgGenQuadf();
		break;
	case GL4DH_FREE: gl4dgDelete(_quadId); gl4duClean(GL4DU_ALL); break;
	case GL4DH_DRAW: run_shaders(_pId, _quadId, &time, 1.5f, &lastTime); break;
	}
}
void animationsInit(void) {
	if(!_quadId)
		_quadId = gl4dgGenQuadf();
}

