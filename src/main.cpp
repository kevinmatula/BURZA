#include <SDL3/SDL.h>
#include <chrono>
#include <glad/glad.h>
#include <iostream>
using namespace std;

int main() {

  // INITIALZING RENDER //
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
  glClearColor(0.7f, 0.9f, 0.1f, 1.0f);

  ////

  double timePerFrame = 1.0 / 60.0;
  int isRunning = 1;
  while (isRunning) {

    auto start = chrono::high_resolution_clock::now();
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

    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    double frameTime = elapsed.count();
    if (frameTime > 0.25) {
      frameTime = 0.25;
    }
    if (timePerFrame >= frameTime) {
      SDL_Delay(
          static_cast<uint32_t>((timePerFrame * 1000) - (frameTime * 1000)));
    }
  }

  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(window);

  SDL_Quit();
}
