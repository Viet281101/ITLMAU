/*!\file animations.h
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

#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H


#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


#ifdef __cplusplus
extern "C" {
#endif
	/* animations */
	extern void animation_vide(int state);

	extern void green(int state);
	extern void blue(int state);
	extern void strip(int state);
	extern void strip2(int state);
	extern void credit_fin(int state);

	extern void animationsInit(void);

	/* transition */
	extern void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
	extern void fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
	extern void spectre(int state);
#ifdef __cplusplus
}
#endif

#endif



