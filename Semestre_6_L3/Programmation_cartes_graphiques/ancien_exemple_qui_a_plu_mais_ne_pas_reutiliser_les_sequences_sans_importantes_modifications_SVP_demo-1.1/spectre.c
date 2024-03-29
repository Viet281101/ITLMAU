/*!\file window.c
 * \brief GL4Dummies, exemple simple 3D avec GL4Dummies
 * \author Farès BELHADJ, amsi@up8.edu
 * \date February 03 2022
 */

/* inclusion des entêtes de fonctions de création et de gestion de
 * fenêtres système ouvrant un contexte favorable à GL4dummies. Cette
 * partie est dépendante de la bibliothèque SDL2 */
#include <GL4D/gl4dm.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4df.h>
#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include <assert.h>

static void init(void);
static void draw(void);
static void scene(void);
static void quit(void);

/* mon plateau de 32x32 cubes */
const int _EW = 16, _EH = 16;

/* on créé une variable pour stocker l'identifiant du programme GPU */
static GLuint _pId = 0;
/* on créé une variable pour stocker l'identifiant de la géométrie d'un cube GL4D */
static GLuint _cube = 0;

/* des identifiants de textures */
static GLuint _texId[1] = { 0 };


/*!\brief nombre d'échantillons du signal sonore */
#define ECHANTILLONS 1024
/*!\brief amplitude des échantillons du signal sonore */
static Sint16 _hauteurst[ECHANTILLONS];
static Sint16 _hauteurs[ECHANTILLONS];

void spectre(int state) {
  const int toursmax = 4;
  static int tours = 0;
  int i, len;
  Sint16 *s = NULL;
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
    if(tours == 0)
      memset(_hauteurst, 0, sizeof _hauteurst);
    if(len >= 2 * ECHANTILLONS)
      for(i = 0; i < ECHANTILLONS; i++)
	_hauteurst[i] += 1.5f * 256 * pow(abs(s[i]) / ((1 << 15) + 1.0), 1.5);
    ++tours;
    if(tours == toursmax) {
      tours = 0;
      for(i = 0; i < ECHANTILLONS; i++)
	_hauteurs[i] = _hauteurst[i] / toursmax;
    }
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    draw();
    return;
  }
}



/* initialise des paramètres GL et GL4D */
void init(void) {
  GLuint image_0[] = { -1, -1, -1, -1 };
  assert(4 * _EW * _EH == ECHANTILLONS);
  /* générer un identifiant de texture */
  glGenTextures(1, _texId);
  assert(_texId[0]);
  /* binder _texId[0] comme texture bidimensionnelle */
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  /* comportement de l'interpolation en minimisant puis maximisant la texture */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  /* spécification et transfert de la donnée */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_0);
  /* dé-binder la texture bidimensionnelle */
  glBindTexture(GL_TEXTURE_2D, 0);
  
  /* set la couleur d'effacement OpenGL */
  glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
  /* générer un cube en GL4D */
  _cube = gl4dgGenCubef();
  /* créer un programme GPU pour OpenGL (en GL4D) */
  _pId = gl4duCreateProgram("<vs>shaders/spectre.vs", "<fs>shaders/spectre.fs", NULL);
  /* créer dans GL4D une matrice qui s'appelle model ; matrice de
     modélisation qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "model");
  /* créer dans GL4D une matrice qui s'appelle view ; matrice de
     (point de) vue qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "view");
  /* créer dans GL4D une matrice qui s'appelle proj ; matrice de
     projection qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "proj");
}

void draw(void) {
  GLboolean dt;
  GLint vp[4];
  GLfloat inv_ratio;
  /* effacer le buffer de couleur (image) et le buffer de profondeur d'OpenGL */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glGetIntegerv(GL_VIEWPORT, vp);
  dt = glIsEnabled(GL_DEPTH_TEST);
  /* s'il n'est pas activé, l'activer */
  if(!dt)
    glEnable(GL_DEPTH_TEST);

  /* calculer l'inverse du ratio fenêtre (multiplicateur de la hauteur du plan near) */
  inv_ratio = vp[3] / (GLfloat)vp[2];
  /* binder (mettre au premier plan, "en courante" ou "en active") la matrice proj */
  gl4duBindMatrix("proj");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  /* combiner la matrice courante avec une matrice de projection en
     perspective. Voir le support de cours pour les six paramètres :
     left, right, bottom, top, near, far */
  gl4duFrustumf(-1.0f, 1.0f, -1.0f * inv_ratio, 1.0f * inv_ratio, 1.0f, 1000.0f);

  gl4duBindMatrix("view");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  /* composer (multiplication à droite) avec une translation dans les z négatifs (-5) */ 
  gl4duLookAtf(-5, 30, 25, 0, 0, 0, 0, 1, 0);

  scene();

  GLint tId;
  glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
  gl4dfSobelSetMixMode(GL4DF_SOBEL_MIX_MULT);
  //gl4dfBlur(tId, tId, 5, 1, 0, GL_FALSE);
  gl4dfSobel(tId, tId, GL_FALSE);

  /* s'il n'était pas activé, de désactiver */
  if(!dt)
    glDisable(GL_DEPTH_TEST);
}

void scene(void) {
  const GLfloat colors[64] = {
    0.0f, 1.0f, 0.0f, 1.0f,//vert
    0.15f, 1.0f, 0.0f, 1.0f,
    0.3f, 1.0f, 0.0f, 1.0f,
    0.45f, 1.0f, 0.0f, 1.0f,
    0.6f, 1.0f, 0.0f, 1.0f,
    0.75f, 1.0f, 0.0f, 1.0f,
    0.9f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,//jaune
    1.0f, 0.85f, 0.0f, 1.0f,
    1.0f, 0.7f, 0.0f, 1.0f,
    1.0f, 0.55f, 0.0f, 1.0f,
    1.0f, 0.4f, 0.0f, 1.0f,
    1.0f, 0.25f, 0.0f, 1.0f,
    1.0f, 0.1f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,//rouge
    0.5f, 0.0f, 0.0f, 1.0f //rouge 2
  };
  /* utiliser le programme GPU "_pId" */
  glUseProgram(_pId);

  /* binder (mettre au premier plan, "en courante" ou "en active") la
     matrice model */
  gl4duBindMatrix("model");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  int maxh = 0;
  for(int i = 0; i < _EH; ++i) {
    for(int jj = 0; jj < _EW; ++jj) {
      int j = (i % 2) ? _EW - 1 - jj : jj;
      int mh = ( (_hauteurs[4 * (i * _EW + j) + 0] / 8.0f) +
		 (_hauteurs[4 * (i * _EW + j) + 1] / 8.0f) +
		 (_hauteurs[4 * (i * _EW + j) + 2] / 8.0f) +
		 (_hauteurs[4 * (i * _EW + j) + 3] / 8.0f) ) / 4;
      mh = mh > 16 ? 16 : mh;
      for(int h = 0; h <= mh ; ++h) {
	if(maxh < h) maxh = h;
	/* sauvegarder l'état actuel de la matrice courante */
	gl4duPushMatrix(); {
	  /* composer (multiplication à droite) avec une translation à gauche <-3, 0, 0> */
	  gl4duTranslatef(j * 2.0f - _EW, 0, i * 2.0f - _EH);
	  /* augmenter y en fonction de _hauteur */
	  //gl4duScalef(1.0f, _hauteurs[i * _EW + j] / 16.0, 1.0f);
	  gl4duTranslatef(0.0f, 2 * h, 0.0f);
	  /* rapetisser les cubes à 70% */
	  gl4duScalef(0.7f, 0.7f, 0.7f);
	  /* envoyer les matrice GL4D au programme GPU OpenGL (en cours) */
	  gl4duSendMatrices();
	}
	/* restaurer l'état de la matrice au moment de la sauvegarde */
	gl4duPopMatrix();

	/* dans fragment shader, mettre vert pour la variable "couleur" */
	glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, &colors[4 * (h % 17)]);
	/* booléen pour dire d'utiliser ou pas une texture */

	/* activer l'étage de texture 0 */
	glActiveTexture(GL_TEXTURE0);
	/* binder _texId[0] comme texture bidimensionnelle */
	glBindTexture(GL_TEXTURE_2D, _texId[0]);
	glUniform1i(glGetUniformLocation(_pId, "tex"), 0); /* 0 correspond à GL_TEXTURE0 */
	glUniform1i(glGetUniformLocation(_pId, "use_texture"), 1);
	/* demander le dessin du cube GL4D */
	gl4dgDraw(_cube);
      }
    }
  }
  /* n'utiliser aucun programme GPU (pas nécessaire) */
  glUseProgram(0);
  /* dé-binder la texture */
  glBindTexture(GL_TEXTURE_2D, 0);
}

void quit(void) {
  /* libérer l'identifiant de texture (et la donnée associée en GPU) */
  if(_texId[0]) {
    glDeleteTextures(1, _texId);
    _texId[0] = 0;
  }
}

