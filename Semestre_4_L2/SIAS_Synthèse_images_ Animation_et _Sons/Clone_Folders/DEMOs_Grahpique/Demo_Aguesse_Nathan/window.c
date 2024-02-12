#include <stdlib.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dh.h>
#include <GL4D/gl4duw_SDL2.h>
#include "animations.h"
#include "audioHelper.h"
#include "particules.h"

static void init(void);
static void quit(void);
static void keydown(int keycode);

static GL4DHanime _animations[] = {
  {19200, credit_intro, NULL, NULL }, // Crédit intro
  {67200, main_section, NULL, NULL }, // Main section 1
  {19200, transition_2d, NULL, NULL }, // Transition 2D
  {77700, main_section, NULL, NULL }, // Main section 2
  {    0, NULL, NULL, NULL }
};

static GLfloat _dim[] = {1920, 948};

int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "Demoscene - API8", 
			 GL4DW_POS_CENTERED, GL4DW_POS_CENTERED, 
			 _dim[0], _dim[1],
			 /*GL4DW_BORDERLESS | GL4DW_FULLSCREEN | GL4DW_FULLSCREEN_DESKTOP | GL4DW_MAXIMIZED | GL4DW_FULLSCREEN |*/ GL4DW_OPENGL | GL4DW_RESIZABLE | GL4DW_SHOWN))
    return 1;
  init();
  initParticules();
  SDL_GL_SetSwapInterval(1);
  gl4dpInitScreen();
  atexit(quit);
  gl4duwKeyDownFunc(keydown);
  gl4duwDisplayFunc(gl4dhDraw);

  ahInitAudio("zohryu-roux-08jabberwock.flac");
  gl4duwMainLoop();
  return 0;
}

static void init(void) {
  gl4dhInit(_animations, _dim[0], _dim[1], animationsInit);
  gl4duGenMatrix(GL_FLOAT, "model");
  gl4duGenMatrix(GL_FLOAT, "view");
  gl4duGenMatrix(GL_FLOAT, "proj");
  
  gl4duBindMatrix("proj");
  gl4duLoadIdentityf();
  gl4duFrustumf(-1.0f * (_dim[0] / (GLfloat)_dim[1]), 1.0f * (_dim[0] / (GLfloat)_dim[1]), -1.0f, 1.0f, 1.0f, 1010.0f);

  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
}

static void keydown(int keycode) {
  switch(keycode) {
  case SDLK_ESCAPE:
  case 'q':
    exit(0);
  default: break;
  }
}

static void quit(void) {
  ahClean();
  gl4duClean(GL4DU_ALL);
}
