#include <GL4D/gl4du.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL_image.h>
#include <assert.h>

/* Prototypes des fonctions statiques contenues dans ce fichier C */
static void init(void);
static void draw(void);
static void quit(void);

/*!\brief largeur et hauteur de la fenêtre */
static int _wW = 800, _wH = 600;
/*!\brief largeur et hauteur de la texture */
static int _tW = 0, _tH = 0;
/*!\brief identifiant du (futur) GLSL program */
static GLuint _pId = 0;
/*!\brief identifiant de framebuffer */
static GLuint _fbo = 0;
/*!\brief identifiant du plan */
static GLuint _quad = 0;
/*!\brief identifiant de textures */
static GLuint _texId[] = { 0, 0 };

static GLint _out = 1;

/*!\brief créé la fenêtre d'affichage, initialise GL et les données,
 * affecte les fonctions d'événements et lance la boucle principale
 * d'affichage.
 */
int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "GL4Dummies", 20, 20, 
			 _wW, _wH, GL4DW_RESIZABLE | GL4DW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwDisplayFunc(draw);
  gl4duwMainLoop();
  return 0;
}
/*!\brief initialise les paramètres OpenGL et les données. 
 *
 * Exercice : texturer le vao.
 */
static void init(void) {
  _quad = gl4dgGenQuadf();
  _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/basic.fs", NULL);
  SDL_Surface * s = IMG_Load("images/map.png");
  assert(s);
  assert(s->format->BytesPerPixel == 3);
  _tW = s->w;
  _tH = s->h;
  // s->pixels est le tableau brut de pixels (en CPU)
  glGenTextures(2, _texId);
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  /* transfert CPU->GPU avec description */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, _tW, _tH, 0, GL_RGB, GL_UNSIGNED_BYTE, s->pixels);

  glBindTexture(GL_TEXTURE_2D, _texId[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  /* transfert CPU->GPU avec description */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, _tW, _tH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  /* effacer la texture du CPU */
  SDL_FreeSurface(s);
  glBindTexture(GL_TEXTURE_2D, 0);  

  glGenFramebuffers(1, &_fbo);

}
/*!\brief Cette fonction dessine dans le contexte OpenGL actif. */
static void draw(void) {
  glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texId[_out],  0);
  glViewport(0, 0, _tW, _tH);
  /* effacement du buffer de couleur */
  glClear(GL_COLOR_BUFFER_BIT);
  /* activation du programme _pId */
  glUseProgram(_pId);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[(_out + 1) % 2]);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0); // le 0 correspond à glActiveTexture(GL_TEXTURE0);

  gl4dgDraw(_quad);
  glBindTexture(GL_TEXTURE_2D, 0);  
  /* dé-lier le VAO */
  glBindVertexArray(0);
  /* désactiver le programme shader */
  glUseProgram(0);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(0, 0, _tW, _tH, 0, 0, _wW, _wH, GL_COLOR_BUFFER_BIT, GL_LINEAR);
  /* SDL_Delay(100); */
  _out = (_out + 1) % 2;
}
/*!\brief appelée au moment de sortir du programme (atexit), elle
 *  libère les éléments OpenGL utilisés.*/
static void quit(void) {
  /* suppression de la texture */
  if(_texId[0])
    glDeleteTextures(2, _texId);
  /* suppression du fbo */
  if(_fbo)
    glDeleteFramebuffers(1, &_fbo);
  /* nettoyage des éléments utilisés par la bibliothèque GL4Dummies */
  gl4duClean(GL4DU_ALL);
}
