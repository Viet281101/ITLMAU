/*!\file animations.c
 *
 * \brief Votre espace de liberté : c'est ici que vous pouvez ajouter
 * vos fonctions de transition et d'animation avant de les faire
 * référencées dans le tableau _animations du fichier \ref window.c
 *
 * Des squelettes d'animations et de transitions sont fournis pour
 * comprendre le fonctionnement de la bibliothèque. En bonus des
 * exemples dont un fondu en GLSL.
 *
 * \author Farès BELHADJ, amsi@up8.edu
 * \date April 12, 2023
 */

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

void exemple_d_animation_00(int state) {
	int l, i;
	Uint16 * s;
	static GLfloat c[4] = {0, 0, 0, 0};
	switch(state) {
	case GL4DH_INIT:
		return;
	case GL4DH_FREE:
		return;
	case GL4DH_UPDATE_WITH_AUDIO:
		s = (Uint16 *)ahGetAudioStream();
		l = ahGetAudioStreamLength();
		if(l >= 8)
		for(i = 0; i < 4; i++)
	c[i] = s[i] / ((1 << 16) - 1.0);
		return;
	default: 
		glClearColor(c[0], c[1], c[2], c[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		return;
	}
}

void exemple_de_transition_00(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
	/* INITIALISEZ VOS VARIABLES */
	switch(state) {
	case GL4DH_INIT:
		/* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
		return;
	case GL4DH_FREE:
		/* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
		return;
	case GL4DH_UPDATE_WITH_AUDIO:
		/* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
		if(a0) a0(state);
		if(a1) a1(state);
		return;
	default: /* GL4DH_DRAW */
		/* JOUER LES DEUX ANIMATIONS */
		if(a0) a0(state);
		if(a1) a1(state);
		/* MIXER LES DEUX ANIMATIONS */
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

void red(int state) {
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
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		return;
	}
}

void ciel(int state) {
	static GLuint _pId = 0;
	static GLuint _quad = 0;
	static int increment = 0;
	switch (state) {
	case GL4DH_INIT:
		_pId = gl4duCreateProgram( "<vs>shaders/basic.vs", "<fs>shaders/ciel.fs", NULL );
		_quad = gl4dgGenQuadf();
		gl4duGenMatrix( GL_FLOAT, "projectionMatrix" );
		gl4duGenMatrix( GL_FLOAT, "modelMatrix" );
		gl4duGenMatrix( GL_FLOAT, "viewMatrix" );
		return;
	case GL4DH_FREE:
		if ( _quad ) gl4dgDelete( _quad );
		gl4duClean( GL4DU_ALL );
		return;
	case GL4DH_UPDATE_WITH_AUDIO:
		return;
	default: /* GL4DH_DRAW */
		/* JOUER L'ANIMATION */
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glUseProgram(_pId);
		gl4duBindMatrix( "projectionMatrix" );
		gl4duLoadIdentityf();
		gl4duScalef( 1.0f, 1.0f, 1.0f );
		gl4duBindMatrix( "viewMatrix" );
		gl4duLookAtf( 0, 0, 1, 0, 0, 0, 0, 1, 0 );
		gl4duBindMatrix( "modelMatrix" );
		gl4duLoadIdentityf();
		gl4duSendMatrices();

		gl4dgDraw(_quad);
		glUseProgram(0);
		increment++;
		increment %= 10;
		return;
	}
}

void animationsInit(void) {
	if(!_quadId)
		_quadId = gl4dgGenQuadf();
}


