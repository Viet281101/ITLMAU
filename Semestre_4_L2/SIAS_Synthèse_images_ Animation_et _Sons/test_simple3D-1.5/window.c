/*!\file window.c
 * \brief GL4Dummies, exemple simple 3D avec GL4Dummies
 * textures avec chargement depuis un fichier
 * \author Farès BELHADJ, amsi@up8.edu
 * \date February 20 2023
 */

/* inclusion des entêtes de fonctions de création et de gestion de
 * fenêtres système ouvrant un contexte favorable à GL4dummies. Cette
 * partie est dépendante de la bibliothèque SDL2 */
#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dm.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>

/* inclure le support SDL2_image */
#include <SDL_image.h>

static void init(void);
static void resize(int width, int height);
static void keydown(int keycode);
static void simu(void);
static void draw(void);
static void vue(int laquelle);
static void scene(GLfloat angle);
static void quit(void);

/* dimensions de la fenêtre */
static int _ww = 1024, _wh = 768;

/* on créé une variable pour stocker l'identifiant du programme GPU */
static GLuint _pId = 0;
/* on créé une variable pour stocker l'identifiant de la géométrie d'un cube GL4D */
static GLuint _cube = 0;
/* on créé une variable pour stocker l'identifiant de la géométrie d'un tore GL4D */
static GLuint _tore = 0;
/* flag pour switcher d'une multi-vues à mono-vue (perspective) */
static GLboolean _multi_views = GL_FALSE;
/* z de la caméra */
static GLfloat _z = 5.0f;

/* des identifiants de textures */
static GLuint _texId[2] = { 0, 0 };

/* on met l'angle qui permet de faire tourner les objet en globale */
static GLfloat _angle = 0.0f;

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
  /* activer la synchronisation verticale */
  SDL_GL_SetSwapInterval(1);
  /* appeler init pour initialiser des paramètres GL et GL4D */
  init();
  /* placer quit comme fonction à appeler au moment du exit */
  atexit(quit);
  /* placer une fonction callback à l'événement touche de clavier pressée */
  gl4duwKeyDownFunc(keydown);
  /* placer resize comme fonction à appeler au redimensionnement de la fenêtre */
  gl4duwResizeFunc(resize);
  /* placer simu comme fonction à appeler lors du idle (temps qui arrive juste avant draw) */
  gl4duwIdleFunc(simu);
  /* placer draw comme fonction à appeler pour dessiner chaque frame */
  gl4duwDisplayFunc(draw);
  /* boucle infinie pour éviter que le programme ne s'arrête et ferme
   * la fenêtre immédiatement */
  gl4duwMainLoop();
  return 0;
}

/* initialise des paramètres GL et GL4D */
void init(void) {
  GLuint image_0[] = { (0xFF << 24) | 0xFF, (0xFF << 24) | (0xFF << 8) | 0xFF, (0xFF << 24) | (0xFF << 8), -1 };
  /* générer un identifiant de texture */
  glGenTextures(2, _texId);
  assert(_texId[0] && _texId[1]);
  /* binder _texId[0] comme texture bidimensionnelle */
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  /* comportement de l'interpolation en minimisant puis maximisant la texture */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  /* spécification et transfert de la donnée */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_0);
  /* dé-binder la texture bidimensionnelle */
  glBindTexture(GL_TEXTURE_2D, 0);

  {
    /* transférer une texture depuis fichier -> RAM-CPU -> RAM-GPU */
    /* première résolution de texture depuis le fichier */
    SDL_Surface * s = NULL, * d;
    s = IMG_Load("images/01.png");
    assert(s);
    d = SDL_CreateRGBSurface(0, s->w, s->h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
    SDL_BlitSurface(s, NULL, d, NULL);
    SDL_FreeSurface(s);
    glActiveTexture(GL_TEXTURE0);
    /* binder _texId[1] comme texture bidimensionnelle */
    glBindTexture(GL_TEXTURE_2D, _texId[1]);
    /* comportement de l'interpolation en minimisant puis maximisant la texture */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /* spécification et transfert de la donnée */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d->w, d->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d->pixels);
    SDL_FreeSurface(d);
    /* deuxième résolution de texture depuis le fichier puis toutes les autres sont générées automatiquement */
    s = IMG_Load("images/02.png");
    assert(s);
    /* dans cette boucle, on prend "images/02.png" telle quelle, en
       level = 1, puis on la réduit progressivement, à chaque tour, en
       divisant par 2 les dimensions. */
    for(int w = s->w, h = s->h, level = 1; w > 0 && h > 0; w /= 2, h /= 2, ++level) {
      SDL_Rect R = { 0, 0, w, h };
      d = SDL_CreateRGBSurface(0, w, h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
      /* remplacer le BlitSurface par le BlitScaled pour changer de résolution */
      SDL_BlitScaled(s, NULL, d, &R);
      /* spécification et transfert de la donnée */
      glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, d->w, d->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);
    /* dé-binder la texture bidimensionnelle */
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  
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

void keydown(int keycode) {
  switch(keycode) {
  case GL4DK_UP:
    _z -= 0.1f;
    break;
  case GL4DK_DOWN:
    _z += 0.1f;
    break;
  case GL4DK_m:
    _multi_views = !_multi_views;
    break;
  case GL4DK_ESCAPE:
    exit(0);
    break;
  default:
    fprintf(stderr, "touche pressee : %d\n", keycode);
    break;
  }
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

/* cette fonction servira simplemment à modifier la variable _angle en
 * fonction du temps passé entre deux simulations (appel à la idle
 * func) */
void simu(void) {
  static double t0 = 0.0;
  double t = gl4dGetElapsedTime() / 1000.0, dt = t - t0;
  t0 = t;
  _angle += 90.0 * dt;
}

void draw(void) {
  /* effacer le buffer de couleur (image) et le buffer de profondeur d'OpenGL */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if(_multi_views) {
    vue(0);
    scene(_angle);
    vue(1);
    scene(_angle);
    vue(2);
    scene(_angle);
    vue(3);
    scene(_angle);
  } else {
    vue(4);
    scene(_angle);
  }
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
  case 3:
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
    gl4duLookAtf(0, 2, _z, 0, 0, 0, 0, 1, 0);
    break;
  default: /* mono-vue obtenue dans case 4 */
    /* déterminer la portion de la fenêtre dans laquelle on rend la vue 0 */
    glViewport(0, 0, _ww, _wh);
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
    gl4duLookAtf(0, 2, _z, 0, 0, 0, 0, 1, 0);
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
  glUniform4f(glGetUniformLocation(_pId, "couleur"), 0.5f, 1.0f, 0.5f, 1.0f);
  /* booléen pour dire d'utiliser ou pas une texture */

  /* activer l'étage de texture 0 */
  glActiveTexture(GL_TEXTURE0);
  /* binder _texId[1] comme texture bidimensionnelle */
  glBindTexture(GL_TEXTURE_2D, _texId[1]);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0); /* 0 correspond à GL_TEXTURE0 */
  glUniform1i(glGetUniformLocation(_pId, "use_texture"), 1);
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

  /* dans fragment shader, mettre blanc pour la variable "couleur" */
  glUniform4f(glGetUniformLocation(_pId, "couleur"), 1.0f, 1.0f, 1.0f, 1.0f);

  /* activer l'étage de texture 0 */
  glActiveTexture(GL_TEXTURE0);
  /* binder _texId[0] comme texture bidimensionnelle */
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0); /* 0 correspond à GL_TEXTURE0 */
  /* booléen pour dire d'utiliser ou pas une texture */
  glUniform1i(glGetUniformLocation(_pId, "use_texture"), 1);

  /* demander le dessin du tore GL4D */
  gl4dgDraw(_tore);
  
  /* dé-binder la texture bidimensionnelle */
  glBindTexture(GL_TEXTURE_2D, 0);


  /* n'utiliser aucun programme GPU (pas nécessaire) */
  glUseProgram(0);
}


/* appelée lors du exit */
void quit(void) {
  /* libérer l'identifiant de texture (et la donnée associée en GPU) */
  if(_texId[0]) {
    glDeleteTextures(2, _texId);
    _texId[0] = 0;
  }
  /* nettoyer (libérer) tout objet créé avec GL4D */
  gl4duClean(GL4DU_ALL);
}

