#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <stdbool.h>

#include "fire.h"
#include "utils.h"

void
fire_init(fire_t* f, GLuint pgm_id, GLuint pgm_id_rendu)
{
  f->pgm_id_rendu = pgm_id_rendu;
  f->pgm_id = pgm_id;
  f->mesh_id = gl4dgGenCylinderf(100, 100);
  f->fbo_id = 0;

  /* création et paramétrage de la texture */
  glGenTextures(1, &(f->tex_id));
  glBindTexture(GL_TEXTURE_2D, f->tex_id);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  /* Génération et activation d'un FBO pour rendu de texture */
  glGenFramebuffers(1, &(f->fbo_id));
  glBindFramebuffer(GL_FRAMEBUFFER, f->fbo_id);
  /* Affectation de notre texture au FBO */
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, f->tex_id, 0);
  /* Affectation d'un drawbuffer au FBO */
  GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, DrawBuffers);
  /* desactivation */
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void
fire_render(fire_t* f)
{
  // Activation du FBO
  glBindFramebuffer(GL_FRAMEBUFFER, f->fbo_id);

  // Rafraichissement des buffers (reset)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* texturisation */
  glBindTexture(GL_TEXTURE_2D, f->tex_id);
  // glEnable(GL_CULL_FACE);
  // glEnable(GL_DEPTH_TEST);

  glUseProgram(f->pgm_id_rendu);
  glActiveTexture(GL_TEXTURE0);

  gl4duBindMatrix("projection_matrix");
  gl4duPushMatrix();
  {
      gl4duLoadIdentityf();

      gl4duBindMatrix("view_matrix");
      gl4duPushMatrix();
      {
          gl4duLoadIdentityf();
          gl4duLookAtf(
            0, 0, -10,
            0, 0, -20,
            0.0, 0.5, 0.0);

          gl4duBindMatrix("model_matrix");
          gl4duPushMatrix();
          {
              gl4duLoadIdentityf();

              gl4duTranslatef(-5, 0, -5);
              gl4duScalef(10, 10, 10);

              gl4duSendMatrices();
          }
          gl4duBindMatrix("model_matrix");
          gl4duPopMatrix();
      }
      gl4duBindMatrix("view_matrix");
      gl4duPopMatrix();
  }
  gl4duBindMatrix("projection_matrix");
  gl4duPopMatrix();


  glUniform1f(glGetUniformLocation(f->pgm_id_rendu, "temps"), getTime() / 1000);
  glUniform1i(glGetUniformLocation(f->pgm_id_rendu, "tex"), 0);

  gl4dgDraw(f->mesh_id);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void
fire_draw(fire_t* f)
{
  fire_render(f);

  gl4duBindMatrix("modelMatrix");
  gl4duLoadIdentityf();
  glUseProgram(f->pgm_id);
  glActiveTexture(GL_TEXTURE0);


  /* transformations */
  gl4duPushMatrix();
  {
    gl4duTranslatef(-5, 2, -5);
    gl4duRotatef(-65, 0, 1, 0);
    gl4duScalef(1, 1, 1);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  gl4duPopMatrix();

  /* texturisation */
  glBindTexture(GL_TEXTURE_2D, f->tex_id);
  // glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  glUniform1i(glGetUniformLocation(f->pgm_id, "tex"), 0);
  gl4dgDraw(f->mesh_id);
}

void fire_clear(fire_t* f) {
  glDeleteTextures(1, &f->tex_id);
}
