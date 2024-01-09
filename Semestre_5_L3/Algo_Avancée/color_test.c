

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* pour Bocal */
#include <GL/gl.h> 
#include <GL/glut.h>
#include <GL/freeglut.h>  

int ColorsInt (GLubyte r, GLubyte g, GLubyte b) {
    int rgb = 0;
    int bits = 8;
    for ( int i = 0; i < bits; i++ ) {
        rgb |= (r & 1) << ( 2 * bits - 3 - i );
        rgb |= (g & 1) << ( 2 * bits - 2 - i );
        rgb |= (b & 1) << ( 2 * bits - 1 - i );
        r >>= 1;
        g >>= 1;
        b >>= 1;
    }
    return rgb;
};


