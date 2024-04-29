#include "utils.h"
#include <SDL_image.h>
#include <GL4D/gl4dg.h>


void
loadTexture(GLuint id, const char * filename)
{
  SDL_Surface * t;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  if( (t = IMG_Load(filename)) != NULL ) {
    #ifdef __APPLE__
    int mode = t->format->BytesPerPixel == 4 ? GL_BGRA : GL_BGR;
    #else
    int mode = t->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
    #endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->w, t->h, 0, mode, GL_UNSIGNED_BYTE, t->pixels);
    SDL_FreeSurface(t);
  } else {
    fprintf(stderr, "can't open file %s : %s\n", filename, SDL_GetError());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  }
}

float
getTime()
{
  float dt;
  static float t0 = 0, t;

  dt = ((t = gl4dGetElapsedTime()) - t0) / 1000.0;
  t0 = t;
  return t0;
}
