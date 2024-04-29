#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <stdbool.h>

#include "floor.h"
#include "utils.h"

void
floor_init(floor_t* q, GLuint pgm_id, char* tex)
{
  q->pgm_id = pgm_id;
  q->mesh_id = gl4dgGenQuadf();

  /* création et paramétrage de la texture */
  glGenTextures(1, &(q->tex_id));
  glBindTexture(GL_TEXTURE_2D, q->tex_id);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  loadTexture(q->tex_id, tex);
}

void
floor_draw(floor_t* q)
{
  gl4duBindMatrix("modelMatrix");
  gl4duLoadIdentityf();
  glUseProgram(q->pgm_id);
  glActiveTexture(GL_TEXTURE0);

  /* transformations */
  gl4duTranslatef(0, 0, -10.0);
  gl4duPushMatrix(); {
    gl4duTranslatef(0, 0.0, -10);
    gl4duRotatef(-90, 1, 0, 0);
    gl4duScalef(200, 200, 200);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4duPopMatrix();

  /* texturisation */
  glBindTexture(GL_TEXTURE_2D, q->tex_id);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glUniform1i(glGetUniformLocation(q->pgm_id, "tex"), 0);
  gl4dgDraw(q->mesh_id);
}

void floor_clear(floor_t* q) {
  glDeleteTextures(1, &q->tex_id);
}
