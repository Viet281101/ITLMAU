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
	extern void spectre(int state);
#ifdef __cplusplus
}
#endif

#endif

