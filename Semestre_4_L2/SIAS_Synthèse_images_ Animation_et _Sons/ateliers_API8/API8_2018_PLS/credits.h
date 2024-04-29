#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL4D/gl4dummies.h>

typedef struct {
    GLuint mesh_id;
    GLuint tex_id;
    GLuint pgm_id;
} credits_t;

void credits_init(credits_t* g, GLuint pgm_id, char* tex);
void credits_draw(credits_t* g);
void credits_clear(credits_t* g);
