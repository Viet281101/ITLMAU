/*!\file window.c
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

static void init(void);
static void resize(int width, int height);
static void draw(void);
static void vue(int laquelle);
static void scene(GLfloat angle);
static void quit(void);

/* dimensions de la fenêtre */
int _ww = 800, _wh = 600;

/* on créé une variable pour stocker l'identifiant du programme GPU */
GLuint _pId = 0;
/* on créé une variable pour stocker l'identifiant de la géométrie d'un cube GL4D */
GLuint _cube = 0;
/* on créé une variable pour stocker l'identifiant de la géométrie d'un tore GL4D */
GLuint _tore = 0;

/*!\brief créé la fenêtre, un screen 2D effacé en noir et lance une
 *  boucle infinie.*/
int main(int argc, char ** argv) {
  /* tentative de création d'une fenêtre pour GL4Dummies */
  if(!gl4duwCreateWindow(argc, argv, /* args du programme */
			 "GL4Dummies' Hello World", /* titre */
			 10, 10, _ww, _wh, /* x,y, largeur, heuteur */
			 GL4DW_SHOWN | GL4DW_RESIZABLE) /* état visible */) {
    /* ici si échec de la création souvent lié à un problème d'absence
     * de contexte graphique ou d'impossibilité d'ouverture d'un
     * contexte OpenGL (au moins 3.2) */
    return 1;
  }
  /* appeler init pour initialiser des paramètres GL et GL4D */
  init();
  /* placer quit comme fonction à appeler au moment du exit */
  atexit(quit);
  /* placer resize comme fonction à appeler au redimensionnement de la fenêtre */
  gl4duwResizeFunc(resize);
  /* placer draw comme fonction à appeler pour dessiner chaque frame */
  gl4duwDisplayFunc(draw);
  /* boucle infinie pour éviter que le programme ne s'arrête et ferme
   * la fenêtre immédiatement */
  gl4duwMainLoop();
  return 0;
}

/* initialise des paramètres GL et GL4D */
void init(void) {
  /* set la couleur d'effacement OpenGL */
  glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
  /* générer un cube en GL4D */
  _cube = gl4dgGenCubef();
  /* générer un tore en GL4D */
  _tore = gl4dgGenTorusf(20, 10, 0.2f);
  /* créer un programme GPU pour OpenGL (en GL4D) */
  _pId = gl4duCreateProgram("<vs>shaders/hello.vs", "<fs>shaders/hello.fs", NULL);
  /* créer dans GL4D une matrice qui s'appelle model ; matrice de
     modélisation qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "model");
  /* créer dans GL4D une matrice qui s'appelle view ; matrice de
     (point de) vue qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "view");
  /* créer dans GL4D une matrice qui s'appelle proj ; matrice de
     projection qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "proj");
  resize(_ww, _wh);
  /* passer le rendu de toutes les faces en mode filaire */
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
  /* activer le test de profondeur */
  glEnable(GL_DEPTH_TEST);
}

void resize(int width, int height) {
  GLfloat inv_ratio;
  _ww = width;
  _wh = height;
  /* déterminer la portion de la fenêtre dans laquelle on rend la vue */
  glViewport(0, 0, _ww, _wh);
  /* calculer l'inverse du ratio fenêtre (multiplicateur de la hauteur du plan near) */
  inv_ratio = _wh / (GLfloat)_ww;
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
  /* effacer le buffer de couleur (image) et le buffer de profondeur d'OpenGL */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /* une variable pour stocker un ange qui incrémente */
  static float a = 0;
  vue(0);
  scene(a);
  vue(1);
  scene(a);
  vue(2);
  scene(a);
  vue(3);
  scene(a);
  /* augmenter l'ange a de 1 */
  a += 1;
}

static void vue(int laquelle) {
  switch(laquelle) {
  case 0:
    /* déterminer la portion de la fenêtre dans laquelle on rend la vue 0 */
    glViewport(0, 0, _ww / 2, _wh / 2);
    /* binder (mettre au premier plan, "en courante" ou "en active") la matrice proj */
    gl4duBindMatrix("proj");
    /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
    gl4duLoadIdentityf();
    /* combiner la matrice courante avec une matrice de projection
       orthogonale. Voir le support de cours pour les six paramètres :
       left, right, bottom, top, near, far */
    gl4duOrthof(-5.0f, 5.0f, -5.0f * _wh / (GLfloat)_ww, 5.0f * _wh / (GLfloat)_ww, 0.0f, 1000.0f);
    /* binder (mettre au premier plan, "en courante" ou "en active") la
       matrice view */
    gl4duBindMatrix("view");
    /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
    gl4duLoadIdentityf();
    /* composer (multiplication à droite) avec une translation dans les z négatifs (-5) */ 
    /* gl4duTranslatef(0, 0, -5); */
    gl4duLookAtf(0, 0, 5, 0, 0, 0, 0, 1, 0);
    break;
  case 1:
    /* déterminer la portion de la fenêtre dans laquelle on rend la vue 0 */
    glViewport(0, _wh / 2, _ww / 2, _wh / 2);
    /* binder (mettre au premier plan, "en courante" ou "en active") la matrice proj */
    gl4duBindMatrix("proj");
    /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
    gl4duLoadIdentityf();
    /* combiner la matrice courante avec une matrice de projection
       orthogonale. Voir le support de cours pour les six paramètres :
       left, right, bottom, top, near, far */
    gl4duOrthof(-5.0f, 5.0f, -5.0f * _wh / (GLfloat)_ww, 5.0f * _wh / (GLfloat)_ww, 0.0f, 1000.0f);
    /* binder (mettre au premier plan, "en courante" ou "en active") la
       matrice view */
    gl4duBindMatrix("view");
    /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
    gl4duLoadIdentityf();
    /* composer (multiplication à droite) avec une translation dans les x négatifs (-5) */ 
    /* gl4duTranslatef(-5, 0, 0); */
    gl4duLookAtf(5, 0, 0, 0, 0, 0, 0, 1, 0);
    break;
  case 2:
    /* déterminer la portion de la fenêtre dans laquelle on rend la vue 0 */
    glViewport(_ww / 2, _wh / 2, _ww / 2, _wh / 2);
    /* binder (mettre au premier plan, "en courante" ou "en active") la matrice proj */
    gl4duBindMatrix("proj");
    /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
    gl4duLoadIdentityf();
    /* combiner la matrice courante avec une matrice de projection
       orthogonale. Voir le support de cours pour les six paramètres :
       left, right, bottom, top, near, far */
    gl4duOrthof(-5.0f, 5.0f, -5.0f * _wh / (GLfloat)_ww, 5.0f * _wh / (GLfloat)_ww, 0.0f, 1000.0f);
    /* binder (mettre au premier plan, "en courante" ou "en active") la
       matrice view */
    gl4duBindMatrix("view");
    /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
    gl4duLoadIdentityf();
    /* composer (multiplication à droite) avec une translation dans les y négatifs (-5) */ 
    /* gl4duTranslatef(0, -5, 0); */
    gl4duLookAtf(0, 5, 0, 0, 0, 0, 0, 0, -1);
    break;
  default:
    /* déterminer la portion de la fenêtre dans laquelle on rend la vue 0 */
    glViewport(_ww / 2, 0, _ww / 2, _wh / 2);
    /* binder (mettre au premier plan, "en courante" ou "en active") la matrice proj */
    gl4duBindMatrix("proj");
    /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
    gl4duLoadIdentityf();
    /* combiner la matrice courante avec une matrice de projection en
       perspective. Voir le support de cours pour les six paramètres :
       left, right, bottom, top, near, far */
    gl4duFrustumf(-1.0f, 1.0f, -1.0f * _wh / (GLfloat)_ww, 1.0f * _wh / (GLfloat)_ww, 1.0f, 1000.0f);
    /* binder (mettre au premier plan, "en courante" ou "en active") la
       matrice view */
    gl4duBindMatrix("view");
    /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
    gl4duLoadIdentityf();
    /* composer (multiplication à droite) avec une translation dans les z négatifs (-5) */ 
    /* gl4duTranslatef(0, 0, -5); */
    gl4duLookAtf(0, 2, 5, 0, 0, 0, 0, 1, 0);
    break;
  }
}

void scene(GLfloat angle) {
  /* utiliser le programme GPU "_pId" */
  glUseProgram(_pId);

  /* binder (mettre au premier plan, "en courante" ou "en active") la
     matrice model */
  gl4duBindMatrix("model");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();

  /* sauvegarder l'état actuel de la matrice courante */
  gl4duPushMatrix(); {
    /* composer (multiplication à droite) avec une translation à gauche <-3, 0, 0> */
    gl4duTranslatef(-3, 0, 0);
    /* composer (multiplication à droite) avec une rotation d'angle a et
       d'axe (autour de l'axe) <0, 1, 0> */
    gl4duRotatef(angle, 0, 1, 0);
    /* envoyer les matrice GL4D au programme GPU OpenGL (en cours) */
    gl4duSendMatrices();
  }
  /* restaurer l'état de la matrice au moment de la sauvegarde */
  gl4duPopMatrix();

  /* dans fragment shader, mettre vert pour la variable "couleur" */
  glUniform4f(glGetUniformLocation(_pId, "couleur"), 0.0f, 1.0f, 0.0f, 1.0f);
  /* demander le dessin du cube GL4D */
  gl4dgDraw(_cube);


  /* sauvegarder l'état actuel de la matrice courante */
  gl4duPushMatrix(); {
    /* composer (multiplication à droite) avec une translation à droite <-3, 0, 0> */
    gl4duTranslatef(3, 0, 0);
    /* composer (multiplication à droite) avec une rotation d'angle -a et
       d'axe (autour de l'axe) <0, 1, 0> */
    gl4duRotatef(-angle, 0, 1, 0);
    /* envoyer les matrice GL4D au programme GPU OpenGL (en cours) */
    gl4duSendMatrices();
  }
  /* restaurer l'état de la matrice au moment de la sauvegarde */
  gl4duPopMatrix();

  /* dans fragment shader, mettre rouge pour la variable "couleur" */
  glUniform4f(glGetUniformLocation(_pId, "couleur"), 1.0f, 0.0f, 0.0f, 1.0f);
  /* demander le dessin du tore GL4D */
  gl4dgDraw(_tore);
  


  /* n'utiliser aucun programme GPU (pas nécessaire) */
  glUseProgram(0);
}


/* appelée lors du exit */
void quit(void) {
  /* nettoyer (libérer) tout objet créé avec GL4D */
  gl4duClean(GL4DU_ALL);
}

