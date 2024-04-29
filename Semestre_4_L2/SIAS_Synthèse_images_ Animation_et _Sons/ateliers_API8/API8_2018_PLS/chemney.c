#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <stdbool.h>

#include "chemney.h"
#include "utils.h"

#define PARTS_NUMBER 3

GLuint mesh[PARTS_NUMBER] = { 0 };
GLuint texs[PARTS_NUMBER] = { 0 };

void
chemney_init(chemney_t* c, GLuint pgm_id, char* tex)
{
  c->pgm_id = pgm_id;
  c->mesh_id = mesh;
  c->tex_id = texs;

  c->mesh_id[0] = gl4dgGenCubef();
  c->mesh_id[1] = gl4dgGenCubef();
  c->mesh_id[2] = gl4dgGenCylinderf(100, 100);

  /* PARTIE BASSE */

  glGenTextures(1, &(c->tex_id[0]));
  glBindTexture(GL_TEXTURE_2D, c->tex_id[0]);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  loadTexture(c->tex_id[0], tex);

  /* REBORDS*/

  glGenTextures(1, &(c->tex_id[1]));
  glBindTexture(GL_TEXTURE_2D, c->tex_id[1]);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  loadTexture(c->tex_id[1], tex);
}

void
chemney_draw(chemney_t* c)
{
  glUniform1i(glGetUniformLocation(c->pgm_id, "tex"), 0);

  gl4duBindMatrix("modelMatrix");
  gl4duLoadIdentityf();

  /* REBORDS BAS FRONT*/

  gl4duPushMatrix(); {
    gl4duTranslatef(-4, 1, -5.0);
    gl4duRotatef(0, 0, 0, 0);
    gl4duScalef(0.5, 0.1, 1.1);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4duPopMatrix();

  /* texturisation */
  glUseProgram(c->pgm_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, c->tex_id[1]);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);


  gl4dgDraw(c->mesh_id[1]);

  /* lolwoot ? */

  gl4duPushMatrix(); {
    gl4duTranslatef(-4, 1, -5.0);
    gl4duRotatef(0, 0, 0, 0);
    gl4duScalef(0.1, 0.1, 1.1);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4duPopMatrix();

  /* texturisation */
  glUseProgram(c->pgm_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, c->tex_id[1]);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);


  gl4dgDraw(c->mesh_id[1]);

  /* REBORDS BAS GAUCHE*/

  gl4duPushMatrix(); {
    gl4duTranslatef(-5, 1, -4);
    gl4duRotatef(-90, 0, 1, 0);
    gl4duScalef(0.1, 0.1, 1);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4duPopMatrix();

  /* texturisation */
  glUseProgram(c->pgm_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, c->tex_id[1]);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);


  gl4dgDraw(c->mesh_id[1]);

  /* REBORDS BAS DROITE */

  gl4duPushMatrix(); {
    gl4duTranslatef(-5, 1, -6);
    gl4duRotatef(-90, 0, 1, 0);
    gl4duScalef(0.1, 0.1, 1);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4duPopMatrix();

  /* texturisation */
  glUseProgram(c->pgm_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, c->tex_id[1]);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);


  gl4dgDraw(c->mesh_id[1]);

  /* PARTIE BASSE */

  gl4duPushMatrix(); {
    gl4duTranslatef(-6, 0, -5);
    gl4duScalef(2, 1, 1);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4duPopMatrix();

  /* texturisation */
  glUseProgram(c->pgm_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, c->tex_id[0]);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);


  gl4dgDraw(c->mesh_id[0]);

  /* PARTIE HAUTE 1 */

  gl4duPushMatrix(); {
    gl4duTranslatef(-6, 3, -5);
    gl4duScalef(2.1, 0.5, 1.2);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4duPopMatrix();

  /* texturisation */
  glUseProgram(c->pgm_id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, c->tex_id[0]);
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);


  gl4dgDraw(c->mesh_id[0]);

}

void chemney_clear(chemney_t* c) {
  glDeleteTextures(1, &(c->tex_id[0]));
}
