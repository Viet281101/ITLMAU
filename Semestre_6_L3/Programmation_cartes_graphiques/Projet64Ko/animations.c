
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

/*!\brief identifiant de la géométrie QUAD GL4Dummies */
static GLuint _quadId = 0;

void animation_vide(int state) {
	switch(state) {
	case GL4DH_DRAW:
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	default:
		return;
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
	case GL4DH_FREE:
		if(tex[0]) {
			glDeleteTextures(2, tex);
			tex[0] = tex[1] = 0;
		}
		return;
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
		if(et / (GLfloat)t > 1) {
			fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
			exit(0);
		}
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

void fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
	/* INITIALISEZ VOS VARIABLES */
	int vp[4], i;
	GLint tId;
	static GLuint tex[2], pId;
	switch(state) {
	case GL4DH_INIT:
		/* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
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
	case GL4DH_FREE:
		/* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
		if(tex[0]) {
			glDeleteTextures(2, tex);
			tex[0] = tex[1] = 0;
		}
		return;
	case GL4DH_UPDATE_WITH_AUDIO:
		/* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
		if(a0) a0(state);
		if(a1) a1(state);
		return;
	default: /* GL4DH_DRAW */
		/* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
		glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
		/* JOUER LES DEUX ANIMATIONS */
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
		if(a0) a0(state);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
		if(a1) a1(state);
		/* MIXER LES DEUX ANIMATIONS */
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
		glDisable(GL_DEPTH);
		glUseProgram(pId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex[1]);
		if(et / (GLfloat)t > 1) {
			fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
			exit(0);
		}
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
	/* INITIALISEZ VOS VARIABLES */
	static double mp = 0.0;
	switch(state) {
	case GL4DH_INIT:
		/* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
		return;
	case GL4DH_FREE:
		/* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
		return;
	case GL4DH_UPDATE_WITH_AUDIO: {
		/* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
		int l = ahGetAudioStreamLength(), i;
		short * s = (short *)ahGetAudioStream();
		double m = 0.0;
		for(i = 0; i < l / 2; ++i)
		m += fabs(s[i] / (double)(1 << 15));
		mp = m / (l / 2);
		return;
	}
	default: /* GL4DH_DRAW */
		/* JOUER L'ANIMATION */
		glClearColor(0.0f, 5.0f * mp, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	}
}

void blue(int state) {
	/* INITIALISEZ VOS VARIABLES */
	/* ... */
	switch(state) {
	case GL4DH_INIT:
		/* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
		return;
	case GL4DH_FREE:
		/* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
		gl4dpDeleteScreen();
		return;
	case GL4DH_UPDATE_WITH_AUDIO:
		/* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
		return;
	default: /* GL4DH_DRAW */
		/* JOUER L'ANIMATION */
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	}
}

void strip(int state) {
	static float time = 0.0;
	static GLuint stripId = 0;
	static GLuint stripQuadId = 0;
	switch(state) {
	case GL4DH_INIT:
		stripId = gl4duCreateProgram("<vs>shaders/strip.vs", "<fs>shaders/strip.fs", NULL);
		stripQuadId = gl4dgGenQuadf();
		break;
	case GL4DH_FREE:
		gl4dgDelete(stripQuadId);
		gl4duClean(GL4DU_ALL);
		break;
	case GL4DH_DRAW:
		time += 0.1;
		glUseProgram(stripId);
		glUniform1f(glGetUniformLocation(stripId, "time"), time);
		int width, height;
		SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &width, &height);
		glUniform2f(glGetUniformLocation(stripId, "resolution"), (float) width, (float) height);
		gl4dgDraw(stripQuadId);
		glUseProgram(0);
		break;
	}
}
void strip2(int state) {
	static float time = 0.0;
	static GLuint stripId2 = 0;
	static GLuint stripQuadId2 = 0;
	switch(state) {
	case GL4DH_INIT:
		stripId2 = gl4duCreateProgram("<vs>shaders/strip.vs", "<fs>shaders/strip2.fs", NULL);
		stripQuadId2 = gl4dgGenQuadf();
		break;
	case GL4DH_FREE:
		gl4dgDelete(stripQuadId2);
		gl4duClean(GL4DU_ALL);
		break;
	case GL4DH_DRAW:
		time += 0.05;
		glUseProgram(stripId2);
		glUniform1f(glGetUniformLocation(stripId2, "time"), time);
		int width, height;
		SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &width, &height);
		glUniform2f(glGetUniformLocation(stripId2, "resolution"), (float) width, (float) height);
		gl4dgDraw(stripQuadId2);
		glUseProgram(0);
		break;
	}
}

void animationsInit(void) {
	if(!_quadId)
		_quadId = gl4dgGenQuadf();
}


