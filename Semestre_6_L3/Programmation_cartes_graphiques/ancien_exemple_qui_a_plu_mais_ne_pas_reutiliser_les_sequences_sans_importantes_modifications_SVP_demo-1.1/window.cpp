/*!\file window.cpp
 *
 * \brief Utilisation de GL4Dummies pour réaliser une démo.
 *
 * Ici est géré l'ouverture de la fenêtre ainsi que l'ordonnancement
 * des animations. Apriori les seuls éléments à modifier ici lors de
 * votre intégration sont le tableau static \ref _animations et le nom
 * du fichier audio à lire.
 *
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date May 05, 2014 - February 26, 2016
 */
#include <stdlib.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dh.h>
#include <GL4D/gl4duw_SDL2.h>
#include "animations.h"
#include "audioHelper.h"

/* Prototypes des fonctions statiques contenues dans ce fichier C. */
static void init(void);
static void quit(void);
static void resize(int w, int h);
static void keydown(int keycode);

/*!\brief tableau contenant les animations sous la forme de timeline,
 * ce tableau se termine toujours par l'élémént {0, NULL, NULL,
 * NULL} */
static GL4DHanime _animations[] = {
  { 18000, obj_loader, NULL, NULL },
  {  2000, obj_loader, light_n_tex, exemple_de_transition_01 },
  {  5000, light_n_tex, NULL, NULL },
  { 10000, light_n_tex, random_anim, exemple_de_transition_01 },
  {  6000, random_anim, NULL, NULL },
  {  5000, random_anim, heightmap, exemple_de_transition_01 },
  {  3000, heightmap, NULL, NULL },
  {  5000, heightmap, spectre, exemple_de_transition_01 },
  { 10000, spectre, NULL, NULL },
  {    0, NULL, NULL, NULL } /* Toujours laisser à la fin */
};

/*!\brief dimensions initiales de la fenêtre */
static GLfloat _dim[] = {1024, 768};

/*!\brief fonction principale : initialise la fenêtre, OpenGL, audio
 * et lance la boucle principale (infinie).
 */
int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "GL4Dummies DemoHelper", 
			 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			 _dim[0], _dim[1],
			 SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwResizeFunc(resize);
  gl4duwKeyDownFunc(keydown);
  gl4duwDisplayFunc(gl4dhDraw);

  ahInitAudio("audio/power.mp3");
  gl4duwMainLoop();
  return 0;
}

/*!\brief Cette fonction initialise les paramètres et éléments OpenGL
 * ainsi que les divers données et fonctionnalités liées à la gestion
 * des animations.
 */
static void init(void) {
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  gl4dhInit(_animations, _dim[0], _dim[1], animationsInit);
  resize(_dim[0], _dim[1]);
}

/*!\brief paramétre la vue (viewPort) OpenGL en fonction des
 * dimensions de la fenêtre.
 * \param w largeur de la fenêtre.
 * \param w hauteur de la fenêtre.
 */
static void resize(int w, int h) {
  _dim[0] = w; _dim[1] = h;
  glViewport(0, 0, _dim[0], _dim[1]);
}

/*!\brief permet de gérer les évènements clavier-down.
 * \param keycode code de la touche pressée.
 */
static void keydown(int keycode) {
  switch(keycode) {
  case SDLK_ESCAPE:
  case 'q':
    exit(0);
  default: break;
  }
}

/*!\brief appelée à la sortie du programme (atexit).
 */
static void quit(void) {
  ahClean();
  gl4duClean(GL4DU_ALL);
}
