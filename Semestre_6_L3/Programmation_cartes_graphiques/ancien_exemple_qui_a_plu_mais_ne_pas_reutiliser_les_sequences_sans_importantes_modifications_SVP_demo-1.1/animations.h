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
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date May 05, 2014
 */
#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

  extern void exemple_de_transition_00(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void exemple_de_transition_01(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void exemple_d_animation_00(int state);
  extern void random_anim(int state);
  extern void animationsInit(void);
  /* Dans heightmap.c */
  extern void heightmap(int state);
  /* Dans spectre.c */
  extern void spectre(int state);
  extern void obj_loader(int state);
#ifdef __cplusplus
}

/* Dans light_n_tex.cpp */
/* elle n'est pas au même endroit que les autres car c'est du c++ */
extern void light_n_tex(int state);

#endif

#endif
