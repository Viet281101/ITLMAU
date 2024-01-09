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

typedef struct{
  double x;
  double y;
}point;


#define MAX_STEPS 500000

  void mendel(int max);
  void mendel_anim();
  void julia(double zooma,int maxIterations,double cIm,double cRe);

  extern void animation_julia(int state);
  extern void animation_mendel(int state);
  extern void exemple_de_transition_00(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void exemple_de_transition_01(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void exemple_d_animation_00(int state);
  extern void exemple_d_animation_01(int state);
  extern void animationsInit(void);
  /* dans seq_voro.c */
  extern void seq_voro(int state);
  /* dans spectre_3d.c */
  extern void spectre_3d(int state);
  /* dans credit.c */
  extern void credit_fin(int state);
#ifdef __cplusplus
}
#endif

#endif
