#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL4D/gl4dummies.h>

typedef struct {
    GLuint mesh_id;
    GLuint tex_id;
    GLuint fbo_id;
    GLuint pgm_id;
    GLuint pgm_id_rendu;
} sea_t;

void sea_init(sea_t* c, GLuint pgm_id, GLuint pgm_id_rendu);
void sea_draw(sea_t* c);
void sea_clear(sea_t* c);
