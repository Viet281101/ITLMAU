#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL4D/gl4dummies.h>

typedef struct {
    GLuint mesh_id;
    GLuint tex_id;
    GLuint pgm_id;
} floor_t;

void floor_init(floor_t* g, GLuint pgm_id, char* tex);
void floor_draw(floor_t* g);
void floor_clear(floor_t* g);
