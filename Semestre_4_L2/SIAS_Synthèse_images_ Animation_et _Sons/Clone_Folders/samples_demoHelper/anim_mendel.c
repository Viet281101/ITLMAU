
#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL4D/gl4dg.h>
#include <SDL2/SDL_image.h>
#include <animations.h>

static int max = 10;
static int etat = 0;

void animation_mendel(int state) {
  static GLuint screen_id;
  switch(state) {
  case GL4DH_INIT:
    screen_id = gl4dpInitScreen();
    gl4dpUpdateScreen(NULL);
    return;
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    gl4dpSetScreen(screen_id);
    mendel_anim();
    gl4dpUpdateScreen(NULL);
    return;
  }
}

void animation_julia(int state) {
  static GLuint screen_id;
  static int etat = 0;
  static double cImaginaire = 1;
  static double cReel = 1;
  switch(state) {
  case GL4DH_INIT:
    screen_id = gl4dpInitScreen();
    julia(1.0,40,cImaginaire,cReel);
    gl4dpUpdateScreen(NULL);
    gl4dpDeleteScreen();
    return;
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    gl4dpSetScreen(screen_id);
    julia(1,40,cImaginaire,cReel);
    switch(etat)
    {
      case 0:
        cImaginaire -=0.01;
        cReel -= 0.01;
        if(cReel < -2)
          etat = 1;
        break;

      case 1:
        cImaginaire +=0.015;
        if(cImaginaire > 2)
          etat = 2;
        break;

      case 2 :
        cReel +=0.015;
        if(cReel > 2)
          etat = 0;
    }
    gl4dpUpdateScreen(NULL);
    return;
  }
}

int HSBtoRGB(float hue, float saturation, float brightness) 
{
  int r = 0, g = 0, b = 0;
  if (saturation == 0) r = g = b = (int) (brightness * 255.0f + 0.5f);
  else 
  {
    float h = (hue - (float)floor(hue)) * 6.0f;
    float f = h - (float)floor(h);
    float p = brightness * (1.0f - saturation);
    float q = brightness * (1.0f - saturation * f);
    float t = brightness * (1.0f - (saturation * (1.0f - f)));
    switch ((int) h) 
    {
      case 0:
        r = (int) (brightness * 255.0f + 0.5f);
        g = (int) (t * 255.0f + 0.5f);
        b = (int) (p * 255.0f + 0.5f);
        break;
      case 1:
        r = (int) (q * 255.0f + 0.5f);
        g = (int) (brightness * 255.0f + 0.5f);
        b = (int) (p * 255.0f + 0.5f);
        break;
      case 2:
        r = (int) (p * 255.0f + 0.5f);
        g = (int) (brightness * 255.0f + 0.5f);
        b = (int) (t * 255.0f + 0.5f);
        break;
      case 3:
        r = (int) (p * 255.0f + 0.5f);
        g = (int) (q * 255.0f + 0.5f);
        b = (int) (brightness * 255.0f + 0.5f);
        break;
      case 4:
        r = (int) (t * 255.0f + 0.5f);
        g = (int) (p * 255.0f + 0.5f);
        b = (int) (brightness * 255.0f + 0.5f);
        break;
      case 5:
        r = (int) (brightness * 255.0f + 0.5f);
        g = (int) (p * 255.0f + 0.5f);
        b = (int) (q * 255.0f + 0.5f);
        break;
    }
  }
  return 0xff000000 | (r << 16) | (g << 8) | (b << 0);
}

void mendel_anim()
{
  mendel(max);
  if(max == 50)etat = 0;
  if(max == 3)etat = 1;
  if(etat == 0)--max;
  if(etat == 1)++max;
}

void mendel(int max){
  int height = gl4dpGetHeight();
  int width =  gl4dpGetWidth();
  int color[max];

  for(int i =0;i< max;++i){
    color[i] = HSBtoRGB(i/256.f,1,i/(i+8.f));
  }

  float nouveauReel = 0;
  float nouveauIm =0;
  float reel = 0;
  float imaginaire = 0;

  for(int ligne = 0;ligne < height;++ligne)
  {
    for(int col = 0;col < width;++col)
    {
      float  cReel = 1.5 * (col - width / 2) / (0.5  * width);
      float  cImaginaire = (ligne - height / 2) / (0.5 * height);
      nouveauReel = nouveauIm = reel = imaginaire = 0;

      int i = 0;
      while (nouveauReel * nouveauReel + nouveauIm * nouveauIm <= 4 && i < max) 
      {
        reel = nouveauReel;
        imaginaire = nouveauIm;
        nouveauReel = reel * reel - imaginaire * imaginaire + cReel;
        nouveauIm = 2 * reel * imaginaire + cImaginaire;
        i++;
      }

      if (i < max)
      {
        gl4dpSetColor(color[i]);
        gl4dpPutPixel(col, ligne);
      } else {
        gl4dpSetColor(RGB(0,0,0));
        gl4dpPutPixel(col, ligne);
      }
    }
  }
}

double zoomeur( double zoom, int val)
{
  double nouveau_max = 2 / zoom;
  double nouveau_min = -2 / zoom;
  return (( double)val * (nouveau_max - nouveau_min)) / gl4dpGetWidth() + nouveau_min;
}

void julia(double zoom,int maxIterations,double cImaginaire,double cReel){
  int height = gl4dpGetHeight();
  int width = gl4dpGetWidth();
  double nouveauReel, nouveauIm, reel, imaginaire;
  int color[maxIterations];
  for(int i =0;i< maxIterations;++i)
  {
    color[i] = HSBtoRGB(i/256.f,1,i/(i+8.f));
  }
  for(int y = 0; y < height; ++y)
  {
    for(int x = 0; x < width; ++x)
    {
      nouveauReel = zoomeur(zoom, y);
      nouveauIm = zoomeur(zoom, x);
      int i;

      for(i = 0; i < maxIterations; ++i)
      {
        reel = nouveauReel;
        imaginaire = nouveauIm;

        nouveauReel = reel * reel - imaginaire * imaginaire + cReel;
        nouveauIm = 2 * reel * imaginaire + cImaginaire;

        if((nouveauReel * nouveauReel + nouveauIm * nouveauIm) > 4) break;
      }

      if (i < maxIterations){
        gl4dpSetColor(color[i]);
        gl4dpPutPixel(x, y);
      }
      else
      {
        gl4dpSetColor(RGB(0,0,0));
        gl4dpPutPixel(x,y);
      }
    }
  }
}
