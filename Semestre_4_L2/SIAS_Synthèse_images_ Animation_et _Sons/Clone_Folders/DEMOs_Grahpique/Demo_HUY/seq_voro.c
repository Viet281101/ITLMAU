/*!\file seq_voro.c
 * \brief GL4Dummies, exemple simple GL4Dummies/OpenGL
 * \author Farès BELHADJ, amsi@up8.edu
 * \date February 10 2021
 */

/* inclusion des entêtes de fonctions de création et de gestion de
 * fenêtres système ouvrant un contexte favorable à GL4dummies. Cette
 * partie est dépendante de la bibliothèque SDL2 */
#include <GL4D/gl4duw_SDL2.h>
/* sous bibliothèque d'utilities GL4Dummies */
#include <GL4D/gl4du.h>
/* sous bibliothèque de géométries GL4Dummies */
#include <GL4D/gl4dg.h>
/* sous bibliothèque demoHelper */
#include <GL4D/gl4dh.h>
#include <assert.h>

/* structure des mobiles */
typedef struct mobile_t mobile_t;
struct mobile_t {
  GLfloat x, y;
  GLfloat c[4];
  GLfloat vx, vy;
};

static void init(void);
static void draw(void);

static void mobile_init(int n);
static void mobile_move(void);
static int  mobile_to_data(GLfloat **coords, GLfloat **colors);
static void mobile_free(void);

/* pointeur vers les mobiles */
static mobile_t * _mobiles = NULL;
/* nombre de mobiles */
static int _nb_mobiles = 0;

/* identifiant du quadrilatère à générer */
GLuint _quad = 0;

/* identifiant du programme GLSL */
GLuint _pId = 0;


void seq_voro(int state) {
  /* INITIALISEZ VOS VARIABLES */
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    init();
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    mobile_free();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    draw();
    return;
  }
}

void init(void) {
  _quad = gl4dgGenQuadf(); 
  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
  _pId = gl4duCreateProgram("<vs>shaders/seq_voro.vs", "<fs>shaders/seq_voro.fs", NULL);
  mobile_init(10);
}

void draw(void) {
  GLint n;
  GLfloat * coords, * colors;
  mobile_move();
  n = mobile_to_data(&coords, &colors);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(_pId);
  glUniform2fv(glGetUniformLocation(_pId, "coords"), n, coords);
  glUniform4fv(glGetUniformLocation(_pId, "colors"), n, colors);
  glUniform1i (glGetUniformLocation(_pId, "nb_mobiles"), n);
  gl4dgDraw(_quad);
  glUseProgram(0);
  free(coords);
  free(colors);
}

void mobile_init(int n) {
  int i, j;
  _mobiles = malloc((_nb_mobiles = n) * sizeof *_mobiles);
  assert(_mobiles);
  for(i = 0; i < _nb_mobiles; ++i) {
    _mobiles[i].x = rand() / (RAND_MAX + 1.0f);
    _mobiles[i].y = rand() / (RAND_MAX + 1.0f);
    for(j = 0; j < 4; ++j)
      _mobiles[i].c[j] = rand() / (RAND_MAX + 1.0f);
    _mobiles[i].vx = 0.5f * (2.0f * (rand() / (RAND_MAX + 1.0f)) - 1.0f);
    _mobiles[i].vy = 0.5f * (2.0f * (rand() / (RAND_MAX + 1.0f)) - 1.0f);
  }
}

void mobile_move(void) {
  int i;
  static GLfloat t0 = -1.0f;
  if(t0 < 0.0f) {
    t0 = gl4dhGetTicks() / 1000.0;
  }
  GLfloat t = gl4dhGetTicks() / 1000.0, dt = t - t0;
  t0 = t;
  for(i = 0; i < _nb_mobiles; ++i) {
    _mobiles[i].x += _mobiles[i].vx * dt;
    _mobiles[i].y += _mobiles[i].vy * dt;
    /* en cas  de collision avec un bord */
    if( (_mobiles[i].x < 0.0f && _mobiles[i].vx < 0.0f) ||
	(_mobiles[i].x >= 1.0f && _mobiles[i].vx > 0.0f) )
      _mobiles[i].vx = -_mobiles[i].vx;
    if( (_mobiles[i].y < 0.0f && _mobiles[i].vy < 0.0f) ||
	(_mobiles[i].y >= 1.0f && _mobiles[i].vy > 0.0f) )
      _mobiles[i].vy = -_mobiles[i].vy;
  }
}

int mobile_to_data(GLfloat **coords, GLfloat **colors) {
  int i, j;
  *coords = malloc(2 * _nb_mobiles * sizeof **coords);
  assert(*coords);
  *colors = malloc(4 * _nb_mobiles * sizeof **colors);
  assert(*colors);
  for(i = 0; i < _nb_mobiles; ++i) {
    (*coords)[2 * i + 0] = _mobiles[i].x;
    (*coords)[2 * i + 1] = _mobiles[i].y;
    for(j = 0; j < 4; ++j)
      (*colors)[4 * i + j] = _mobiles[i].c[j];
  }
  return _nb_mobiles;
}

void mobile_free(void) {
  if(_mobiles) {
    free(_mobiles);
    _mobiles = NULL;
    _nb_mobiles = 0;
  }
}
