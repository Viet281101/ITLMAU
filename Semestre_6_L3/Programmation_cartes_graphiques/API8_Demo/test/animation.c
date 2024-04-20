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
