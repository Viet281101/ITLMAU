/*!\file animations.c
 *
 * \brief Votre espace de liberté : c'est ici que vous pouvez ajouter
 * vos fonctions de transition et d'animation avant de les faire
 * référencées dans le tableau _animations du fichier \ref window.c
 *
 * Des squelettes d'animations et de transitions sont fournis pour
 * comprendre le fonctionnement de la bibliothèque. En bonus des
 * exemples dont un fondu en GLSL.
 *
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date May 05, 2014
 */

#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include <assert.h>
#include <stdlib.h>
#include <GL4D/gl4dg.h>

/*!\brief identifiant de la géométrie QUAD GL4Dummies */
static GLuint _quadId = 0;
static GLuint _time = 0;

float cx = 0.7, cy = 0.0;

static GLfloat _resx = 1024;
static GLfloat _resy = 768;

void exemple_de_transition_00(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  /* INITIALISEZ VOS VARIABLES */
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* JOUER LES DEUX ANIMATIONS */
    if(a0) a0(state);
    if(a1) a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    return;
  }
}

void exemple_de_transition_01(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for(i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mix.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if(tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}

void exemple_de_transition_02(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for(i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/titrage.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if(tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}

void 
animation_verte(int state) 
{
  /* INITIALISEZ VOS VARIABLES */
  static GLuint screen_id;
  static GLint pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    screen_id = gl4dpInitScreen();
    gl4dpUpdateScreen(NULL);
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/verte.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    _time++;
    
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glUniform1i(glGetUniformLocation(pId, "time"), _time);
    gl4dgDraw(_quadId);
    return;
  }
}

void 
animation_psycho(int state) 
{
  /* INITIALISEZ VOS VARIABLES */
  
  int l, i;
  Sint16 * s;
  GLint tr;
  static int _coef = 0;
  
  static GLuint screen_id;
  static GLint pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    screen_id = gl4dpInitScreen();
    gl4dpUpdateScreen(NULL);
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/psycho.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    s = (Sint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    for(i = 0, tr = 0; i < l >> 1; i++)
      tr += abs(s[i]);
    tr /= l >> 2;
    _time = (float)tr;
    
    if(_coef < 500)
      _coef++;
      
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glUniform1i(glGetUniformLocation(pId, "coef"), _coef);
    glUniform1i(glGetUniformLocation(pId, "time"), _time);
    gl4dgDraw(_quadId);
    return;
  }
}

void 
animation_blow(int state) 
{
  /* INITIALISEZ VOS VARIABLES */
  
  int l, i;
  Sint16 * s;
  GLint tr;
  static int _coef = 0;
  
  static GLuint screen_id;
  static GLint pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    screen_id = gl4dpInitScreen();
    gl4dpUpdateScreen(NULL);
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/blow.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    s = (Sint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    for(i = 0, tr = 0; i < l >> 1; i++)
      tr += abs(s[i]);
    tr /= l >> 2;
    _time = (float)tr;
    
    _coef++;
    _coef = _coef%50;
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glUniform1i(glGetUniformLocation(pId, "coef"), _coef);
    glUniform1i(glGetUniformLocation(pId, "time"), _time);
    gl4dgDraw(_quadId);
    return;
  }
}

void 
animation_circle(int state) 
{
  /* INITIALISEZ VOS VARIABLES */
  
  int l, i;
  Sint16 * s;
  GLint tr;
  static int _coef = 0;
  
  static GLuint screen_id;
  static GLint pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    screen_id = gl4dpInitScreen();
    gl4dpUpdateScreen(NULL);
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/circle.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    s = (Sint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    for(i = 0, tr = 0; i < l >> 1; i++)
      tr += abs(s[i]);
    tr /= l >> 8;
    _time = (float)tr;
    
    _coef++;
    _coef = _coef%50;
    printf("coef = %d\n", _coef);
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glUniform1i(glGetUniformLocation(pId, "coef"), _coef);
    glUniform1i(glGetUniformLocation(pId, "time"), _time);
    glUniform1i(glGetUniformLocation(pId, "resx"), _resx);
    glUniform1i(glGetUniformLocation(pId, "resy"), _resy);
    gl4dgDraw(_quadId);
    return;
  }
}

void 
animation_light(int state) 
{
  /* INITIALISEZ VOS VARIABLES */
  static int _coef = 0;
  int l, i;
  Sint16 * s;
  GLint tr;
  static GLuint screen_id;
  static GLint pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    _coef = 0;
    screen_id = gl4dpInitScreen();
    gl4dpUpdateScreen(NULL);
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/light.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    s = (Sint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    for(i = 0, tr = 0; i < l >> 1; i++)
      tr += abs(s[i]);
    tr /= l >> 8;
    _time = (float)tr;
    
    _coef++;
    printf("coef = %d\n", _coef);
    if (_coef > 100)
      _coef += 5;
    if (_coef > 500)
      _coef += 20;
      /*
    if (_coef > 1000)
      _coef += 100;*/
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glUniform1i(glGetUniformLocation(pId, "coef"), _coef);
    glUniform1i(glGetUniformLocation(pId, "time"), _time);
    glUniform1i(glGetUniformLocation(pId, "resx"), _resx);
    glUniform1i(glGetUniformLocation(pId, "resy"), _resy);
    gl4dgDraw(_quadId);
    return;
  }
}

void 
animation_lense(int state) 
{
  /* INITIALISEZ VOS VARIABLES */
  static int _coef = 0;
  int l, i;
  Sint16 * s;
  GLint tr;
  static GLuint screen_id;
  static GLint pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    screen_id = gl4dpInitScreen();
    gl4dpUpdateScreen(NULL);
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/lense.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    s = (Sint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    for(i = 0, tr = 0; i < l >> 1; i++)
      tr += abs(s[i]);
    tr /= l >> 8;
    _time = (float)tr;
    
    _coef++;
    printf("coef = %d\n", _coef);
    if (_coef > 100)
      _coef += 5;
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glUniform1i(glGetUniformLocation(pId, "coef"), _coef);
    glUniform1i(glGetUniformLocation(pId, "time"), _time);
    glUniform1i(glGetUniformLocation(pId, "resx"), _resx);
    glUniform1i(glGetUniformLocation(pId, "resy"), _resy);
    gl4dgDraw(_quadId);
    return;
  }
}

void animationsInit(void) {
  if(!_quadId)
    _quadId = gl4dgGenQuadf();
}
