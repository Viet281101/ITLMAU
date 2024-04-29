#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL4D/gl4dummies.h>

typedef struct {
    GLuint mesh_id;
    GLuint tex_id;
    GLuint fbo_id;
    GLuint pgm_id;
    GLuint pgm_id_rendu;
} fire_t;

void fire_init(fire_t* f, GLuint pgm_id, GLuint pgm_id_rendu);
void fire_draw(fire_t* f);
void fire_clear(fire_t* f);
