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
static void draw(void);
static void quit(void);

/* on créé une variable pour stocker l'identifiant du programme GPU */
GLuint _pId = 0;
/* on créé une variable pour stocker l'identifiant de la géométrie d'un cube GL4D */
GLuint _cube = 0;

/*!\brief créé la fenêtre, un screen 2D effacé en noir et lance une
 *  boucle infinie.*/
int main(int argc, char ** argv) {
  /* tentative de création d'une fenêtre pour GL4Dummies */
  if(!gl4duwCreateWindow(argc, argv, /* args du programme */
			 "GL4Dummies' Hello World", /* titre */
			 10, 10, 800, 600, /* x,y, largeur, heuteur */
			 GL4DW_SHOWN) /* état visible */) {
    /* ici si échec de la création souvent lié à un problème d'absence
     * de contexte graphique ou d'impossibilité d'ouverture d'un
     * contexte OpenGL (au moins 3.2) */
    return 1;
  }
  /* appeler init pour initialiser des paramètres GL et GL4D */
  init();
  /* placer quit comme fonction à appeler au moment du exit */
  atexit(quit);
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
  /* créer un programme GPU pour OpenGL (en GL4D) */
  _pId = gl4duCreateProgram("<vs>shaders/hello.vs", "<fs>shaders/hello.fs", NULL);
  /* créer dans GL4D une matrice qui s'appelle modview ; matrice de
     modélisation et vue qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "modview");
  /* créer dans GL4D une matrice qui s'appelle proj ; matrice de
     projection qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "proj");
  /* binder (mettre au premier plan, "en courante" ou "en active") la matrice proj */
  gl4duBindMatrix("proj");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  /* combiner la matrice courante avec une matrice de projection en
     perspective. Voir le support de cours pour les six paramètres :
     left, right, bottom, top, near, far */
  gl4duFrustumf(-1, 1, -1, 1, 1, 1000);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE /*GL_FILL*/);
}

void draw(void) {
  
  /* une variable pour stocker un ange qui incrémente */
  static float a = 0;
  /* set une couleur d'effacement random pour OpenGL */
  //glClearColor(gl4dmURand(), gl4dmURand(), gl4dmURand(), 1.0);
  /* effacer le buffer de couleur (image) et le buffer de profondeur d'OpenGL */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /* utiliser le programme GPU "_pId" */
  glUseProgram(_pId);
  /* binder (mettre au premier plan, "en courante" ou "en active") la
     matrice modview */
  gl4duBindMatrix("modview");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  /* composer (multiplication à droite) avec une rotation d'angle a et
     d'axe (autour de l'axe) <0, 1, 0> */
   // gl4duRotatef(a, 0, 1, 0);

   // P = Id * Front -> P = Id * Front * sommet
   // M = Id * R * T * sommet
  
  /* composer (multiplication à droite) avec une translation dans les z négatifs (-5) */ 
  
  // rotation horizontale
  gl4duTranslatef(-2, 0, -5);
  gl4duRotatef(a, 0, 1, 0);
  gl4duSendMatrices();
  gl4dgDraw(_cube);

  // rotation verticale
  gl4duLoadIdentityf();
  gl4duTranslatef(2, 0, -5);
  gl4duRotatef(a / 2.0f, 1, 0, 0);

  /* envoyer les matrice GL4D au programme GPU OpenGL (en cours) */
  gl4duSendMatrices();
  /* demander le dessin d'un objet GL4D */
  gl4dgDraw(_cube);
  /* n'utiliser aucun programme GPU (pas nécessaire) */
  glUseProgram(0);
  /* augmenter l'ange a de 1 */
  a += 1;
}

/* appelée lors du exit */
void quit(void) {
  /* nettoyer (libérer) tout objet créé avec GL4D */
  gl4duClean(GL4DU_ALL);
}

