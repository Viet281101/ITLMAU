#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL4D/gl4dummies.h>

typedef struct {
    GLuint mesh_id;
    GLuint tex_id;
    GLuint fbo_id;
    GLuint pgm_id;
    GLuint pgm_id_rendu;
} ceiling_t;

void ceiling_init(ceiling_t* c, GLuint pgm_id, GLuint pgm_id_rendu);
void ceiling_draw(ceiling_t* c);
void ceiling_clear(ceiling_t* c);
