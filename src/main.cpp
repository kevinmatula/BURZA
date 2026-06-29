#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <iostream>
using namespace std;

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL Failed to Initialize.");
    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window *window;
  window = SDL_CreateWindow("BURZA", 600, 600,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  SDL_GLContext glContext;
  if (glContext = SDL_GL_CreateContext(window); glContext == NULL) {
    SDL_Log("OpenGL Context Failed to Initialize.");
    return -1;
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_Log("Glad Failed to Initialize.");
    return -1;
  }

  // For debugging and demo purposes
  cout << glGetString(GL_VERSION) << endl;

  int isRunning = 1;
  while (isRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        case SDL_EVENT_QUIT:
          isRunning = 0;
          break;
        case SDL_EVENT_KEY_DOWN:
          if (event.key.key == SDLK_ESCAPE) {
            isRunning = 0;
          }
          break;
        default:
          break;
      }
    }

    glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
    SDL_Delay(1);
  }

  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(window);

  SDL_Quit();
}
