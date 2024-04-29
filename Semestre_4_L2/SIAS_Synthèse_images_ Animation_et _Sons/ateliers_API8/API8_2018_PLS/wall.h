#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL4D/gl4dummies.h>

typedef struct {
    GLuint mesh_id;
    GLuint tex_id;
    GLuint pgm_id;
} wall_t;

void wall_init(wall_t* g, GLuint pgm_id, char* tex);
void wall_draw(wall_t* g);
void wall_clear(wall_t* g);
