#include <GL4D/gl4du.h>
#include <GL4D/gl4dp.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

  extern void exemple_de_transition_00(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void animation2(int state);
  extern void animation1(int state);
  extern void mobileDraw(void);
  extern void animationsInit(void);

#ifdef __cplusplus
}
#endif

#endif
