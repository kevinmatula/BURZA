#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <iostream>
using namespace std;

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL Failed to Initialize.");
    return -1;
  }

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

  SDL_Delay(5000);

  SDL_Quit();
}
