#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif
  
  extern void exemple_de_transition_00(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void exemple_de_transition_01(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void exemple_de_transition_02(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);	
  extern void animation_verte(int state);
  extern void animation_psycho(int state);
  extern void animation_blow(int state);
  extern void animation_circle(int state);
  extern void animation_light(int state);
  extern void animation_lense(int state);
  extern void animationsInit(void);
  extern void animation_bloop(void);
  extern void credits(int state);

#ifdef __cplusplus
}
#endif

#endif
