#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4dh.h>
#include <stdio.h>
#include <assert.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "audioHelper.h"
#include "particules.h"

static void draw(void);
static void drawRandomStuf(int x, int y, int limit);
static void drawOtherRandomStuf(int x, int y, int dir, int limit);

static int _musicMax = 0;

void transition_2d(int state) {
  switch(state) {
  case GL4DH_INIT:
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO: {
    int l = ahGetAudioStreamLength(), i;
    short * s = (short *)ahGetAudioStream();
    int max = 0;
    for(i = 0; i < l / 4; ++i)
      if (max < s[2 * i])
        max = MAX(s[2 * i], s[1 + 2 * i]);
    _musicMax = max >> 10;
    return;
  }
  default: /* GL4DH_DRAW */
    draw();
    return;
  }
}

static double get_dt(void) {
  static double t0 = 0.0f;
  double t = gl4dGetElapsedTime(), dt = (t - t0) / 1000.0;
  t0 = t;
  return dt;
}

void draw(void) {
  static GLfloat a = 0.0f;
  GLfloat time = gl4dhGetTicks();

  static float radius = 0.0f;

  if (time > 86000 && time < 87000) {
    gl4duBindMatrix("view");
    gl4duLoadIdentityf();
    gl4duLookAtf(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  }

  if (time > 104000 && time < 106000) {
    radius += (time-104000) / 2;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gl4dpSetColor(RGB(0, 0, 0));

  gl4dpClearScreenWith(RGB(255, 255, 255));
  drawRandomStuf(960, 474, 5);
  drawOtherRandomStuf(960, 474, 0, 10);
  drawOtherRandomStuf(960, 474, 1, 10);
  drawOtherRandomStuf(960, 474, 2, 10);
  drawOtherRandomStuf(960, 474, 3, 10);
  gl4dpUpdateScreen(NULL);

  a += 0.1f * M_PI * get_dt();
}

void drawRandomStuf(int x, int y, int limit) {
  int dirX, dirY;
  if (!limit)
    return;
  dirX = gl4dmSURand()*10;
  dirY = gl4dmSURand()*10;

  gl4dpLine(x, y, x+(dirX+_musicMax)*5, y+dirY); // droit
  drawRandomStuf(x+(dirX+_musicMax)*5, y+dirY, limit-1);

  gl4dpLine(x, y, x+(dirX+_musicMax)*(-5), y-dirY); // gauche
  drawRandomStuf(x+(dirX+_musicMax)*(-5), y-dirY, limit-1);

  gl4dpLine(x, y, x-dirX, y+(dirY+_musicMax)*5); // haut
  drawRandomStuf(x-dirX, y+(dirY+_musicMax)*5, limit-1);

  gl4dpLine(x, y, x+dirX, y+(dirY+_musicMax)*(-5)); // bas
  drawRandomStuf(x+dirX, y+(dirY+_musicMax)*(-5), limit-1);
}

void drawOtherRandomStuf(int x, int y, int dir, int limit) {
  int dirX, dirY;
  if (!limit)
    return;
  dirX = gl4dmSURand()*10;
  dirY = gl4dmSURand()*10;

  switch(dir) {
    case 0: // droit
      gl4dpLine(x, y, x+_musicMax*4+dirX, y+_musicMax*4-dirY);
      drawOtherRandomStuf(x+_musicMax*4+dirX, y+_musicMax*4-dirY, dir, limit-1);
      gl4dpLine(x, y, x+_musicMax*4-dirX, y-_musicMax*4+dirY);
      drawOtherRandomStuf(x+_musicMax*4-dirX, y-_musicMax*4+dirY, dir, limit-1);
      break;
    case 1: // gauche
      gl4dpLine(x, y, x-_musicMax*4-dirX, y-_musicMax*4+dirY);
      drawOtherRandomStuf(x-_musicMax*4-dirX, y-_musicMax*4+dirY, dir, limit-1);
      gl4dpLine(x, y, x-_musicMax*4+dirX, y+_musicMax*4-dirY);
      drawOtherRandomStuf(x-_musicMax*4+dirX, y+_musicMax*4-dirY, dir, limit-1);
      break;
    case 2: // haut
      gl4dpLine(x, y, x+_musicMax*4-dirX, y+_musicMax*4+dirY);
      drawOtherRandomStuf(x+_musicMax*4-dirX, y+_musicMax*4+dirY, dir, limit-1);
      gl4dpLine(x, y, x-_musicMax*4+dirX, y+_musicMax*4-dirY);
      drawOtherRandomStuf(x-_musicMax*4+dirX, y+_musicMax*4-dirY, dir, limit-1);
      break;
    case 3: // bas
      gl4dpLine(x, y, x-_musicMax*4+dirX, y-_musicMax*4-dirY);
      drawOtherRandomStuf(x-_musicMax*4+dirX, y-_musicMax*4-dirY, dir, limit-1);
      gl4dpLine(x, y, x+_musicMax*4-dirX, y-_musicMax*4+dirY);
      drawOtherRandomStuf(x+_musicMax*4-dirX, y-_musicMax*4+dirY, dir, limit-1);
      break;
  }
}