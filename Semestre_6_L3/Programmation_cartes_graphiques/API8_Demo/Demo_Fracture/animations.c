/*

KARUNAKARAN Nithusha
L2 Informatique Groupe Y
*/
#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL4D/gl4dg.h>
#include <SDL_image.h>
#include <animations.h>

static GLuint _quadId = 0;
static int max = 10;
static int etat = 0;
static float steps = 5.0f;

void animation_sierpinski(int state) {
	static GLuint screen_id;
	switch(state)
	{
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
			sierpinski_anim();
			gl4dpUpdateScreen(NULL);
			return;
	}
}


void animation_mendel(int state) {
	static GLuint screen_id;
	switch(state)
	{
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
	switch(state) 
	{
		case GL4DH_INIT:
			screen_id = gl4dpInitScreen();
			julia(1.0,40,cImaginaire,cReel);
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
			julia(1,40,cImaginaire,cReel);
			switch(etat)
			{
				case 0:
					cImaginaire -=0.01;
					cReel -= 0.01;
					if(cReel < -2){ etat = 1; }
					break;
				case 1:
					cImaginaire +=0.015;
					if(cImaginaire > 2){ etat = 2; }
					break;
				case 2 :
					cReel +=0.015;
					if(cReel > 2){ etat = 0; }
			}
			gl4dpUpdateScreen(NULL);
			return;
	}
}



void animation_julia_zoom(int state) {
	static GLuint screen_id;
	static float zoom = 1.0;
	static double cImaginaire = 0.27015;
	static double cReel = -0.7;
	switch(state) {
	case GL4DH_INIT:
		screen_id = gl4dpInitScreen();
		julia(1.0,40,cImaginaire,cReel);
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
			julia(zoom,500,cImaginaire,cReel);
			if(zoom < 5.0){ zoom+=0.2;}
			gl4dpUpdateScreen(NULL);
			return;
	}
}



void animation_pythagore(int state) {
	static GLuint screen_id;
	point a,b;
	a.x = (1024/2) - 60;
	a.y =   768 - 100;
	b.x = (1024/2) + 60;
	b.y =  768 - 100;
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
		pythagore_arbre(a,b,10);
		gl4dpUpdateScreen(NULL);
		return;
	}
}

void animation_barnsley(int state) {
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
		barnsley(1024,100);
		gl4dpUpdateScreen(NULL);
		return;
	}
}



void animationsInit(void) {
	if(!_quadId)
		_quadId = gl4dgGenQuadf();
}



/*

HSBtoRGB
CODE ISSU DE L'ANCIENNE BIBLIOTHEQUE GRAPHIQUE AWT POUR JAVA : COLOR.JAVA
JE NE SUIS PAS L'AUTEUR DU CODE,J'AI JUSTE TRADUIS LE CODE JAVA EN C,
http://www.docar.com/html/api/java/awt/Color.java.html
LIGNE 839 À 884
*/


int HSBtoRGB(float hue, float saturation, float brightness) {
	int r = 0, g = 0, b = 0;
	if (saturation == 0) {
		r = g = b = (int) (brightness * 255.0f + 0.5f);
	} else {
		float h = (hue - (float)floor(hue)) * 6.0f;
		float f = h - (float)floor(h);
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));
		switch ((int) h) {
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


/*
Fonctions pour créer un ensemble de Mendelbrot
*/

void mendel_anim(){
	mendel(max);
	if(max == 50){ etat = 0; }
	if(max == 3){ etat = 1; }
	if(etat == 0){ --max; }
	if(etat == 1){ ++max; }
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

	for(int ligne = 0;ligne < height;++ligne){
		for(int col = 0;col < width;++col){
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
			if (i < max){
				gl4dpSetColor(color[i]);
				gl4dpPutPixel(col, ligne);
			} else {
				gl4dpSetColor(RGB(0,0,0));
				gl4dpPutPixel(col, ligne);
			}
		}
	}
}


/*
Fonction pour dessiner un triangle de Sierpinski
*/

void sierpinski_triangle(float steps){
	float h = gl4dpGetHeight() ;
	float w = gl4dpGetWidth();

	point a;
	point b;
	point c;
	point p;

	a.x = 10;
	a.y = h - 10;
	b.x = w - 10;
	b.y = h - 10;
	c.x = w / 2;
	c.y = 10;

	p.x = a.x;
	p.y = a.y;

	for(int n = 0; n < steps; ++n)
	{
		switch(abs(rand() % 3))
		{
			case 0:
				p.x = (p.x + a.x) / 2.0;
				p.y = (p.y + a.y) / 2.0;
				gl4dpSetColor(RGB(255,0,0));
				gl4dpPutPixel(p.x,p.y);
				break;
			case 1:
				p.x = (p.x + b.x) / 2.0;
				p.y = (p.y + b.y) / 2.0;
				gl4dpSetColor(RGB(0,255,0));
				gl4dpPutPixel(p.x,p.y);
				break;
			case 2:
				p.x = (p.x + c.x) / 2.0;
				p.y = (p.y + c.y) / 2.0;
				gl4dpSetColor(RGB(0,0,255));
				gl4dpPutPixel(p.x,p.y);
				break;
		}
	}
}

void sierpinski_anim(){
	static Uint32 t0 = 0;
	Uint32 t = SDL_GetTicks();
	float dt = (t - t0) / 1.0;
	t0 = t;

	if(steps < MAX_STEPS){
		sierpinski_triangle(steps);
		if(steps < 1000){
			steps = steps + (dt/200);
		} else {
			steps = steps + dt + 100;
		}
		usleep(10000);
	}
}


/*
Fonction pour créer un arbre de Pythagore
*/

void pythagore_arbre(point a,point b,int i){
	point alpha;
	point beta;
	point gamma;

	alpha.x = b.x -(a.y - b.y);
	alpha.y = b.y - (b.x - a.x);
	beta.x = a.x - (a.y -  b.y);
	beta.y = a.y - (b.x - a.x);
	gamma.x = beta.x +  ( b.x - a.x - (a.y -  b.y) ) / 2;
	gamma.y = beta.y -  ( b.x - a.x + a.y -  b.y ) / 2;

	if(i>0){
		gl4dpSetColor(RGB(rand()% 255,rand()% 255,rand()% 255));

		gl4dpLine(a.x,a.y,b.x,b.y);
		gl4dpLine(alpha.x,alpha.y,b.x,b.y);
		gl4dpLine(alpha.x,alpha.y,beta.x,beta.y);
		gl4dpLine(a.x,a.y,beta.x,beta.y);

		pythagore_arbre(beta,gamma,i-1);
		pythagore_arbre(gamma,alpha,i-1);
	}
}

double zoomeur( double zoom, int val){

	double nouveau_max = 2 / zoom;
	double nouveau_min = -2 / zoom;

	return (( double)val * (nouveau_max - nouveau_min)) / gl4dpGetWidth() + nouveau_min;
}

/*
Fonction pour créer un ensemble de Julia
*/


void julia(double zoom,int maxIterations,double cImaginaire,double cReel){
	int height = gl4dpGetHeight();
	int width = gl4dpGetWidth();
	double nouveauReel, nouveauIm, reel, imaginaire;
	int color[maxIterations];
	for(int i =0;i< maxIterations;++i){
		color[i] = HSBtoRGB(i/256.f,1,i/(i+8.f));
	}

	for(int y = 0; y < height; ++y)
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
		} else {
			gl4dpSetColor(RGB(0,0,0));
			gl4dpPutPixel(x,y);
		}
	}
}


/*
Fonction pour creer une une fougère de Barnsley
*/

void barnsley(int width, int i){
	double x0=0;
	double y0=0;
	double nouveau_x;
	double nouveau_y;

	int random;
	for(int j= 0;j< i;++j){
		random = rand()%100;
		if(random==0){
			nouveau_x = 0;
			nouveau_y = 0.16*y0;
		} else if (random>=1 && random<=7){
			nouveau_x = -0.15*x0 + 0.28*y0;
			nouveau_y = 0.26*x0 + 0.24*y0 + 0.44;
		} else if (random>=8 && random<=15){
			nouveau_x = 0.2*x0 - 0.26*y0;
			nouveau_y = 0.23*x0 + 0.22*y0 + 1.6;
		} else {
			nouveau_x = 0.85*x0 + 0.04*y0;
			nouveau_y = -0.04*x0 + 0.85*y0 + 1.6;
		}
		gl4dpSetColor(RGB(255,69,0));
		gl4dpPutPixel(70*nouveau_x + width/2.0,70*nouveau_y);
		x0 = nouveau_x;
		y0 = nouveau_y;
	}
}
