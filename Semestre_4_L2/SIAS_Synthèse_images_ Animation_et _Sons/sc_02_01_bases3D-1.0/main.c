#include <GL4D/gl4duw_SDL2.h>
#include <stdio.h>

static void init(void);
static void resize(int width, int height);
static void draw(void);
static void sortie(void);

static GLuint _wW = 640, _wH = 480;
static GLuint _sphereId = 0;
static GLuint _torusId = 0;
static GLuint _pId = 0;

int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "bases 3D", GL4DW_POS_CENTERED, GL4DW_POS_CENTERED,
			 _wW, _wH, GL4DW_OPENGL | GL4DW_RESIZABLE | GL4DW_SHOWN)) {
    fprintf(stderr, "Erreur lors de la création de la fenêtre\n");
    return 1;
  }
  init();
  atexit(sortie);
  gl4duwResizeFunc(resize);
  gl4duwDisplayFunc(draw);
  gl4duwMainLoop();
  return 0;
}

void init(void) {
  glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
  _sphereId = gl4dgGenSpheref(10, 10);
  _torusId = gl4dgGenTorusf(10, 10, 0.3f);
  _pId = gl4duCreateProgram("<vs>shaders/hello.vs", "<fs>shaders/hello.fs", NULL);
  glEnable(GL_DEPTH_TEST);
  /* glEnable(GL_CULL_FACE); */
  /* glCullFace(GL_FRONT); */
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  gl4duGenMatrix(GL_FLOAT, "proj");
  gl4duGenMatrix(GL_FLOAT, "mod");
  gl4duGenMatrix(GL_FLOAT, "view");
  resize(_wW, _wH);
}

static void resize(int width, int height) {
  GLfloat ratio;
  _wW = width;
  _wH = height;
  glViewport(0, 0, _wW, _wH);
  ratio = _wW / ((GLfloat)_wH);
  gl4duBindMatrix("proj");
  gl4duLoadIdentityf();
  /* gl4duOrthof(-1 * ratio, 1 * ratio, -1 /\* / ratio *\/, 1 /\* / ratio *\/, -1, 1); */
  gl4duFrustumf(-1 * ratio, 1 * ratio, -1 /* / ratio */, 1 /* / ratio */, 2, 100);
}

void scene(GLfloat a) {
  GLfloat rouge[] = {1.0f, 0, 0, 1.0f}, bleu[] = {0, 0, 1.0f, 1.0f};
  gl4duBindMatrix("mod");
  gl4duLoadIdentityf();
  gl4duRotatef(a, 0, 1, 0);
  glUseProgram(_pId);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, rouge);
  gl4dgDraw(_sphereId);
  gl4duTranslatef(3.0f, 0, 0);
  gl4duRotatef(90, 0, 1, 0);
  gl4duRotatef(90, 1, 0, 0);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "couleur"), 1, bleu);
  gl4dgDraw(_torusId);
  glUseProgram(0);

}

void draw(void) {
  static double t0 = 0.0;
  double t = gl4dGetElapsedTime() / 1000.0, dt = t - t0;
  t0 = t;
  static GLfloat a = 0.0f, y = 0.0f;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /* vue 1 */
  glViewport(0, 0, _wW / 2, _wH / 2);
  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(0, y, 8.0f, 0, 0, 0, 0, 1.0f, 0);
  scene(a);
  /* vue 2 */
  glViewport(_wW / 2, 0, _wW / 2, _wH / 2);
  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(8.0f, y, 0.0f, 0, 0, 0, 0, 1.0f, 0);
  scene(a);

  a += 180.0f * dt;
  //y += 0.5f * dt;
}

void sortie(void) {
  gl4duClean(GL4DU_ALL);
}
