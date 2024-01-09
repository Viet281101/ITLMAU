
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
	float x ; // composante horizontale du vecteur
	float y ; // composante verticale du vecteur
} Vecteur ;


Vecteur somme(Vecteur a, Vecteur b) {
	Vecteur c = a;
	c.x += b.x;
	c.y += b.y;

	return c;
}

