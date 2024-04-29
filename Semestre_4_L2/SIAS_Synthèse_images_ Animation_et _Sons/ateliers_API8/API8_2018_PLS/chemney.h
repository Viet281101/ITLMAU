#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL4D/gl4dummies.h>

typedef struct {
    GLuint* mesh_id;
    GLuint* tex_id;
    GLuint pgm_id;
    GLuint fire_fbo;
} chemney_t;

void chemney_init(chemney_t* c, GLuint pgm_id, char* tex);
void chemney_draw(chemney_t* c);
void chemney_clear(chemney_t* c);
