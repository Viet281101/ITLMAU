#ifndef PARTICULES_H

#define PARTICULES_H

#ifdef __cplusplus
extern "C" {
#endif

extern void initParticules();
extern void drawParticules(int nmb, int nmbColor, int scale, int rotateSelf, int rotateAxeZ, int random, int ld);
  
#ifdef __cplusplus
}
#endif
#endif
