#include "scene.h"
#include "utils.h"

#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <stdbool.h>

#define SHADER_NBR 10

void
scene_init(scene_t* s)
{
  GLuint pid[SHADER_NBR] = {0};

  /* shader quad */
  /* base */
  pid[0] = gl4duCreateProgram("<vs>shaders/depTex.vs", "<fs>shaders/depTex.fs", NULL);
  /* snow render */
  pid[1] = gl4duCreateProgram("<vs>shaders/depTex.vs", "<fs>shaders/snow.fs", NULL);
  /* snow */
  pid[6] = gl4duCreateProgram("<vs>shaders/snow.vs", "<fs>shaders/depTex.fs", NULL);
  /* fire */
  pid[4] = gl4duCreateProgram("<vs>shaders/fire.vs", "<fs>shaders/depTex.fs", NULL);
  /* fire render */
  pid[2] = gl4duCreateProgram("<vs>shaders/fire.vs", "<fs>shaders/fire.fs", NULL);
  /* ceiling */
  pid[5] = gl4duCreateProgram("<vs>shaders/space.vs", "<fs>shaders/depTex.fs", NULL);
  /* ceiling render */
  pid[3] = gl4duCreateProgram("<vs>shaders/fire.vs", "<fs>shaders/space.fs", NULL);
  /* floor */
  pid[7] = gl4duCreateProgram("<vs>shaders/floor.vs", "<fs>shaders/depTex.fs", NULL);
  /* sea render */
  pid[8] = gl4duCreateProgram("<vs>shaders/depTex.vs", "<fs>shaders/sea.fs", NULL);
  /* sea */
  pid[9] = gl4duCreateProgram("<vs>shaders/sea.vs", "<fs>shaders/depTex.fs", NULL);

  s->pgm_id = pid;

  /* GL objects */
  floor_init(&s->floor, s->pgm_id[7], "images/sphere.jpg");
  wall_init(&s->wall, s->pgm_id[0], "images/quad.jpg");
  fire_init(&s->fire, s->pgm_id[4], s->pgm_id[2]);
  chemney_init(&s->chemney, s->pgm_id[4],"images/sphere.jpg");
  ceiling_init(&s->ceiling, s->pgm_id[5], s->pgm_id[3]);
  snow_init(&s->snow, s->pgm_id[6], s->pgm_id[1]);
  sea_init(&s->sea, s->pgm_id[9], s->pgm_id[8]);
  credits_init(&s->credits, s->pgm_id[4], "images/credits.jpg");
}

void
scene_draw(scene_t* s)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);

  wall_draw(&s->wall);
  fire_draw(&s->fire);
  chemney_draw(&s->chemney);
  floor_draw(&s->floor);
  ceiling_draw(&s->ceiling);
  snow_draw(&s->snow);
  sea_draw(&s->sea);
  credits_draw(&s->credits);
}

void
scene_clear(scene_t* s) {
  floor_clear(&s->floor);
  wall_clear(&s->wall);
  fire_clear(&s->fire);
  chemney_clear(&s->chemney);
  ceiling_clear(&s->ceiling);
  snow_clear(&s->snow);
  sea_clear(&s->sea);
  credits_clear(&s->credits);
}
