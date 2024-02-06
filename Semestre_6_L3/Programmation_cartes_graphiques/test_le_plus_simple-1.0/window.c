#include <GL4D/gl4duw_SDL2.h>
#include <unistd.h>

void draw(void) {
  glClearColor(gl4dmURand() , gl4dmURand(), gl4dmURand(), 1);
  glClear(GL_COLOR_BUFFER_BIT);
  usleep(400000);
}

int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, /* args du programme */
			 "GL4Dummies' Hello World", /* titre */
			 10, 10, 640, 480, /* x,y, largeur, heuteur */
			 GL4DW_SHOWN | GL4DW_FULLSCREEN_DESKTOP) /* état visible */) {
    return 1;
  }
  glViewport(0, 0, 320, 480);
  gl4duwDisplayFunc(draw);
  gl4duwMainLoop();
  return 0;
}
