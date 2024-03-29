/*!\file light_n_tex.cpp
 * \brief GL4Dummies, exemple éclairage complet avec
 * GL4Dummies. Complété avec placage d'une texture écrite directement
 * dans un tableau en RAM CPU puis transférée en RAM-GPU.
 * + texture fichier + normal_map
 * intégré dans demo_helper
 * \author Farès BELHADJ, amsi@up8.edu
 * \date April 18 2022
 */

/* pour la structure (template) vector */
#include <vector>
/* inclusion des entêtes de fonctions de création et de gestion de
 * fenêtres système ouvrant un contexte favorable à GL4dummies. Cette
 * partie est dépendante de la bibliothèque SDL2 */
#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dm.h>
#include <GL4D/gl4dg.h>
/* pour la macro RGB */
#include <GL4D/gl4dp.h>
/* pour IMG_Load */
#include <SDL_image.h>
/* pour l'ensemble des fonctions liées au son */
#include <SDL_mixer.h>

/* noueaux include depuis demo_helper */
#include <GL4D/gl4dh.h>
#include "audioHelper.h"

/* on créé une variable pour stocker l'identifiant du programme GPU */
static GLuint _pId = 0;
/* on créé une variable pour stocker l'identifiant de la géométrie : un plan, un cube et une sphère GL4D */
static GLuint _plan = 0;
static GLuint _cube = 0;
static GLuint _sphere = 0;
/* entiers (positifs) pour y stocker les identifiants de textures
 * OpenGL générées. */
static GLuint _texId[] = { 0, 0, 0 };
/* pour stocker la moyenne du son sur 1/44 de seconde (cherchez pourquoi 1/44) */
static double _moyenne_son = 0.0;
#define N_CUBES 32
/* pour stocker N_CUBES moyennes de son, chacune sur 32 échantillons (32x32=1024) */
static double _moyenne_32[N_CUBES] = { 0.0 };
/* une structure pour stocker un cube */
typedef struct cube_t cube_t;
struct cube_t {
  int index;
  GLfloat color[4];
};
/* un vecteur de "cubes" par numéro dans _moyenne_32 */
std::vector <cube_t> _cubes;

static void   init(void);
static void   update_audio(Uint8 *stream, int len);
static double inter_frames_dt(void);
static void   dessine_un_seul_cube(cube_t cube, GLfloat a);
static void   essayer_d_ajouter_un_cube(void);
static void   set_projection(void);
static void   draw(void);
static void   quit(void);

void light_n_tex(int state) {
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
    update_audio(ahGetAudioStream(), ahGetAudioStreamLength());
    return;
  default: /* GL4DH_DRAW */ {
    /* JOUER L'ANIMATION */
    GLint dt = glIsEnabled(GL_DEPTH_TEST);
    /* activer le test de profondeur si non activé */
    if(!dt)
      glEnable(GL_DEPTH_TEST);
    draw();
    /* désactiver le test de profondeur s'il l'était avant */
    if(!dt)
      glDisable(GL_DEPTH_TEST);
    return;
  }
  }
}


/* initialise des paramètres GL et GL4D */
void init(void) {
  /* image directement en RAM de 2x2 pixels (texels) avec un gris, un
   * blanc en première ligne puis un blanc un gris en deuxième
   * ligne */
  GLuint pixels[] = { (GLuint)RGB(128, 128, 128), (GLuint)-1, (GLuint)-1, (GLuint)RGB(128, 128, 128) };
  /* set la couleur d'effacement OpenGL */
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  /* générer un plan en GL4D */
  _plan = gl4dgGenQuadf();
  /* générer un cube en GL4D */
  _cube = gl4dgGenCubef();
  /* générer une sphere en GL4D */
  _sphere = gl4dgGenSpheref(42, 42);
  /* créer un programme GPU pour OpenGL (en GL4D) */
  _pId = gl4duCreateProgram("<vs>shaders/light_n_tex.vs", "<fs>shaders/light_n_tex.fs", NULL);
  /* créer dans GL4D une matrice qui s'appelle model ; matrice de
     modélisation qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "model");
  /* créer dans GL4D une matrice qui s'appelle view ; matrice de
     vue (point de vue) qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "view");
  /* créer dans GL4D une matrice qui s'appelle proj ; matrice de
     projection qu'on retrouvera dans le vertex shader */
  gl4duGenMatrix(GL_FLOAT, "proj");

  /* Générer 3 identifiants de texture côté OpenGL (GPU) pour y
   * transférer des textures. */
  glGenTextures(3, _texId);
  /* binder la texture générée comme texture 2D côté GPU */
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  /* paramétrer quelques propriétés de texture : voir la doc OpenGL de glTexParameteri */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST /* mettre GL_LINEAR si interpolation linéaire */);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST /* mettre GL_LINEAR si interpolation linéaire */);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT /* REPEAT est le par défaut, mettre par exemple GL_MIRRORED_REPEAT pour une répitions en mirroir */);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT /* REPEAT est le par défaut, mettre par exemple GL_MIRRORED_REPEAT pour une répitions en mirroir */);
  /* fonction de transfert de données (texels) de CPU vers GPU :
   * fonction assez riche, voir sa doc */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  /* à ce niveau pixels en RAM-CPU n'est plus nécessaire */
  /* dé-binder la texture, par mesure de protection de ses paramètres
   * et ses données */
  glBindTexture(GL_TEXTURE_2D, 0);

  /* binder la texture générée comme texture 2D côté GPU */
  glBindTexture(GL_TEXTURE_2D, _texId[1]);
  /* paramétrer quelques propriétés de texture : voir la doc OpenGL de glTexParameteri */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR /* on veut la lisser */);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR /* on veut la lisser */);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT /* on veut la rendre cyclique */);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT /* on veut la rendre cyclique */);
  /* bloc concernant le chargement de fichier image, sa conversion
   * dans notre format RGBA et son transfert vers le GPU */
  {
    /* utilisation de SDL2_image pour charger une image au format png */
    SDL_Surface * orig = IMG_Load("images/brick.png");
    /* si échec de chargement, mettre une texture avec un seul pixel blanc */
    if(orig == NULL) {
      GLuint blanc = -1; /* ou 0xFFFFFFFF */
      /* transfert du pixel blanc */
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &blanc);      
    } else {
      /* création d'une surface SDL (image) compatible avec mon format de transfert OpenGL */
      SDL_Surface * image_au_format_RGBA = SDL_CreateRGBSurface(0, orig->w, orig->h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
      /* copie de orig vers image_au_format_RGBA en convertissant au format de image_au_format_RGBA */
      SDL_BlitSurface(orig, NULL, image_au_format_RGBA, NULL);
      /* plus besoin d'orig, libérer la mémoire */
      SDL_FreeSurface(orig);
      /* fonction de transfert de données (texels) RGBA de CPU vers GPU :
       * fonction assez riche, voir sa doc */
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_au_format_RGBA->w, image_au_format_RGBA->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_au_format_RGBA->pixels);
      /* plus besoin de image_au_format_RGBA, libérer la mémoire */
      SDL_FreeSurface(image_au_format_RGBA);
    }
  }
  /* à ce niveau pixels en RAM-CPU n'est plus nécessaire */
  /* dé-binder la texture, par mesure de protection de ses paramètres
   * et ses données */
  glBindTexture(GL_TEXTURE_2D, 0);

  /* pensez à faire une fonction car ici il y a beaucoup de répétitions */
  /* binder la texture générée comme texture 2D côté GPU */
  glBindTexture(GL_TEXTURE_2D, _texId[2]);
  /* paramétrer quelques propriétés de texture : voir la doc OpenGL de glTexParameteri */
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR /* on veut la lisser */);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR /* on veut la lisser */);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT /* on veut la rendre cyclique */);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT /* on veut la rendre cyclique */);
  /* bloc concernant le chargement de fichier image, sa conversion
   * dans notre format RGBA et son transfert vers le GPU */
  {
    /* utilisation de SDL2_image pour charger une image au format png */
    SDL_Surface * orig = IMG_Load("images/brick_nm.png");
    /* si échec de chargement, mettre une texture avec un seul pixel noir */
    if(orig == NULL) {
      GLuint noir = 0;
      /* transfert du pixel noir */
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &noir);      
    } else {
      /* création d'une surface SDL (image) compatible avec mon format de transfert OpenGL */
      SDL_Surface * image_au_format_RGBA = SDL_CreateRGBSurface(0, orig->w, orig->h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
      /* copie de orig vers image_au_format_RGBA en convertissant au format de image_au_format_RGBA */
      SDL_BlitSurface(orig, NULL, image_au_format_RGBA, NULL);
      /* plus besoin d'orig, libérer la mémoire */
      SDL_FreeSurface(orig);
      /* fonction de transfert de données (texels) RGBA de CPU vers GPU :
       * fonction assez riche, voir sa doc */
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_au_format_RGBA->w, image_au_format_RGBA->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_au_format_RGBA->pixels);
      /* plus besoin de image_au_format_RGBA, libérer la mémoire */
      SDL_FreeSurface(image_au_format_RGBA);
    }
  }
  /* à ce niveau pixels en RAM-CPU n'est plus nécessaire */
  /* dé-binder la texture, par mesure de protection de ses paramètres
   * et ses données */
  glBindTexture(GL_TEXTURE_2D, 0);
}

void update_audio(Uint8 *stream, int len) {
    int i, j, k;
    double moyenne = 0.0;
    Sint16 *s16 = (Sint16 *)stream;
    int sous_echantillons;
    static double moyenne_32[N_CUBES] = { 0.0 };
    len = len / 2; /* car 2 octets par échantillon */
    sous_echantillons = len / N_CUBES;
    memset(moyenne_32, 0, sizeof moyenne_32);
    /* je me contente de moyenner les intensités du son */
    for(i = 0, j = 0, k = 0; i < len; ++i, ++j) {
        if (j == sous_echantillons) {
            ++k;
            j = 0;
        }
        moyenne += (s16[i] < 0.0 ? -s16[i] : s16[i]) / (double)(1<<13);
        moyenne_32[k] += (s16[i] < 0.0 ? -s16[i] : s16[i]) / (double)(1 << 13);
    }
    moyenne = moyenne / i;
    _moyenne_son = moyenne < 1.0 ? moyenne : 1.0;
    for (j = 0; j < N_CUBES; ++j) {
      moyenne_32[j] = moyenne_32[j] / sous_echantillons;
      moyenne_32[j] = moyenne_32[j] > 1.0f ? 1.0f : moyenne_32[j];
      moyenne_32[j] = moyenne_32[j] < 0.0f ? 0.0f : moyenne_32[j];
    }
    for (j = 0; j < N_CUBES; ++j)
      _moyenne_32[j] = (_moyenne_32[j] + moyenne_32[j]) / 2;
}

double inter_frames_dt(void) {
  static double t0 = -1.0;
  double t = gl4dGetElapsedTime(), dt;
  if(t0 < 0.0) /* ça ne devrait arriver qu'au premier appel */
    t0 = t;
  dt = (t - t0) / 1000.0;
  /* pour la prochaine frame */
  t0 = t;
  return dt;
}

void dessine_un_seul_cube(cube_t cube, GLfloat a) {
    const GLfloat blanc[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    /***** On fini avec le cube *****/
    /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
    gl4duLoadIdentityf();
    /* composer (multiplication à droite) avec une translation vers le
       haut <0, 1.5, 0> */
    gl4duTranslatef(0, 1.5f, 0);
    /* composer (multiplication à droite) avec une rotation d'angle -90 et
       d'axe (autour de l'axe) <1, 0, 0> pour coucher le plan */
    gl4duRotatef(180.0f + (-cube.index * 360.0f / N_CUBES) + a / 2.0f, 0, 1, 0);
    /* composer (multiplication à droite) avec une translation vers la
       droite <3, 0, 0> */
    gl4duTranslatef(3, 0, 0);
    gl4duRotatef(-a, 0, 1, 0);
    gl4duTranslatef(0, -1.0 + _moyenne_32[cube.index], 0);
    gl4duScalef(0.2f, 0.2f + _moyenne_32[cube.index], 0.2f);
    /* envoyer les matrice GL4D au programme GPU OpenGL (en cours) */
    gl4duSendMatrices();
    glUniform4fv(glGetUniformLocation(_pId, "surface_ambient_color"), 1, cube.color);
    glUniform4fv(glGetUniformLocation(_pId, "surface_diffuse_color"), 1, cube.color);
    glUniform4fv(glGetUniformLocation(_pId, "surface_specular_color"), 1, blanc);

    /* activer la l'unité 0 pour y stocker une texture */
    glActiveTexture(GL_TEXTURE0);
    /* binder la texture _texId[0] pour l'utiliser sur l'unité 0 */
    glBindTexture(GL_TEXTURE_2D, _texId[0]);
    /* informer le programme GPU _pId que ma texture est celle posée à l'unité 0 */
    glUniform1i(glGetUniformLocation(_pId, "my_texture"), 0 /* le 0 correspond à GL_TEXTURE0 */);
    /* informer le programme GPU _pId que pour cette surface je souhaite utiliser la texture */
    glUniform1i(glGetUniformLocation(_pId, "use_texture"), GL_TRUE);

    /* demander le dessin d'un objet GL4D */
    gl4dgDraw(_cube);

    /* après mon draw informer le programme GPU _pId que je ne souhaite plus utiliser de texture */
    glUniform1i(glGetUniformLocation(_pId, "use_texture"), GL_FALSE);
    /* dé-binder ma texture pour la désaffecter de l'unité 0 */
    glBindTexture(GL_TEXTURE_2D, 0);

}

void essayer_d_ajouter_un_cube(void) {
  static double t0 = -1.0;
  double t = gl4dGetElapsedTime(), dt;
  if(t0 < 0.0) /* ça ne devrait arriver qu'au premier appel */
    t0 = t;
  dt = (t - t0) / 1000.0;
  /* ne faire que si une seconde au moins est passée */
  if(dt > 1.0) {
    GLfloat color[4] = {(GLfloat)gl4dmURand(), (GLfloat)gl4dmURand(), (GLfloat)gl4dmURand(), (GLfloat)gl4dmURand()};
    cube_t c;
    c.index = (int)_cubes.size();
    for(int i = 0; i < 4; ++i)
      c.color[i] = color[i];
    // ou memcpy(c.color, color, sizeof color);
    _cubes.push_back(c);
    /* pour la prochaine seconde */
    t0 = t;
  }
}


/* modification, à faire à chaque fois (draw) ; si jamais une autre
 * "anime" modifie ma matrice. */
void set_projection(void) {
  GLint vp[4];
  /* récupérer le viewport actuel de GL */
  glGetIntegerv(GL_VIEWPORT, vp);
  GLfloat inv_ratio = vp[3] / (GLfloat)vp[2];
  /* binder (mettre au premier plan, "en courante" ou "en active") la matrice proj */
  gl4duBindMatrix("proj");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  /* combiner la matrice courante avec une matrice de projection en
     perspective. Voir le support de cours pour les six paramètres :
     left, right, bottom, top, near, far */
  gl4duFrustumf(-1.0f, 1.0f, -inv_ratio, inv_ratio, 1.0f, 1000.0f);
}

void draw(void) {
  int i;
  /* une variable pour stocker un angle qui s'incrémente */
  static float a = 0;
  /* quelques couleurs qu'on transmettra au program shader */
  const GLfloat rouge[] = {1.0f, 0.0f, 0.0f, 1.0f};
  const GLfloat blanc[] = {1.0f, 1.0f, 1.0f, 1.0f};
  const GLfloat vert_tres_clair[] = {0.7f, 1.0f, 0.7f, 1.0f};
  const GLfloat jaune_clair[] = {0.9f, 0.9f, 0.5f, 1.0f};
  static GLfloat position_lumiere[] = {2.0f, 3.5f, -5.5f, 1.0f};
  GLfloat amplified_amb_light[4], amplified_diff_light[4], amplified_spec_light[4], cam_pos[3];

  set_projection();

  if(_cubes.size() < 32)
    essayer_d_ajouter_un_cube(); 

  /* on bouge un peu la lumière */
  position_lumiere[0] =  6.0f * sin(a / 200.0f);
  position_lumiere[2] = -6.0f * cos(a / 200.0f);
  /* effacer le buffer de couleur (image) et le buffer de profondeur d'OpenGL */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /* utiliser le programme GPU "_pId" */
  glUseProgram(_pId);
  /* mettre le facteur de multiplication de texture (répétition, voir le vertex shader) à 1 */
  glUniform1f(glGetUniformLocation(_pId, "mult_tex_coord"), 1.0f);
  /* binder (mettre au premier plan, "en courante" ou "en active") la
     matrice view */
  gl4duBindMatrix("view");
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  /* position de la caméra */
  cam_pos[0] = 6.0f * sin(-a / 1000.0);
  cam_pos[1] = 2.0f;
  cam_pos[2] = 6.0f * cos(-a / 1000.0);
  /* composer (multiplication à droite) avec une matrice fabriquée par LookAt */ 
  gl4duLookAtf(cam_pos[0], cam_pos[1], cam_pos[2], 0, 0, 0, 0, 1, 0);
  /* binder (mettre au premier plan, "en courante" ou "en active") la
     matrice model */
  gl4duBindMatrix("model");

  /* amplifier la lumière en fonction du son */
  for(i = 0; i < 3; ++i) {
    double a = pow(_moyenne_son, 2.5);
    amplified_amb_light[i]  = blanc[i] * (1.0 + 0.5 * a); 
    amplified_diff_light[i] = jaune_clair[i] * (1.0 + 1.5 * a); 
    amplified_spec_light[i] = blanc[i] * (1.0 + 5.0 * a); 
  }
  glUniform4fv(glGetUniformLocation(_pId, "light_ambient_color"), 1, amplified_amb_light);
  glUniform4fv(glGetUniformLocation(_pId, "light_diffuse_color"), 1, amplified_diff_light);
  glUniform4fv(glGetUniformLocation(_pId, "light_specular_color"), 1, amplified_spec_light);
  glUniform4fv(glGetUniformLocation(_pId, "light_position"), 1, position_lumiere);

  /***** On commence par la sphère *****/
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  /* composer (multiplication à droite) avec un scale lié à l'intensité du son */
  {
    double s = 1.0 + 0.5 * pow(_moyenne_son, 2.0);
    gl4duScalef(s, s, s);
  }
  /* composer (multiplication à droite) avec une translation vers le
     haut <0, 1.5, 0> */
  gl4duTranslatef(0, 1.5f, 0);  
  /* composer (multiplication à droite) avec une rotation d'angle a et
     d'axe (autour de l'axe) <0, 1, 0> */
  gl4duRotatef(a / 5.0f, 0, 1, 0);
  /* envoyer les matrice GL4D au programme GPU OpenGL (en cours) */
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "surface_ambient_color"), 1, rouge);
  glUniform4fv(glGetUniformLocation(_pId, "surface_specular_color"), 1, rouge);
  glUniform4fv(glGetUniformLocation(_pId, "surface_diffuse_color"), 1, rouge);

  /* demander le dessin d'un objet GL4D */
  gl4dgDraw(_sphere);


  /***** On continue avec le plan *****/
  /* mettre la matrice identité (celle qui ne change rien) dans la matrice courante */
  gl4duLoadIdentityf();
  /* composer (multiplication à droite) avec une rotation d'angle -90 et
     d'axe (autour de l'axe) <1, 0, 0> pour coucher le plan */
  gl4duRotatef(-90, 1, 0, 0);
  /* composer (multiplication à droite) avec un scale x5 <15, 15, 15> */
  gl4duScalef(15, 15, 15);  
  /* envoyer les matrice GL4D au programme GPU OpenGL (en cours) */
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "surface_ambient_color"), 1, blanc);
  glUniform4fv(glGetUniformLocation(_pId, "surface_diffuse_color"), 1, vert_tres_clair);
  glUniform4fv(glGetUniformLocation(_pId, "surface_specular_color"), 1, blanc);

  /* activer la l'unité 1 pour y stocker une texture de normal map */
  glActiveTexture(GL_TEXTURE1);
  /* binder la texture _texId[2] (normal map de brick) pour l'utiliser sur l'unité 1 */
  glBindTexture(GL_TEXTURE_2D, _texId[2]);
  /* informer le programme GPU _pId que ma texture est celle posée à l'unité 1 */
  glUniform1i(glGetUniformLocation(_pId, "my_nm_texture"), 1 /* le 1 correspond à GL_TEXTURE1 */);
  /* dire que je utilise une normal map */
  glUniform1i(glGetUniformLocation(_pId, "use_nm_texture"), GL_TRUE);
  /* activer la l'unité 0 pour y stocker une texture */
  glActiveTexture(GL_TEXTURE0);
  /* binder la texture _texId[1] (brick) pour l'utiliser sur l'unité 0 */
  glBindTexture(GL_TEXTURE_2D, _texId[1]);
  /* informer le programme GPU _pId que ma texture est celle posée à l'unité 0 */
  glUniform1i(glGetUniformLocation(_pId, "my_texture"), 0 /* le 0 correspond à GL_TEXTURE0 */);
  /* informer le programme GPU _pId que pour cette surface je souhaite utiliser la texture */
  glUniform1i(glGetUniformLocation(_pId, "use_texture"), GL_TRUE);
  /* mettre en place le facteur de multiplication de texture (répétition, voir le vertex shader) */
  glUniform1f(glGetUniformLocation(_pId, "mult_tex_coord"), 20.0f);

  /* demander le dessin d'un objet GL4D */
  gl4dgDraw(_plan);

  /* après mon draw informer le programme GPU _pId que je ne souhaite plus utiliser de texture */
  glUniform1i(glGetUniformLocation(_pId, "use_texture"), GL_FALSE);
  /* remettre le facteur de multiplication de texture (répétition, voir le vertex shader) à 1 */
  glUniform1f(glGetUniformLocation(_pId, "mult_tex_coord"), 1.0f);
  /* dire que je n'utilise plus de normal map */
  glUniform1i(glGetUniformLocation(_pId, "use_nm_texture"), GL_FALSE);
  /* dé-binder ma texture pour la désaffecter de l'unité 1 */
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, 0);
  /* dé-binder ma texture pour la désaffecter de l'unité 0 */
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);

  for(std::vector<cube_t>::iterator it = _cubes.begin(); it != _cubes.end(); ++it)
    dessine_un_seul_cube(*it, a);

  /* n'utiliser aucun programme GPU (pas nécessaire) */
  glUseProgram(0);
  /* augmenter l'ange a de 1 */
  a += 60.0 * inter_frames_dt();
}

/* appelée lors du exit */
void quit(void) {
  /* libérer les textures générées côté OpenGL/GPU */
  if(_texId[0]) {
    glDeleteTextures(3, _texId);
    _texId[0] = 0;
  }
  /* effacer le vetor d'entiers */
  _cubes.clear();
}

