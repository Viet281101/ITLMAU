#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL4D/gl4dummies.h>

typedef struct {
    GLuint mesh_id;
    GLuint tex_id;
    GLuint fbo_id;
    GLuint pgm_id;
    GLuint pgm_id_rendu;
} snow_t;

void snow_init(snow_t* c, GLuint pgm_id, GLuint pgm_id_rendu);
void snow_draw(snow_t* c);
void snow_clear(snow_t* c);
