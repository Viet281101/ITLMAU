#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <stdbool.h>

#include "credits.h"
#include "utils.h"

void
credits_init(credits_t* q, GLuint pgm_id, char* tex)
{
  q->pgm_id = pgm_id;
  q->mesh_id = gl4dgGenCubef();

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
credits_draw(credits_t* q)
{
  gl4duBindMatrix("modelMatrix");
  gl4duLoadIdentityf();
  glUseProgram(q->pgm_id);
  glActiveTexture(GL_TEXTURE0);

  /* transformations */
  gl4duTranslatef(0, 0, -10.0);
  gl4duPushMatrix(); {
    gl4duTranslatef(0, 2, -35);
    gl4duRotatef(-180, 0, 0, 1);
    gl4duScalef(2, 2, 1);
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

void credits_clear(credits_t* q) {
  glDeleteTextures(1, &q->tex_id);
}
