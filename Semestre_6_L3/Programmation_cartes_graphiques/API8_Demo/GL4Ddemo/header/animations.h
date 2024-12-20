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

#include "audioHelper.h"
#include "assimp.h"
#include <SDL_ttf.h>
#include <SDL_image.h>


#ifdef __cplusplus
extern "C" {
#endif

  // extern void fondu1(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void player1(int state);
  extern void player2(int state);
  extern void versus(int state);
  extern void depart1(int state);
  extern void depart2(int state);
  extern void toutdroit(int state);
  extern void viraged(int state);
  extern void virageg(int state);
  extern void arrivee1(int state);
  extern void arrivee2(int state);
  extern void pd(int state);
  extern void animationsInit(void);
    
#ifdef __cplusplus
}
#endif

#endif
