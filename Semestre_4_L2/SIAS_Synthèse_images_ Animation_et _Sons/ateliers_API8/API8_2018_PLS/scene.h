#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL4D/gl4dummies.h>
#include <stdbool.h>

#include "fire.h"
#include "floor.h"
#include "wall.h"
#include "chemney.h"
#include "ceiling.h"
#include "snow.h"
#include "sea.h"
#include "credits.h"

typedef struct {
    /* GLSL program Id */
    GLuint* pgm_id;

    /* scene objects */
    floor_t floor;
    fire_t fire;
    wall_t wall;
    chemney_t chemney;
    ceiling_t ceiling;
    snow_t snow;
    sea_t sea;
    credits_t credits;
} scene_t;

void scene_init(scene_t* s);
void scene_resize(scene_t* s, int width, int height);
void scene_draw(scene_t* s);
void scene_clear(scene_t* s);
