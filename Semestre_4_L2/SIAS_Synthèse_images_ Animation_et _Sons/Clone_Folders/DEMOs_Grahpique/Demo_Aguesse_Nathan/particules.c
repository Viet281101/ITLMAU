#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4dh.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "particules.h"

typedef struct s_particules_t {
  float scaleSet, scaleX, scaleY, scaleZ;
  float posX, posY, posZ;
  float angRot, rotX, rotY, rotZ, angRotSpe;
  float r, g, b, a;
  int forme;
} particules_t;

static particules_t _particules[10000];
static GLuint _pId = 0;
static GLuint _cubeId = 0;
static GLuint _sphereId = 0;
static GLuint _coneId = 0;
static GLuint _fanConeId = 0;
static GLuint _cylinderId = 0;
static GLuint _torusId = 0;
static GLint _use_Ld = 0;

static double get_dt(void) {
  static double t0 = 0.0f;
  double t = gl4dGetElapsedTime(), dt = (t - t0) / 1000.0;
  t0 = t;
  return dt;
}

void initParticules() {
    int i;
    srand(12345);
    for (i = 0; i < 10000; i++) {
        _particules[i].posZ = gl4dmURand() * -1000.0f;
        _particules[i].posX = gl4dmSURand() * ((abs(_particules[i].posZ)+5.0f) * 2);
        _particules[i].posY = gl4dmSURand() * ((abs(_particules[i].posZ)+5.0f) * 2);
        _particules[i].scaleSet = 1.0f + 1.0f * ((abs(_particules[i].posZ)+5.0f) * 0.001f);
        _particules[i].angRot = gl4dmURand() * 360.0f;
        _particules[i].rotX = gl4dmURand();
        _particules[i].rotY = gl4dmURand();
        _particules[i].rotZ = gl4dmURand();
        _particules[i].angRotSpe = i%2 ? -1.0f : 1.0f;
        _particules[i].r = gl4dmURand();
        _particules[i].g = gl4dmURand();
        _particules[i].b = gl4dmURand();
        _particules[i].a = 1.0f;
        _particules[i].forme = 0;
    }

    _pId = gl4duCreateProgram("<vs>shaders/particules.vs", "<fs>shaders/particules.fs", NULL);
    _cubeId = gl4dgGenCubef();
    _sphereId = gl4dgGenSpheref(4, 4);
    _coneId = gl4dgGenConef(3, GL_TRUE);
    _fanConeId = gl4dgGenFanConef(3, GL_TRUE);
    _cylinderId = gl4dgGenCylinderf(6, GL_TRUE);
    _torusId = gl4dgGenTorusf(4, 4, 0.3);
}

static void randomizeFormes() {
    int i;
    for (i = 0; i < 10000; i++)
        _particules[i].forme = rand() % 6;
} 
/*
int nmb : Nombre de particules
int nmbColor : Nombre de particules coloré
int scale : Coeficient qui agit sur le scale des particules par rapport à la profondeur
int rotateSelf : Vitesse de rotation sur soi même (angle degré par secondes)
int rotateAxeZ : Vitesse de rotation sur l'axe Z (angle degré par secondes)
int random : Booléen si les formes change aléatoirement chaque seconde
int ld : Booléen si lumière directionelle utilisé
*/
void drawParticules(int nmb, int nmbColor, int scale, int rotateSelf, int rotateAxeZ, int random, int ld) {
    static float addAngleRotSelf = 0.0f, addAngleRotAxeZ = 0.0f, timer = 0.0f, time = 0.0f;
    double dt = get_dt();
    int i;
    timer += dt; time += dt;
    if (timer > 1.2f) {
        timer -= 1.2f;
        randomizeFormes();
    }
    glUseProgram(_pId);

    glUniform3f(glGetUniformLocation(_pId, "ld"), cos(time*1.33), sin(time*1.33), -1.0f);

    if (ld != _use_Ld) {
        _use_Ld = ld;
        glUniform1i(glGetUniformLocation(_pId, "use_Ld"), _use_Ld);
    }

    if (nmb > 10000)
        nmb = 10000;

    if (rotateSelf)
        addAngleRotSelf += rotateSelf * dt;
    if (rotateAxeZ)
        addAngleRotAxeZ += rotateAxeZ * dt;

    for (i = 0; i < nmb; i++) {

        gl4duLoadIdentityf();
        gl4duRotatef(_particules[i].angRotSpe * addAngleRotAxeZ, 0.0f, 0.0f, 1.0f);
        gl4duTranslatef(_particules[i].posX, _particules[i].posY, _particules[i].posZ);
        gl4duRotatef(_particules[i].angRot + addAngleRotSelf, _particules[i].rotX, _particules[i].rotY, _particules[i].rotZ);
        if (scale == -1)
            gl4duScalef(_particules[i].scaleSet, _particules[i].scaleSet, _particules[i].scaleSet);
        else
            gl4duScalef(((_particules[i].scaleSet - 1.0f) * scale) + 1.0f, ((_particules[i].scaleSet - 1.0f) * scale) + 1.0f, ((_particules[i].scaleSet - 1.0f) * scale) + 1.0f);
        gl4duSendMatrices();

        if (i < nmbColor)
            glUniform4f(glGetUniformLocation(_pId, "color"), _particules[i].r, _particules[i].g, _particules[i].b, _particules[i].a);
        else
            glUniform4f(glGetUniformLocation(_pId, "color"), 1.0f, 1.0f, 1.0f, 1.0f);

        if (random) {
            switch(_particules[i].forme) {
                case 0:
                    gl4dgDraw(_cubeId);
                    break;
                case 1:
                    gl4dgDraw(_sphereId);
                    break;
                case 2:
                    gl4dgDraw(_coneId);
                    break;
                case 3:
                    gl4dgDraw(_fanConeId);
                    break;
                case 4:
                    gl4dgDraw(_cylinderId);
                    break;
                case 5:
                    gl4dgDraw(_torusId);
                    break;
            }
        }
        else
            gl4dgDraw(_cubeId);
    }
    glUseProgram(0);
}