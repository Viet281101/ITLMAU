#include <stdio.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4df.h>
#include <GL4D/gl4duw_SDL2.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdbool.h>

#include "utils.h"
#include "scene.h"

/* orientation et position de la caméra */
typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat theta;
} cam_t;

/* indexation des touches pour les commandes de direction */
typedef enum {
    KEYS_LEFT = 0,
    KEYS_RIGHT,
    KEYS_UP,
    KEYS_DOWN
} keys_t;

/* Prototypes des fonctions statiques contenues dans ce fichier C */
static void initGL(void);
static void resize(int w, int h);
static void draw(void);
static void key_down(int keycode);
static void key_up(int keycode);
static void passive_motion(int x, int y);
static void idle(void);
static void quit(void);
static void initAudio(const char * filename);
static void mixCallback(void *udata, Uint8 *stream, int len);

/* dimensions de la fenêtre */
static int _wW = 800, _wH = 600;

/* camera */
static cam_t cam = { 0.0, 2.0, 25.0, 0.0 };

/* état des touches de contrôle */
bool keys[] = { false, false, false, false };

/* position de la souris modifiés pas les fonctions de déplacement */
GLfloat mouse_x = 300;
GLfloat mouse_y = 300;

/* scene dans laquelle seront stockés les objets à dessiner */
scene_t scene;

/* ***************************************************** */
/* MUSIQUE */
/*!\brief nombre d'échantillons du signal sonore */
#define ECHANTILLONS 1024
/* amplitude des échantillons du signal sonore */
static Sint16 _hauteurs[ECHANTILLONS];
/* pointeur vers la musique chargée par SDL_Mixer */
static Mix_Music * _mmusic = NULL;

/* Cette fonction est appelée quand l'audio est joué et met
 * dans \a stream les données audio de longueur \a len.
 * \param udata pour user data, données passées par l'utilisateur, ici NULL.
 * \param stream flux de données audio.
 * \param len longueur de \a stream. */
static void mixCallback(void *udata, Uint8 *stream, int len) {
  int i;
  Sint16 *s = (Sint16 *)stream;
  if(len >= 2 * ECHANTILLONS)
    for(i = 0; i < ECHANTILLONS; i++)
      _hauteurs[i] = _wH / 2 + (_wH / 2) * s[i] / ((1 << 15) - 1.0);
  return;
}

/*Cette fonction initialise les paramètres SDL_Mixer et charge le fichier audio.*/
static void initAudio(const char * filename) {
  int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_MOD, res;
  res = Mix_Init(mixFlags);
  if( (res & mixFlags) != mixFlags ) {
    fprintf(stderr, "Mix_Init: Erreur lors de l'initialisation de la bibliotheque SDL_Mixer\n");
    fprintf(stderr, "Mix_Init: %s\n", Mix_GetError());
    //exit(3); commenté car ne réagit correctement sur toutes les architectures
  }
  if(Mix_OpenAudio(44100, AUDIO_S16LSB, 2, 1024) < 0)
    exit(4);
  if(!(_mmusic = Mix_LoadMUS(filename))) {
    fprintf(stderr, "Erreur lors du Mix_LoadMUS: %s\n", Mix_GetError());
    exit(5);
  }
  Mix_SetPostMix(mixCallback, NULL);
  if(!Mix_PlayingMusic())
    Mix_PlayMusic(_mmusic, 1);
}

/* ***************************************************** */
/* CONTROLS */

/* enfoncement des touches */
static void
key_down(int keycode)
{
  GLint v[2];
  switch (keycode)
  {
    case GL4DK_LEFT:
    keys[KEYS_LEFT] = true;
    break;
    case GL4DK_RIGHT:
    keys[KEYS_RIGHT] = true;
    break;
    case GL4DK_UP:
    keys[KEYS_UP] = true;
    break;
    case GL4DK_DOWN:
    keys[KEYS_DOWN] = true;
    break;
    case GL4DK_ESCAPE:
    case 'q':
    exit(EXIT_SUCCESS);
    case 'w':
    /* 'w' pour passer du mode fil-de-fer au mode plein */
    glGetIntegerv(GL_POLYGON_MODE, v);
    if (v[0] == GL_FILL)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glLineWidth(3.0);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glLineWidth(1.0);
    }
    break;
    default:
    break;
  }
}

/* relachement des touches */
static void
key_up(int keycode)
{
  switch (keycode)
  {
    case GL4DK_LEFT:
    keys[KEYS_LEFT] = false;
    break;
    case GL4DK_RIGHT:
    keys[KEYS_RIGHT] = false;
    break;
    case GL4DK_UP:
    keys[KEYS_UP] = false;
    break;
    case GL4DK_DOWN:
    keys[KEYS_DOWN] = false;
    break;
    default:
    break;
  }
}

static void
passive_motion(int x, int y)
{
  // mouse_x = x;
  // mouse_y = y;
}

/* mise à jour de la position en fonction des déplacements */
static void
idle()
{
  double dt, dtheta = M_PI / 12, step = 1.0;
  static double t0 = 0, t;

  static double ttotal = 0;
  dt = ((t = gl4dGetElapsedTime()) - t0) / 1000.0;
  t0 = t;
  ttotal += dt;

  // if (keys[KEYS_LEFT])
  // {
  //   cam.theta += dt * dtheta;
  // }
  // if (keys[KEYS_RIGHT])
  // {
  //   cam.theta -= dt * dtheta;
  // }

  GLfloat delta_x = 0.0;
  GLfloat delta_z = 0.0;
  GLfloat delta_y = 0.0;

  // if (keys[KEYS_UP])
  // {
  //   delta_x -= dt * step * sin(cam.theta) * 5;
  //   delta_z -= dt * step * cos(cam.theta) * 5;
  // }
  // if (keys[KEYS_DOWN])
  // {
  //   delta_x += dt * step * sin(cam.theta);
  //   delta_z += dt * step * cos(cam.theta);
  // }

  /* ANIMATION */
  if (ttotal > 10.0 && ttotal < 13)
  {
    delta_x -= dt * step * sin(cam.theta);
    delta_z -= dt * step * cos(cam.theta);
  }
  if (ttotal > 25 && ttotal < 31)
  {
    delta_x -= dt * step * sin(cam.theta) * 3;
    delta_z -= dt * step * cos(cam.theta) * 3;
  }
  if (ttotal > 31 && ttotal < 37)
  {
    cam.theta += dt * dtheta / 6;
    delta_x -= dt * step * sin(cam.theta) / 2;
    delta_z -= dt * step * cos(cam.theta) / 2;
  }
  if (ttotal >= 37 && ttotal < 42)
  {
    cam.theta += dt * dtheta / 6;
    delta_y -= dt * step * cos(cam.theta) / 6;
  }
  if (ttotal > 55 && ttotal < 63)
  {
    cam.theta -= dt * dtheta / 4;
    delta_y += dt * step * cos(cam.theta) / 6;
  }
  if (ttotal > 65 && ttotal < 68)
  {
    delta_x -= dt * step * sin(cam.theta);
    delta_z -= dt * step * cos(cam.theta);
  }
  if (ttotal >= 68 && ttotal < 71)
  {
    delta_x -= dt * step * sin(cam.theta) * 2;
    delta_z -= dt * step * cos(cam.theta) * 2;
  }
  if (ttotal >= 71 && ttotal < 73)
  {
    delta_x -= dt * step * sin(cam.theta) / 4;
    delta_z -= dt * step * cos(cam.theta) / 4;
  }
  if (ttotal >= 73 && ttotal < 80)
  {
    cam.theta -= dt * dtheta;
    delta_y += dt * step * cos(cam.theta) / 4;
  }
  if (ttotal >= 88 && ttotal < 96)
  {
    cam.theta += dt * dtheta * 0.90;
    delta_y -= dt * step * cos(cam.theta) / 2;
  }
  if (ttotal >= 98 && ttotal < 108)
  {
    delta_x -= dt * step * sin(cam.theta) * 2.5;
    delta_z -= dt * step * cos(cam.theta) * 2.5;
  }

  cam.x += delta_x;
  cam.y += delta_y;
  cam.z += delta_z;
  // printf("delta = %f\n", ttotal);
}

/* ***************************************************** */

/*!\brief initialise les paramètres OpenGL et les données */
static void
initGL(void)
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);

  /* couleur de fond */
  glClearColor(0.0f, 0.2f, 0.2f, 1.0f);

  /* matrices */
  gl4duGenMatrix(GL_FLOAT, "modelMatrix");
  gl4duGenMatrix(GL_FLOAT, "viewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");

  scene_init(&scene);
  resize(_wW, _wH);

  /* une dernière texture vide pour y faire des calculs d'effets */
  // glBindTexture(GL_TEXTURE_2D, _tex[4]);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _wW / 2, _wH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  // glEnable(GL_TEXTURE_2D);
}

/* paramétre la vue (viewport) OpenGL en fonction des dimensions de la fenêtre. */
static void
resize(int w, int h)
{
  _wW  = w; _wH = h;
  glViewport(0, 0, _wW, _wH);
  gl4duBindMatrix("projectionMatrix");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5, 0.5, -0.5 * _wH / _wW, 0.5 * _wH / _wW, 1.0, 1000.0);
  gl4duBindMatrix("modelMatrix");
}

void
display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gl4duBindMatrix("viewMatrix");
  gl4duLoadIdentityf();
  gl4duLookAtf(
    cam.x, cam.y, cam.z,
    cam.x - sin(cam.theta), cam.y - (mouse_y - (_wW >> 1)) / (GLfloat) _wH, cam.z - cos(cam.theta),
    0.0, 2.0, 0.0);

  scene_draw(&scene);
}

/* dessine dans le contexte OpenGL actif. */
static void
draw(void)
{
  display();
}

/*!\brief appelée au moment de sortir du programme (atexit), libère les éléments utilisés */
static void
quit(void)
{
  gl4duClean(GL4DU_ALL);
}

/* La fonction principale créé la fenêtre d'affichage,
initialise GL et les données, affecte les fonctions d'événements et
lance la boucle principale d'affichage. */
int
main(int argc, char** argv)
{
  /* fenêtre */
  if(!gl4duwCreateWindow(argc, argv, "API8_2018_PLS", 0, 0,
  _wW, _wH, GL4DW_RESIZABLE | GL4DW_SHOWN))
  return EXIT_FAILURE;

  initGL();
  atexit(quit);

  initAudio("musique/JP.mid");

  /* handlers */
  gl4duwResizeFunc(resize);
  gl4duwKeyUpFunc(key_up);
  gl4duwKeyDownFunc(key_down);
  gl4duwPassiveMotionFunc(passive_motion);
  gl4duwIdleFunc(idle);
  gl4duwDisplayFunc(draw);

  gl4duwMainLoop();

  return EXIT_SUCCESS;
}
