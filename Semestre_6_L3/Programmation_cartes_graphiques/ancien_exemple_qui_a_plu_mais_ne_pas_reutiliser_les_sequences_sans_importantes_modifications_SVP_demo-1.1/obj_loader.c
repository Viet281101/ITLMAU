/*!\file window.c
 *
 * \brief utilisation de GL4Dummies et Lib Assimp pour chargement de
 * scènes.
 *
 * \author Farès Belhadj amsi@ai.univ-paris8.fr
 * \date February 14 2017
 */

#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dh.h>
#include <SDL_image.h>
#include "assimp.h"
#include "audioHelper.h"

/*!\brief GLSL program Id */
static GLuint _pId = 0;

/*!\brief identifiant de la scene générée par assimpGenScene */
static GLuint _id_scene = 0;

static void init(void);
static void mets_a_jour_avec_audio(Uint8 * stream, int length);
static void draw(void);

void obj_loader(int state) {
  /* INITIALISEZ VOS VARIABLES */
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    init();
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    mets_a_jour_avec_audio(ahGetAudioStream(), ahGetAudioStreamLength());
    return;
  default: { /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    GLboolean dt = glIsEnabled(GL_DEPTH_TEST);
    if(!dt)
      glEnable(GL_DEPTH_TEST);
    draw();
    if(!dt)    
      glDisable(GL_DEPTH_TEST);
    return;
  }
  }
}

static void init(void) {
  _pId = gl4duCreateProgram("<vs>shaders/obj_loader.vs", "<fs>shaders/obj_loader.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "modelViewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);
  
  _id_scene = assimpGenScene("models/soccer/soccerball.obj");
}

static GLfloat rot_y = 0.0f;

static void mets_a_jour_avec_audio(Uint8 * stream, int length) {
  int i;
  Sint16 * s = (Sint16 *)stream;
  double m = 0.0;
  length = length / 2;
  for(i = 0; i < length; ++i)
    m += abs(s[i]);
  m = m / length;
  m = m / (1 << 10);
  rot_y += m;
}


static void draw(void) {
  GLint viewport[4];
  GLfloat lum[4] = {0.0, 0.0, 5.0, 1.0};
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glGetIntegerv(GL_VIEWPORT, viewport);
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.005f, 0.005f, -(0.005f * viewport[3]) / viewport[2], (0.005f * viewport[3]) / viewport[2], 0.01f, 1000.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(_pId);

  glUniform4fv(glGetUniformLocation(_pId, "lumpos"), 1, lum);

  gl4duBindMatrix("modelViewMatrix");
  gl4duLoadIdentityf();
  gl4duLookAtf(0, 0, 3, 0, 0, 0, 0.0, 1.0, 0.0);

  gl4duRotatef(rot_y, 0, 1, 0);
  assimpDrawScene(_id_scene);

  //rot_y += 1.0f;
}


