
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
void pythagore_arbre(point a,point b,int i);
void sierpinski_anim();
void sierpinski_triangle(float steps);
void julia(double zooma,int maxIterations,double cIm,double cRe);
void barnsley(int largeur,int iterations);


  extern void animation_sierpinski(int state);
  extern void animation_mendel(int state);
  extern void animation_pythagore(int state);
  extern void animation_julia(int state);
  extern void animation_julia_zoom(int state);
  extern void animation_barnsley(int state);
  extern void animationsInit(void);

#ifdef __cplusplus
}
#endif

#endif
