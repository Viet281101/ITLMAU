#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include <assert.h>
#include <stdlib.h>
#include <GL4D/gl4dg.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <unistd.h>

static GLuint _quadId = 0;

bool cercle_1 = false;
bool cercle_2 = false;
bool cercle_3 = false;
bool cercle_4 = false;
bool cercle_5 = false;
bool cercle_6 = false;
bool cercle_7 = false;

int ordonne0 = 50;
int ordonne1 = 25;
int ordonne2 = 25;
int ordonne3 = 25;
int ordonne4 = 25;
int ordonne5 = 25;
int ordonne6 = 25;
int ordonne7 = 25;
int taille = 5;
int taille2 = 15;
int timer = 0;

int abscisse0 = 50;
int abscisse1 = 175;
int abscisse2 = 300;
int abscisse3 = 425;
int abscisse4 = 550;
int abscisse5 = 675;

// Deuxième animation avec génération procédurale de cercle 

void animation2(int state) {
  
  int l, i;
  Sint16 * s;
  GLint rect[4], tr, mr;
  static int r = 0, or = 0;
  static GLuint screen_id;
  switch(state) {
  case GL4DH_INIT:
    
    screen_id = gl4dpInitScreen();
    gl4dpUpdateScreen(NULL);
    return;
  case GL4DH_FREE:
    

    gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    
    s = (Sint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    for(i = 0, tr = 0; i < l >> 1; i++)
      tr += abs(s[i]);
    tr /= l >> 1;
    r = 100 + (tr >> 6);
    return;
  default: 

   
    gl4dpClearScreen();
    tr = r;
    mr = MAX(tr, or) + 1;
    gl4dpSetScreen(screen_id);
    rect[0] = MAX((gl4dpGetWidth()  >> 1) - mr, 0);
    rect[1] = MAX((gl4dpGetHeight() >> 1) - mr, 0);
    rect[2] = MIN(mr << 1,  gl4dpGetWidth() - rect[0]);
    rect[3] = MIN(mr << 1, gl4dpGetHeight() - rect[1]);

    gl4dpSetColor(RGB(224,173,234)); //changement de couleur 

  gl4dpFilledCircle(abscisse0,ordonne0, 25);
  
  timer++;
  usleep(520000);
  
  if (ordonne0 < 500){ 

    ordonne0+= 25;

    if(ordonne0 > 200){ 

      gl4dpSetColor(RGB(250, 60, 60) ); 

      cercle_1 = true; 

    }
}

  if (cercle_1 == true){

    gl4dpFilledCircle(abscisse1, ordonne1,25); 
  

    if (ordonne1 < 450){
      
      ordonne1+=25; 

      if(ordonne1 > 200){

        gl4dpSetColor(RGB(255,137, 137) );
        cercle_2 = true;

      }

    }

  }

  if (cercle_2 == true){
    
    gl4dpFilledCircle(abscisse2, ordonne2,25);
    
    
    if (ordonne2 < 400){
      
      ordonne2+=25;
      
      if(ordonne2 > 200){
        
        gl4dpSetColor(RGB(254, 184, 184)); 
        cercle_3 = true; 
      }

    }

  }

  if (cercle_3 == true){
    
    gl4dpFilledCircle(abscisse3, ordonne3,25);
    
    
    if (ordonne3 < 350){
      
      ordonne3+=25;
      
      if(ordonne3 > 200){
        
        gl4dpSetColor(RGB(255,221, 221)); 
        cercle_4 = true;
      }
    }
  }


  if (cercle_4 == true){
    
    gl4dpFilledCircle(abscisse4, ordonne4,25);
    
    
    if (ordonne4 < 300 ){
      
      ordonne4+=25;
      if(ordonne4 > 200){
        
        gl4dpSetColor(RGB(255,242, 242)); 
        cercle_5 = true;
      }

    }

  }

  if (cercle_5 == true){
    
    gl4dpFilledCircle(abscisse5, ordonne5,25);
    
    
    if (ordonne5 < 250){
      
      ordonne5+=25;
      
      if(ordonne5 > 200){
        
        
        cercle_6 = true;
      }
    }
  }

  if (cercle_6 == true){

    gl4dpSetColor(RGB(255, 229, 206));
    gl4dpFilledCircle(ordonne6, ordonne6,taille);
    if (ordonne6 < 150){
      
      ordonne6 +=25;
      
      if(ordonne6 < 450){

        taille += 5;
      }

      if(ordonne6 == 150){
        cercle_7 = true;
      }
    }
  }

  if(cercle_7 == true){
    
    gl4dpSetColor(RGB(135, 255, 206));
    gl4dpFilledCircle(ordonne7, ordonne7,taille2);

    if(ordonne7 < 500){

      ordonne7 += 25;

    }
    if(ordonne7 < 550){

      taille2 += 10;
      taille += 12;
    }
  }
  }
  gl4dpUpdateScreen(NULL);
}

static void copyFromSurface(SDL_Surface * s, int x0, int y0) {
  Uint32 * p, coul, ocoul;
  Uint8 rmix, gmix, bmix;
  double f1, f2;
  int x, y, maxx, maxy;
  assert(s->format->BytesPerPixel == 4);
  p = s->pixels;
  maxx = MIN(x0 + s->w, gl4dpGetWidth());
  maxy = MIN(y0 + s->h, gl4dpGetHeight());
  for(y = y0; y < maxy; y++) {
    for(x = x0; x < maxx; x++) {
      ocoul = gl4dpGetPixel(x, y);
      coul = p[(s->h - 1 - (y - y0)) * s->w + x - x0];
      f1 = ALPHA(coul) / 255.0; f2 = 1.0 - f1;
      rmix = f1 *   RED(coul) + f2 *   RED(ocoul);
      gmix = f1 * GREEN(coul) + f2 * GREEN(ocoul);
      bmix = f1 *  BLUE(coul) + f2 *  BLUE(ocoul);
      gl4dpSetColor(RGB(rmix, gmix, bmix));
      gl4dpPutPixel(x, y);
    }
  }
}



void animation1(int state) {
  
  static SDL_Surface * sprite = NULL;
  static GLuint screen_id = 0;
  switch(state) {
  case GL4DH_INIT: {
  
    SDL_Surface * s = IMG_Load("go.png");
    sprite = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(s);
    screen_id = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    return;
  }
  case GL4DH_FREE:
    
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    
    return;
  default: 
 
  


    gl4dpSetScreen(screen_id);
    copyFromSurface(sprite, rand() % gl4dpGetWidth(),rand() % gl4dpGetHeight());
    gl4dpUpdateScreen(NULL);
    return;
  }
}

void animationsInit(void) {
  if(!_quadId)
    _quadId = gl4dgGenQuadf();
}
