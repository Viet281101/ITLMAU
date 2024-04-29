/*!\file window.c
 *
 * \brief Utilisation de la SDL2, SDL2_Mixer et d'OpenGL 3+
 * \author Far�s BELHADJ, amsi@ai.univ-paris8.fr
 * \date February 03 2014
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <gl4du.h>
#include <SDL_mixer.h>

/*
 * Prototypes des fonctions statiques contenues dans ce fichier C
 */
static SDL_Window * initWindow(int w, int h, SDL_GLContext * poglContext);
static void quit(void);
static void initAudio(char * filename);
static void initGL(SDL_Window * win);
static void initData(void);
static void resizeGL(SDL_Window * win);
static void loop(SDL_Window * win);
static void manageEvents(SDL_Window * win);
static void draw(void);
static void printFPS(void);

/*!\brief pointeur vers la (future) fen�tre SDL */
static SDL_Window * _win = NULL;
/*!\brief pointeur vers le (futur) contexte OpenGL */
static SDL_GLContext _oglContext = NULL;
/*!\brief identifiant du (futur) vertex array object */
static GLuint _vao = 0;
/*!\brief identifiant du (futur) buffer de data */
static GLuint _buffer = 0;
/*!\brief identifiant du (futur) GLSL program */
static GLuint _pId = 0;
/*!\brief identifiant de la texture-�cran */
static GLuint _tId = 0, _tWidth = 1024;
/*!\brief texture utilis�e pour stocker la courbe du son */
static Uint8 * _audioCurve = NULL;
/*!\brief pointeur vers la musique charg�e par SDL_Mixer */
static Mix_Music * _mmusic = NULL;

/*!\brief La fonction principale initialise la biblioth�que SDL2,
 * demande la cr�ation de la fen�tre SDL et du contexte OpenGL par
 * l'appel � \ref initWindow, initialise OpenGL avec \ref initGL et
 * lance la boucle (infinie) principale.
 */
int main(int argc, char ** argv) {
  if(argc != 2) {
    fprintf(stderr, "usage: %s <filename.mp3>\n", argv[0]);
    exit(-1);
  }
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    fprintf(stderr, "Erreur lors de l'initialisation de SDL :  %s", SDL_GetError());
    return -2;
  }
  atexit(SDL_Quit);
  if((_win = initWindow(1024, 256, &_oglContext))) {    
    initAudio(argv[1]);
    initGL(_win);
    _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/basic.fs", NULL);
    initData();
    loop(_win);
  }
  return 0;
}

/*!\brief Cette fonction est appel�e au moment de sortir du programme
 *  (atexit), elle lib�re les donn�es audio, la fen�tre SDL \ref _win
 *  et le contexte OpenGL \ref _oglContext.
 */
static void quit(void) {
  if(_mmusic) {
    while(Mix_PlayingMusic() && Mix_FadeOutMusic(2000)) {
      draw();
      SDL_GL_SwapWindow(_win);
      SDL_Delay(1);
    }
    Mix_FreeMusic(_mmusic);
    _mmusic = NULL;
  }
  Mix_CloseAudio();
  Mix_Quit();
  if(_vao)
    glDeleteVertexArrays(1, &_vao);
  if(_buffer)
    glDeleteBuffers(1, &_buffer);
  if(_buffer)
    glDeleteTextures(1, &_tId);
  if(_oglContext)
    SDL_GL_DeleteContext(_oglContext);
  if(_win)
    SDL_DestroyWindow(_win);
  if(_audioCurve) {
    free(_audioCurve);
    _audioCurve = NULL;
  }
  gl4duClean(GL4DU_ALL);
}

/*!\brief Cette fonction cr�� la fen�tre SDL de largeur \a w et de
 *  hauteur \a h, le contexte OpenGL \ref et stocke le pointeur dans
 *  poglContext. Elle retourne le pointeur vers la fen�tre SDL.
 *
 * Le contexte OpenGL cr�� est en version 3 pour
 * SDL_GL_CONTEXT_MAJOR_VERSION, en version 2 pour
 * SDL_GL_CONTEXT_MINOR_VERSION et en SDL_GL_CONTEXT_PROFILE_CORE
 * concernant le profile. Le double buffer est activ� et le buffer de
 * profondeur est en 24 bits.
 *
 * \param w la largeur de la fen�tre � cr�er.
 * \param h la hauteur de la fen�tre � cr�er.
 * \param poglContext le pointeur vers la case o� sera r�f�renc� le
 * contexte OpenGL cr��.
 * \return le pointeur vers la fen�tre SDL si tout se passe comme
 * pr�vu, NULL sinon.
 */
static SDL_Window * initWindow(int w, int h, SDL_GLContext * poglContext) {
  SDL_Window * win = NULL;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  if( (win = SDL_CreateWindow("Fenetre GL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			      w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | 
			      SDL_WINDOW_SHOWN)) == NULL )
    return NULL;
  if( (*poglContext = SDL_GL_CreateContext(win)) == NULL ) {
    SDL_DestroyWindow(win);
    return NULL;
  }
  fprintf(stderr, "Version d'OpenGL : %s\n", glGetString(GL_VERSION));
  fprintf(stderr, "Version de shaders supportes : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));  
  atexit(quit);
  return win;
}

/*!\brief Cette fonction est appel�e quand l'audio est jou� et met
 * dans \a stream les donn�es audio de longueur \a len.
 */
static void mixCallback(void *udata, Uint8 *stream, int len) {
  if(_audioCurve) {
    int i;
    Sint16 *d = stream;
    memset(_audioCurve, 0,  _tWidth * 256);
    for(i = 0; i < MIN(len >> 1, _tWidth); i++)
      _audioCurve[i + (128 + (d[i] >> 8)) * _tWidth] = -1;
  }
}

/*!\brief Cette fonction initialise les param�tres SDL_Mixer et charge le fichier audio.
 *
 * \param filename le nom du fichier � charger.
 */
static void initAudio(char * filename) {
  int mixFlags = MIX_INIT_MP3, res;
  res = Mix_Init(mixFlags);
  if( (res & mixFlags) != mixFlags ) {
    fprintf(stderr, "Mix_Init: Erreur lors de l'initialisation de la biblioth�que SDL_Mixer\n");
    fprintf(stderr, "Mix_Init: %s\n", Mix_GetError());
    exit(-3);
  }
  if(Mix_OpenAudio(22050, AUDIO_S16LSB, 1, 2048) < 0)
    exit(-4);  
  if(!(_mmusic = Mix_LoadMUS(filename))) {
    fprintf(stderr, "Erreur lors du Mix_LoadMUS: %s\n", Mix_GetError());
    exit(-5);
  }
  Mix_SetPostMix(mixCallback, NULL);
}

/*!\brief Cette fonction initialise les param�tres OpenGL.
 *
 * \param win le pointeur vers la fen�tre SDL pour laquelle nous avons
 * attach� le contexte OpenGL.
 */
static void initGL(SDL_Window * win) {
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  resizeGL(win);
}

static void initData(void) {
  GLfloat data[] = {
    /* 4 coordonn�es de sommets */
    -0.99f, -0.99f, 0.99f, -0.99f,
    -0.99f,  0.99f, 0.99f,  0.99f,
    /* 2 coordonn�es de texture par sommet */
    0.0f, 0.0f, 1.0f, 0.0f, 
    0.0f, 1.0f, 1.0f, 1.0f
  };
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenTextures(1, &_tId);

  glGenBuffers(1, &_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof data, data, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void *)0);  
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const void *)((4 * 2) * sizeof *data));
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glBindTexture(GL_TEXTURE_2D, _tId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  _audioCurve = calloc(_tWidth * 256, sizeof *_audioCurve);
  assert(_audioCurve);

  glBindTexture(GL_TEXTURE_2D, 0);
}

/*!\brief Cette fonction param�trela vue (viewPort) OpenGL en fonction
 * des dimensions de la fen�tre SDL point�e par \a win.
 *
 * \param win le pointeur vers la fen�tre SDL pour laquelle nous avons
 * attach� le contexte OpenGL.
 */
static void resizeGL(SDL_Window * win) {
  int w, h;
  SDL_GetWindowSize(win, &w, &h);
  glViewport(0, 0, w, h);
}

/*!\brief Boucle infinie principale : g�re les �v�nements, dessine,
 * imprime le FPS et swap les buffers.
 *
 * \param win le pointeur vers la fen�tre SDL pour laquelle nous avons
 * attach� le contexte OpenGL.
 */
static void loop(SDL_Window * win) {
  Uint32 t;
  t = SDL_GetTicks();
  SDL_GL_SetSwapInterval(1);
  for(;;) {
    manageEvents(win);
    draw();
    printFPS();
    SDL_GL_SwapWindow(win);
    gl4duUpdateShaders();
    if(!Mix_PlayingMusic() && SDL_GetTicks() - t > 500 /* attendre 0.5s */)
      Mix_PlayMusic(_mmusic, -1);
  }
}

/*!\brief Cette fonction permet de g�rer les �v�nements clavier et
 * souris via la biblioth�que SDL et pour la fen�tre point�e par \a
 * win.
 *
 * \param win le pointeur vers la fen�tre SDL pour laquelle nous avons
 * attach� le contexte OpenGL.
 */
static void manageEvents(SDL_Window * win) {
  SDL_Event event;
  while(SDL_PollEvent(&event)) 
    switch (event.type) {
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
      case SDLK_ESCAPE:
      case 'q':
	exit(0);
      default:
	fprintf(stderr, "La touche %s a ete pressee\n",
		SDL_GetKeyName(event.key.keysym.sym));
	break;
      }
      break;
    case SDL_KEYUP:
      break;
    case SDL_WINDOWEVENT:
      if(event.window.windowID == SDL_GetWindowID(win)) {
	switch (event.window.event)  {
	case SDL_WINDOWEVENT_RESIZED:
	  resizeGL(win);
	  break;
	case SDL_WINDOWEVENT_CLOSE:
	  event.type = SDL_QUIT;
	  SDL_PushEvent(&event);
	  break;
	}
      }
      break;
    case SDL_QUIT:
      exit(0);
    }
}

/*!\brief Cette fonction dessine dans le contexte OpenGL actif.
 */
static void draw(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(_pId);
  glBindVertexArray(_vao);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1); 
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _tId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _tWidth, 256, 0, GL_RED, GL_UNSIGNED_BYTE, _audioCurve);
  glUniform1i(glGetUniformLocation(_pId, "myTexture"), 0);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  glUseProgram(0);
}

/*!\brief Cette fonction imprime le FPS (Frames Per Second) de
 * l'application.
 */
static void printFPS(void) {
  Uint32 t;
  static Uint32 t0 = 0, f = 0;
  f++;
  t = SDL_GetTicks();
  if(t - t0 > 2000) {
    fprintf(stderr, "%8.2f\n", (1000.0 * f / (t - t0)));
    t0 = t;
    f  = 0;
  }
}
