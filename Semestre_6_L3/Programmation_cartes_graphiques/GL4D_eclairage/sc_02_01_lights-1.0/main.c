/*!\file main.c
 *
 * \brief exemple poussé d'éclairage avec atténuation.
 * \author Farès Belhadj, amsi@up8.edu
 * \date May 7, 2024
 */
#include <GL4D/gl4dm.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4duw_SDL2.h>

static void init(void);
static void resize(int width, int height);
static void draw(void);
static void sortie(void);

static GLuint _wW = 640, _wH = 480;
static GLuint _gridId = 0;
static GLuint _pId = 0;

int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "Eclairage", GL4DW_POS_CENTERED, GL4DW_POS_CENTERED,
			 _wW, _wH, GL4DW_OPENGL | GL4DW_RESIZABLE | GL4DW_SHOWN)) {
    fprintf(stderr, "Erreur lors de la création de la fenêtre\n");
    return 1;
  }
  srand(1321);
  SDL_GL_SetSwapInterval(1);
  init();
  atexit(sortie);
  gl4duwResizeFunc(resize);
  gl4duwDisplayFunc(draw);
  gl4duwMainLoop();
  return 0;
}

void init(void) {
  GLfloat * hm = gl4dmTriangleEdge(513, 513, 0.6f);
  _gridId = gl4dgGenGrid2dFromHeightMapf(513, 513, hm);
  free(hm);
  _pId = gl4duCreateProgram("<vs>shaders/lights.vs", "<fs>shaders/lights.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "proj");
  gl4duGenMatrix(GL_FLOAT, "mod");
  gl4duGenMatrix(GL_FLOAT, "view");
  resize(_wW, _wH);

  glClearColor(0.4f, 0.3f, 0.7f, 1.0f);
  glEnable(GL_DEPTH_TEST);
}

void resize(int width, int height) {
  GLfloat ratio;
  _wW = width;
  _wH = height;
  glViewport(0, 0, _wW, _wH);
  ratio = _wW / ((GLfloat)_wH);
  gl4duBindMatrix("proj");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.01f * ratio, 0.01f * ratio, -0.01f, 0.01f, 0.02f, 10.0f);
}

void scene(GLfloat dt) {
  static GLfloat x = 0.0f;
  GLfloat rouge[] = {1.0f, 0.1f, 0.1f, 1.0f}, verdatre[] = { 0.6f, 1.0f, 0.6f, 1.0f };
  GLfloat lum0pos[] = { 0.0f, 0.1f, 0.0f, 1.0f };
  lum0pos[0]  = -cos(x);
  lum0pos[2]  = -cos(x);
  x += dt / 2.0f;
  glUseProgram(_pId);
  /* récupération et envoi de la position de la caméra */
  gl4duBindMatrix("view");
  GLfloat * m = gl4duGetMatrixData(), mp[16];
  memcpy(mp, m, sizeof mp);
  MMAT4INVERSE(mp);
  glUniform3f(glGetUniformLocation(_pId, "vpos"), mp[3], mp[7], mp[11]);

  gl4duBindMatrix("mod");
  gl4duLoadIdentityf();
  gl4duScalef(1.0f, 0.3f, 1.0f);
  glUniform4fv(glGetUniformLocation(_pId, "scolor"), 1, rouge);
  glUniform4fv(glGetUniformLocation(_pId, "lum0color"), 1, verdatre);
  glUniform4fv(glGetUniformLocation(_pId, "lum0pos"), 1, lum0pos);
  glUniform1f(glGetUniformLocation(_pId, "lum0dmax"), 1.5f);
  gl4duSendMatrices();
  gl4dgDraw(_gridId);
  glUseProgram(0);
}

void draw(void) {
  static double t0 = 0.0;
  double t = gl4dGetElapsedTime() / 1000.0, dt = t - t0;
  t0 = t;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(0.8f, 0.05f, 0.85f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  scene(dt);
}

void sortie(void) {
  gl4duClean(GL4DU_ALL);
}
