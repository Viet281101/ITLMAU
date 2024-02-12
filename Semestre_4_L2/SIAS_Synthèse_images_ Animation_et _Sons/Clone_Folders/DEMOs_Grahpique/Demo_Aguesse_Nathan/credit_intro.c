#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4dh.h>
#include <stdio.h>
#include <assert.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "audioHelper.h"

static void init(void);
static void draw(void);
static void sortie(void);

static GLuint _quadId = 0;
static GLuint _pId = 0;
static GLuint _texId[2] = {0, 0};
static int _musicMax = 0;

void credit_intro(int state) {
  switch(state) {
  case GL4DH_INIT:
    init();
    return;
  case GL4DH_FREE:
    sortie();
    return;
  case GL4DH_UPDATE_WITH_AUDIO: {
    int l = ahGetAudioStreamLength(), i;
    short * s = (short *)ahGetAudioStream();
    int max = 0;
    for(i = 0; i < l / 4; ++i)
      if (max < s[2 * i])
        max = MAX(s[2 * i], s[1 + 2 * i]);
    _musicMax = max >> 10;
    return;
  }
  default: /* GL4DH_DRAW */
    draw();
    return;
  }
}


void init(void) {
  SDL_Surface * s = NULL, * d = NULL;
  TTF_Font * font = NULL;
  SDL_Color textColor = {255, 255, 255, 255};

  _quadId = gl4dgGenQuadf();
  _pId = gl4duCreateProgram("<vs>shaders/texte.vs", "<fs>shaders/texte.fs", NULL);

  /* initialiser la lib SDL2_ttf */
  if(TTF_Init() == -1) {
    fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
  /* chargement de la font */
  if( !(font = TTF_OpenFont("DejaVuSans-Bold.ttf", 64)) ) {
    fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
    exit(2);
  }

  // Texture Credit 1 :
  /* création d'une surface SDL avec le texte */
  s = TTF_RenderUTF8_Blended_Wrapped(font, 
  "Réalisé par : Aguesse Nathan\n\n"
  "En s'aidant des ressources créé par Farès Belhadj\n"
  "(ateliers API8 et samples de GL4D)\n\n"
  "Librairies utilisé : GL4D, OpenGL, SDL\n", textColor, 2048);
  if(s == NULL) {
    TTF_CloseFont(font);
    fprintf(stderr, "Erreur lors du TTF_RenderText\n");
    exit(2);
  }
  /* création d'une surface vierge et "compatible transfert" GL */
  d = SDL_CreateRGBSurface(0, s->w, s->h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
  /* copie depuis s vers d */
  SDL_BlitSurface(s, NULL, d, NULL);

  /* transfert vers GL */
  glGenTextures(sizeof _texId / sizeof *_texId, _texId);
  assert(_texId[1]);

  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  /* transfert effectif */
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d->w, d->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Texture Credit 2 :
  s = TTF_RenderUTF8_Blended_Wrapped(font, 
  "Musique : jabberwock\n\n"
  "Compositeur/Producteur/Mixeur/Mastering : zohryu\n\n"
  "Provenant de son album \"roux\" (Bandcamp)\n"
  "zohryu.bandcamp.com/album/roux\n\n"
  "Licence : CC BY 3.0\n", textColor, 2048);
  if(s == NULL) {
    TTF_CloseFont(font);
    fprintf(stderr, "Erreur lors du TTF_RenderText\n");
    exit(2);
  }
  d = SDL_CreateRGBSurface(0, s->w, s->h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
  SDL_BlitSurface(s, NULL, d, NULL);
  SDL_FreeSurface(s);

  glBindTexture(GL_TEXTURE_2D, _texId[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d->w, d->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d->pixels);

  glBindTexture(GL_TEXTURE_2D, 0);
  /* libérer d */
  SDL_FreeSurface(d);
  /* libérer la font */
  TTF_CloseFont(font);
}

static double get_dt(void) {
  static double t0 = 0.0f;
  double t = gl4dGetElapsedTime(), dt = (t - t0) / 1000.0;
  t0 = t;
  return dt;
}

void draw(void) {
  static GLfloat a = 0.0f, delai = 400.0f;
  GLfloat time = gl4dhGetTicks()+delai;

  static float rotateCoef = 0.0f;

  if (time > 8900 && time < 11250)
    rotateCoef = (time-8900) / 2350;

  if (time > 18500 && time < 19500)
    rotateCoef = (time-18500) / 2000 + 1.0f;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(_pId);

  gl4duBindMatrix("model");

  // CREDIT 1 :
  gl4duLoadIdentityf();
  gl4duRotatef(180.0f * rotateCoef, 1.0f, 0.0f, 0.0f);
  gl4duTranslatef(0.5f, 0.0f, 0.01f);
  gl4duScalef(7.0f + _musicMax * 0.02, 2.0f + _musicMax * 0.02, 1.0f);
  gl4duSendMatrices();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  glUniform1i(glGetUniformLocation(_pId, "use_tex"), 1);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  gl4dgDraw(_quadId);
  glUniform1i(glGetUniformLocation(_pId, "use_tex"), 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Derrière des crédit caché par ce rect
  gl4duLoadIdentityf();
  gl4duTranslatef(0.1f, 0.0f, 0.0f);
  gl4duRotatef(180.0f * rotateCoef, 1.0f, 0.0f, 0.0f);
  gl4duScalef(8.0f + _musicMax * 0.02, 4.0f + _musicMax * 0.02, 1.0f);
  gl4duSendMatrices();
  gl4dgDraw(_quadId);

  // CREDIT 2 :
  gl4duLoadIdentityf();
  gl4duRotatef(180.0f * rotateCoef + 180.0f, 1.0f, 0.0f, 0.0f);
  gl4duTranslatef(1.0f, 0.0f, 0.01f);
  gl4duScalef(7.0f + _musicMax * 0.02, 2.0f + _musicMax * 0.02, 1.0f);
  gl4duSendMatrices();
  
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, _texId[1]);
  glUniform1i(glGetUniformLocation(_pId, "use_tex"), 1);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 1);
  gl4dgDraw(_quadId);
  glUniform1i(glGetUniformLocation(_pId, "use_tex"), 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glUseProgram(0);
  a += 0.1f * M_PI * get_dt();
}

void sortie(void) {
  if(_texId[0]) {
    glDeleteTextures(sizeof _texId / sizeof *_texId, _texId);
    _texId[0] = 0;
  }
  if(_texId[1]) {
    glDeleteTextures(sizeof _texId / sizeof *_texId, _texId);
    _texId[1] = 0;
  }
}