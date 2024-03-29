/*!\file heightmap.c
 *
 * \brief Walking on finite plane with skydome textured with a
 * triangle-edge midpoint-displacement algorithm.
 *
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date February 9 2017
 */
#include <math.h>
#include <time.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4dh.h>
#include "audioHelper.h"
/*!\brief nombre d'échantillons du signal sonore */
#define ECHANTILLONS 1024
static int _moyenne = 0;

static void init(void);
static void draw(void);
static void quit(void);

/*!\brief Grid geometry Id  */
static GLuint _grid = 0;
/*!\brief grid width */
static int _gridWidth = 255;
/*!\brief grid height */
static int _gridHeight = 255;
/*!\brief GLSL program Id */
static GLuint _pId = 0, _tId = 0;

void heightmap(int state) {
  int i, len;
  Sint16 * s;
  /* INITIALISEZ VOS VARIABLES */
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    init();
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    quit();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    s = (Sint16 *)ahGetAudioStream();
    len = ahGetAudioStreamLength();
    if(len >= 2 * ECHANTILLONS) {
      for(i = 0, _moyenne = 0; i < ECHANTILLONS; i++)
	_moyenne += abs(s[i]);
      _moyenne /= ECHANTILLONS;
    }
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    draw();
    return;
  }
}

void init(void) {
  _pId  = gl4duCreateProgram("<vs>shaders/heightmap.vs", "<fs>shaders/heightmap.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  //resize(_windowWidth, _windowHeight);
  /* generates a grid using GL4Dummies */
  _grid = gl4dgGenGrid2df(_gridWidth, _gridHeight);
  /* generates a fractal height-map */
  srand(time(NULL));
  GLfloat* hm = gl4dmTriangleEdge(_gridWidth, _gridHeight, 0.6f);
  glGenTextures(1, &_tId);
  glBindTexture(GL_TEXTURE_2D, _tId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _gridWidth, _gridHeight, 0, GL_RED, GL_FLOAT, hm);
  glBindTexture(GL_TEXTURE_2D, 0);
#ifndef _WIN32
  free(hm); /* je ne sais pas pourquoi ça plante sous windows !!!! vraiment un OS de daube */
#endif
}

/*!\brief function called by GL4Dummies' loop at draw.*/
static void draw(void) {
  /* step = x and y max distance between two adjacent vertices */
  GLfloat step[2] = { 2.0 / _gridWidth, 2.0 / _gridHeight};

  /* c'était dans init avant */
  GLboolean dt;
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5, 0.5, -0.5 * vp[3] / (GLfloat)vp[2], 0.5 * vp[3] / (GLfloat)vp[2], 1.0, 10.0);
  glClearColor(0.0f, 0.4f, 0.9f, 0.0f);
  dt = glIsEnabled(GL_DEPTH_TEST);
  /* s'il n'est pas activé, l'activer */
  if(!dt)
    glEnable(GL_DEPTH_TEST);

  /* clears the OpenGL color buffer and depth buffer */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glActiveTexture(GL_TEXTURE0);
  /* sets the current program shader to _pId */
  glUseProgram(_pId);
  /* loads the identity matrix in the current GL4Dummies matrix ("modelViewMatrix") */
  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();

  /* rotation around x-axis, old y-axis and tranlation */
  gl4duPushMatrix(); {
    gl4duTranslatef(0, 0, -5);
    gl4duRotatef(45, 0, cos(45 * M_PI / 180.0), sin(45 * M_PI / 180.0));
    gl4duRotatef(45, 1, 0, 0);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  /* draws the grid */
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  glUniform1i(glGetUniformLocation(_pId, "frame"), SDL_GetTicks());
  glUniform2fv(glGetUniformLocation(_pId, "step"), 1, step);
  glUniform1f(glGetUniformLocation(_pId, "amplitude"), _moyenne / ((1<<15) + 1.0));

  glBindTexture(GL_TEXTURE_2D, _tId);
  gl4dgDraw(_grid);
  glBindTexture(GL_TEXTURE_2D, 0);

  /* s'il n'était pas activé, de désactiver */
  if(!dt)
    glDisable(GL_DEPTH_TEST);
}

/*!\brief function called at exit, it cleans-up SDL2_mixer and GL4Dummies.*/
static void quit(void) {
  if(_tId) {
    glDeleteTextures(1, &_tId);
    _tId = 0;
  }
}

