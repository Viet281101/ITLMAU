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

static void init(void);
static void draw(void);

static GLuint _diskId = 0;
static GLuint _pId = 0;
static int _musicMax = 0;

void main_section(int state) {
  switch(state) {
  case GL4DH_INIT:
    init();
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

void init(void) {
  _diskId = gl4dgGenDiskf(50.0f);
  _pId = gl4duCreateProgram("<vs>shaders/main.vs", "<fs>shaders/main.fs", NULL);
}

static double get_dt(void) {
  static double t0 = 0.0f;
  double t = gl4dGetElapsedTime(), dt = (t - t0) / 1000.0;
  t0 = t;
  return dt;
}

void draw(void) {
  static GLfloat a = 0.0f, delai = 400.0f;
  GLfloat time = gl4dhGetTicks()+delai; // début : 19600

  static float scaleCoef = 0.0f, rotSelfAngle = 0.0f, rotAxeZAngle = 0.0f;
  static int nmbParticules = 0, nmbColor = 0, scale = 0, random = 0, use_Ld = 0, section2_begin;

  // TIME RELATED STUFF | MAIN SECTION 1

  if (time < 86000) {
    if (time > 19600 && time < 20800)
      scaleCoef = (time-19600) / 30;

    if (time > 21000 && time < 22000)
      scaleCoef = (time-21000) / 25 + 40.0f;

    if (time > 22400 && time < 23400)
      scaleCoef = (time-22400) / 25 + 80.0f;

    if (time > 23600 && time < 24400)
      scaleCoef = (time-23600) / 20 + 120.0f;

    if (time > 24800 && time < 25800)
      scaleCoef = (time-24800) / 25 + 160.0f;

    if (time > 29000 && time < 38000)
      nmbParticules = (time-29000)/2;

    if (time > 38700 && time < 86000)
      scale = _musicMax/2;

    if (time > 58000 && time < 86000) {
      rotSelfAngle = 50.0f;
      if (!use_Ld)
        use_Ld = 1;
    }

    if (time > 76000 && time < 86000) {
      rotAxeZAngle = (time-76000) / 100;
      if (time > 77000) {
        gl4duBindMatrix("view");
        gl4duLoadIdentityf();
        gl4duLookAtf(0.0f, 0.0f, 115.0f - (time-76000) / 9.0f, 0.0f, 0.0f, (time-76000) / (-10.0f), 0.0f, 1.0f, 0.0f);
      }
    }
    if (time > 85500 && time < 86000)
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  }

  // TIME RELATED STUFF | MAIN SECTION 2

  if (time > 106000) {
    if (!section2_begin) {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      rotSelfAngle = 0.0f, rotAxeZAngle = 0.0f, nmbParticules = 0, use_Ld = 0;
      section2_begin = 1;
    }
    if (time > 106000 && time < 185000)
      scale = _musicMax/2;
    if (time > 106000 && time < 122000)
      nmbParticules = (time-106000) / 4;
    if (time > 108000 && time < 124000)
      nmbColor = (time-108000) / 4;

    if (time > 125100 && time < 144000) {
      rotSelfAngle = 50.0f, rotAxeZAngle = 90.0f;
      if (!use_Ld)
        use_Ld = 1;
    }
    if (time > 125100 && time < 144500) {
      gl4duBindMatrix("view");
      gl4duLoadIdentityf();
      gl4duLookAtf(0.0f, 0.0f, 5.0f + cos((time-125100))*10.0f, 0.0f, 0.0f, 0.0f + cos((time-125100))*10.0f, 0.0f, 1.0f, 0.0f);
    }

    if (time > 144500 && time < 145000) {
      random = 1;
    }
    if (time > 144500 && time < 163500) {
      gl4duBindMatrix("view");
      gl4duLoadIdentityf();
      gl4duLookAtf(0.0f, 0.0f, 5.0f + cos((time-125100)/1000)*10.0f, 0.0f, 0.0f, 0.0f + cos((time-125100)/1000)*10.0f, 0.0f, 1.0f, 0.0f);
    }

    if (time > 163500 && time < 164000) {
      gl4duBindMatrix("view");
      gl4duLoadIdentityf();
      gl4duLookAtf(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
      nmbParticules /= 1.5, nmbColor /= 1.5;
      scaleCoef = 0.0f;
    }
    if (time > 163500) {
      nmbColor = (16000/4) - (time-163500) / 4;
      nmbParticules = (16000/4) - (time-165500) / 4;
      rotSelfAngle += a*10;
      scaleCoef += a/50;
    }
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(_pId);
  
  gl4duBindMatrix("model");

  if (time < 86000) { // Backgroun circle : Section 1
    gl4duLoadIdentityf();
    gl4duTranslatef(0.0f, 0.0f, -1000.0f);
    gl4duRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gl4duScalef(scaleCoef, scaleCoef, scaleCoef);
    gl4duSendMatrices();
    glUniform1i(glGetUniformLocation(_pId, "use_white"), 1);
    gl4dgDraw(_diskId);
    glUniform1i(glGetUniformLocation(_pId, "use_white"), 0);
  }
  
  if (time > 163500) { // Background circle : Section 2
    gl4duLoadIdentityf();
    gl4duTranslatef(0.0f, 0.0f, -1000.0f);
    gl4duRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gl4duScalef(scaleCoef, scaleCoef, scaleCoef);
    gl4duSendMatrices();
    glUniform1i(glGetUniformLocation(_pId, "use_white"), 1);
    gl4dgDraw(_diskId);
    glUniform1i(glGetUniformLocation(_pId, "use_white"), 0);
  }

  drawParticules(nmbParticules, nmbColor, scale, rotSelfAngle, rotAxeZAngle, random, use_Ld);

  glUseProgram(0);
  a += 0.1f * M_PI * get_dt();
}