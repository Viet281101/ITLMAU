/*!\file spectre_3d.c
 * \brief GL4Dummies, exemple simple 3D avec GL4Dummies
 * \author Farès BELHADJ, amsi@up8.edu
 * \date February 03 2022
 */

/* inclusion des entêtes de fonctions de création et de gestion de
 * fenêtres système ouvrant un contexte favorable à GL4dummies. Cette
 * partie est dépendante de la bibliothèque SDL2 */
#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dm.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4dh.h>
#include "audioHelper.h"

static void init(void);
static void draw(void);
static void quit(void);

/* mon plateau de 64x64 cubes */
const int _EW = 25, _EH = 25;

/* on créé une variable pour stocker l'identifiant du programme GPU */
static GLuint _pId = 0;
/* on créé une variable pour stocker l'identifiant de la géométrie d'un cube GL4D */
static GLuint _cube = 0;

/* des identifiants de textures */
static GLuint _texId[1] = { 0 };


/*!\brief nombre d'échantillons du signal sonore */
#define ECHANTILLONS 625
/*!\brief amplitude des échantillons du signal sonore */
static Sint16 _hauteurs[ECHANTILLONS];


void spectre_3d(int state) {
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
    if(len >= 5 * ECHANTILLONS)
      for(i = 0; i < ECHANTILLONS; i++)
        _hauteurs[i] = 256 * s[i] / ((1 << 15) + 1.0);
    return;
  default: /* GL4DH_DRAW */
    draw();
    return;
  }
}






/* initialise des paramètres GL et GL4D */
void init(void) {
  GLuint image_0[] = { -1, -1, -1, -1 };
  GLfloat inv_ratio;
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);
  assert(_EW * _EH == ECHANTILLONS);
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
  
  /* générer un cube en GL4D */
  _cube = gl4dgGenCubef();
  /* créer un programme GPU pour OpenGL (en GL4D) */
  _pId = gl4duCreateProgram("<vs>shaders/spectre_3d.vs", "<fs>shaders/spectre_3d.fs", NULL);
  /* créer dans GL4D une matrice qui s'appelle model ; matrice de
     modélisation qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "model");
  /* créer dans GL4D une matrice qui s'appelle view ; matrice de
     (point de) vue qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "view");
  /* créer dans GL4D une matrice qui s'appelle proj ; matrice de
     projection qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "proj");


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
}

void draw(void) {
  GLboolean dt = glIsEnabled(GL_DEPTH_TEST);
  /* activer le test de profondeur */
  glEnable(GL_DEPTH_TEST);
  
  /* set la couleur d'effacement OpenGL */
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  /* effacer le buffer de couleur (image) et le buffer de profondeur d'OpenGL */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gl4duBindMatrix("view");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  /* composer (multiplication à droite) avec une translation dans les z négatifs (-5) */ 
  /* gl4duTranslatef(0, 0, -5); */
  gl4duLookAtf(-10, 30, 50, 0, 0, 0, 0, 1, 0);


  /* utiliser le programme GPU "_pId" */
  glUseProgram(_pId);

  /* binder (mettre au premier plan, "en courante" ou "en active") la
     matrice model */
  gl4duBindMatrix("model");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();

  for(int i = 0; i < _EH * _EW; ++i) {   
    /* sauvegarder l'état actuel de la matrice courante */
    gl4duPushMatrix(); {
      /* composer (multiplication à droite) avec une translation à gauche <-3, 0, 0> */
      gl4duTranslatef((i - ECHANTILLONS / 2) * 2.0f * 0.1, 0, 0);
      /* augmenter y en fonction de _hauteur */
      //gl4duScalef(1.0f, _hauteurs[i * _EW + j] / 16.0, 1.0f);
      gl4duTranslatef(0.0f, _hauteurs[i] / 8.0, 0.0f);
      /* rapetisser les cubes à 80% */
      gl4duScalef(0.1f, 0.8f, 0.8f);
      /* envoyer les matrice GL4D au programme GPU OpenGL (en cours) */
      gl4duSendMatrices();
    }
    /* restaurer l'état de la matrice au moment de la sauvegarde */
    gl4duPopMatrix();
    
    /* dans fragment shader, mettre vert pour la variable "couleur" */
    glUniform4f(glGetUniformLocation(_pId, "couleur"), 1.0f, 1.0f, 1.0f, 1.0f);

    /* activer l'étage de texture 0 */
    glActiveTexture(GL_TEXTURE0);
    /* binder _texId[0] comme texture bidimensionnelle */
    glBindTexture(GL_TEXTURE_2D, _texId[0]);
    glUniform1i(glGetUniformLocation(_pId, "tex"), 0); /* 0 correspond à GL_TEXTURE0 */
    /* booléen pour dire d'utiliser ou pas une texture */
    glUniform1i(glGetUniformLocation(_pId, "use_texture"), 1);
    /* demander le dessin du cube GL4D */
    gl4dgDraw(_cube);
  }
  /* n'utiliser aucun programme GPU (pas nécessaire) */
  glUseProgram(0);
  /* désactiver le test de profondeur si nécessaire */
  if(!dt)
    glDisable(GL_DEPTH_TEST);
}

/* appelée lors du exit */
void quit(void) {
  /* libérer l'identifiant de texture (et la donnée associée en GPU) */
  if(_texId[0]) {
    glDeleteTextures(1, _texId);
    _texId[0] = 0;
  }
}
